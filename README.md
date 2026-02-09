# IoT Air Quality Dashboard - Deployment Guide

## 1. Setup Firebase
(See previous instructions to set up Realtime Database and get your keys)

## 2. Prepare Code
1.  **Dashboard**: Open `index.html` and fill in your `firebaseConfig` keys.
2.  **ESP8266**: Open `esp8266_firebase.ino`, fill in `FIREBASE_HOST` and `FIREBASE_AUTH`, and flash to your NodeMCU.

## 3. Host on GitHub Pages
This allows you to access your dashboard from anywhere (e.g., `https://yourname.github.io/air-quality`).

### Step 1: Push to GitHub
If you haven't already:
1.  Create a new repository on GitHub (e.g., `air-quality-dashboard`).
2.  Open a terminal in this folder and run:
    ```bash
    git init
    git add .
    git commit -m "Initial commit"
    git branch -M main
    git remote add origin https://github.com/YOUR_USERNAME/air-quality-dashboard.git
    git push -u origin main
    ```

### Step 2: Enable GitHub Pages
1.  Go to your repository **Settings** on GitHub.
2.  Click **Pages** (in the left sidebar).
3.  Under **Branch**, select `main` and `/ (root)`.
4.  Click **Save**.
5.  Wait a minute, and you will see your live URL!

## 4. Verify
- Open your fresh GitHub Pages URL.
- Power on your ESP8266.
- The dashboard should show "● Live" and the "Last Activity" time should update every 2 seconds.
