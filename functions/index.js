const functions = require("firebase-functions");
const admin = require("firebase-admin");
const { GoogleGenerativeAI } = require("@google/generative-ai");

admin.initializeApp();
const db = admin.database();

// Configure Gemini API
// IMPORTANT: Set your API key in Firebase config:
// firebase functions:config:set gemini.key="YOUR_API_KEY"
const GEN_AI_KEY = functions.config().gemini?.key || "YOUR_API_KEY";
const genAI = new GoogleGenerativeAI(GEN_AI_KEY);
const model = genAI.getGenerativeModel({ model: "gemini-pro" });

/**
 * Triggered when a new sensor reading is written to /sensor/live
 * 1. Archives the reading to /sensor/history
 * 2. Periodically analyzes history with Gemini AI
 */
exports.onSensorUpdate = functions.database.ref("/sensor/live")
    .onWrite(async (change, context) => {
        const data = change.after.val();

        if (!data) return null; // Exit if data was deleted

        // 1. Archive Data
        // We use the timestamp from the data or server time
        const timestamp = Date.now();
        await db.ref("/sensor/history").push({
            ...data,
            timestamp: timestamp
        });

        // 2. Check if we should run AI Analysis
        // To save costs/quota, we only run AI every 10 minutes (600,000 ms)
        const lastRunRef = db.ref("/analysis/lastRun");
        const lastRunSnap = await lastRunRef.once("value");
        const lastRun = lastRunSnap.val() || 0;

        if (timestamp - lastRun < 600000) {
            console.log("Skipping AI analysis (throttled)");
            return null;
        }

        // 3. Run AI Analysis
        return runAIAnalysis(timestamp);
    });

async function runAIAnalysis(timestamp) {
    try {
        // Fetch last 10 readings for context
        const historySnap = await db.ref("/sensor/history")
            .orderByKey()
            .limitToLast(10)
            .once("value");

        const history = [];
        historySnap.forEach(snap => history.push(snap.val()));

        if (history.length === 0) return null;

        const current = history[history.length - 1]; // Latest

        // Construct Prompt
        const prompt = `
            Analyze this air quality data (last ${history.length} readings):
            Current: AQI ${current.aqi}, Temp ${current.temperature}°C, Humidity ${current.humidity}%
            Trend: ${JSON.stringify(history.map(h => ({ a: h.aqi, t: h.temperature, h: h.humidity })))}
            
            Provide a short (2 sentences), friendly environmental summary for a home dashboard. 
            Mention any health risks if AQI is high (>100). 
            Suggest ventilation if humidity > 70.
        `;

        // Call Gemini
        const result = await model.generateContent(prompt);
        const response = await result.response;
        const text = response.text();

        // Save Analysis to DB
        await db.ref("/analysis/latest").set({
            text: text,
            timestamp: timestamp
        });

        // Update Last Run
        await db.ref("/analysis/lastRun").set(timestamp);

        console.log("AI Analysis Complete:", text);
    } catch (error) {
        console.error("AI Analysis Failed:", error);
    }
}
