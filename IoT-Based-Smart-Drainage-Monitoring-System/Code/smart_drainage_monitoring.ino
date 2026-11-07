/*
  IoT-Based Smart Drainage Monitoring System
  Controller: NodeMCU ESP8266
  Sensors: DHT11, MQ-135 (analog), two ultrasonic sensors
  Outputs: 16x2 I2C LCD, buzzer
  Cloud: Blynk

  SECURITY:
  - Enter your own Wi-Fi SSID/password and Blynk auth token below.
  - Never commit real credentials to a public GitHub repository.
*/

#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_BLYNK_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Replace these placeholders with your own local Wi-Fi credentials.
// Do not upload real credentials to GitHub.
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

// Sensor pin definitions (as supplied)
#define DHTPIN D3
#define DHTTYPE DHT11
#define AIR_QUALITY_PIN A0
#define S1_TRIG D8
#define S1_ECHO D7
#define S2_TRIG D6
#define S2_ECHO D5

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // A timeout avoids waiting indefinitely if no echo is received.
  long duration = pulseIn(echoPin, HIGH, 30000UL);
  if (duration == 0) {
    return -1.0; // No echo / out of range
  }
  return duration * 0.0343 / 2.0;
}

void setup() {
  Serial.begin(115200);

  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(S1_TRIG, OUTPUT);
  pinMode(S1_ECHO, INPUT);
  pinMode(S2_TRIG, OUTPUT);
  pinMode(S2_ECHO, INPUT);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int airQuality = analogRead(AIR_QUALITY_PIN);
  float distance1 = getDistance(S1_TRIG, S1_ECHO);
  float distance2 = getDistance(S2_TRIG, S2_ECHO);

  Serial.print("Temp: "); Serial.print(temperature);
  Serial.print(" C, Hum: "); Serial.print(humidity);
  Serial.print(" %, Air: "); Serial.print(airQuality);
  Serial.print(", Dist1: "); Serial.print(distance1);
  Serial.print(" cm, Dist2: "); Serial.println(distance2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(temperature, 0);
  lcd.print(" H:"); lcd.print(humidity, 0);
  lcd.setCursor(0, 1);
  lcd.print("AQ:"); lcd.print(airQuality);
  lcd.print(" P1:"); lcd.print(distance1, 0);

  if (distance1 >= 0 && distance1 <= 3) {
    Blynk.logEvent("pipe_1_blocked");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("WARNING..!!!");
    lcd.setCursor(0, 1);
    lcd.print("PIPE 1 BLOCKED");
    digitalWrite(D0, HIGH);
    delay(1000);
    digitalWrite(D0, LOW);
  }

  if (distance2 >= 0 && distance2 <= 3) {
    Blynk.logEvent("pipe_2_blocked");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("WARNING..!!!");
    lcd.setCursor(0, 1);
    lcd.print("PIPE 2 BLOCKED");
    digitalWrite(D0, HIGH);
    delay(1000);
    digitalWrite(D0, LOW);
  }

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, airQuality);
  Blynk.virtualWrite(V3, distance1);
  Blynk.virtualWrite(V4, distance2);

  delay(500);
}
