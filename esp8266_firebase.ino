#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>

/* -------- WiFi Credentials -------- */
#define WIFI_SSID "dilli"
#define WIFI_PASSWORD "12345678"

/* -------- Firebase Config -------- */
#define FIREBASE_HOST "YOUR_PROJECT_ID.firebaseio.com" // Without http:// or https://
#define FIREBASE_AUTH "YOUR_DATABASE_SECRET"

/* -------- Objects -------- */
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/* -------- Timing -------- */
unsigned long lastSendTime = 0;
unsigned long sendInterval = 2000; // 2 seconds

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); 

  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());

  /* Assign the config data */
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&firebaseConfig, &firebaseAuth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (millis() - lastSendTime > sendInterval) {
    lastSendTime = millis();
    
    int raw = analogRead(A0);
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("DHT Sensor Failed");
      return;
    }

    // Calculate generic AQI from raw (same logic as before)
    int aqi;
    if (raw < 150) aqi = 50;
    else if (raw < 300) aqi = 100;
    else if (raw < 450) aqi = 200;
    else aqi = 300;

    // Create JSON object
    FirebaseJson json;
    json.set("aqi", aqi);
    json.set("raw", raw);
    json.set("temperature", temperature);
    json.set("humidity", humidity);
    json.set("timestamp/.sv", "timestamp"); // Firebase Server Timestamp

    // Push to Firebase at path "/sensor/live"
    if (Firebase.setJSON(firebaseData, "/sensor/live", json)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      digitalWrite(LED_BUILTIN, LOW); // Flash LED
      delay(100);
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
    }
  }
}
