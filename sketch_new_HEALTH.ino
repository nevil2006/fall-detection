#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_I2C.h>

Adafruit_MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BUZZER 25

// WiFi
const char* ssid = "TECNO POVA 5 Pro 5G";
const char* password = "guwei_shi15";
const char* serverName = "http://192.168.85.131:5000/predict";

// Fall detection thresholds
#define FREE_FALL_THRESHOLD 5.0
#define IMPACT_THRESHOLD 10.5

bool fallDetected = false;
unsigned long fallTime = 0;
unsigned long lastLCDUpdate = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  lcd.init();
  lcd.backlight();

  if (!mpu.begin()) {
    lcd.print("MPU Error!");
    while (1);
  }

  WiFi.begin(ssid, password);
  lcd.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1500);
  lcd.clear();
}

void loop() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float totalAcceleration = sqrt(
    a.acceleration.x * a.acceleration.x +
    a.acceleration.y * a.acceleration.y +
    a.acceleration.z * a.acceleration.z
  );

  Serial.print("Acceleration: ");
  Serial.println(totalAcceleration);

  // -------- FALL DETECTION LOGIC (Stable Version) --------
  if (!fallDetected) {
    if (totalAcceleration < FREE_FALL_THRESHOLD) {
      fallTime = millis();
    }

    if (millis() - fallTime < 1000 && totalAcceleration > IMPACT_THRESHOLD) {
      fallDetected = true;
    }
  }

  // -------- LCD UPDATE --------
  if (millis() - lastLCDUpdate > 500) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Acc:");
    lcd.print(totalAcceleration, 1);

    lcd.setCursor(0, 1);

    if (fallDetected) {
      lcd.print("FALL DETECTED");
    } else {
      lcd.print("Normal");
    }

    lastLCDUpdate = millis();
  }

  // -------- BUZZER CONTROL --------
  if (fallDetected) {
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }

  // -------- OPTIONAL: Send Data to Server --------
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String jsonData = "{";
    jsonData += "\"acc_mean\":" + String(totalAcceleration,3) + ",";
    jsonData += "\"acc_max\":" + String(totalAcceleration,3) + ",";
    jsonData += "\"acc_std\":0.5,";
    jsonData += "\"gyro_mean\":0.1,";
    jsonData += "\"gyro_max\":0.1,";
    jsonData += "\"gyro_std\":0.1";
    jsonData += "}";

    http.POST(jsonData);
    http.end();
  }

  delay(50);
}