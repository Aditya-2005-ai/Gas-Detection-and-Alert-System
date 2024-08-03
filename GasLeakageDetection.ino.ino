#include <MQ2.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int analogInputPin = A0;
MQ2 mq2(analogInputPin);
RTC_DS3231 rtc;

// Thresholds for gas leakage detection
const int LPG_THRESHOLD = 600;
const int CO_THRESHOLD = 5000;    // Adjust as needed
const int SMOKE_THRESHOLD = 10000; // Adjust as needed

// Timer variables
unsigned long lastTemperatureDisplayTime = 0;
unsigned long lastGasLevelsDisplayTime = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  mq2.begin();

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  unsigned long currentMillis = millis();

  // Display temperature for 5 seconds every 10 seconds
  if (currentMillis - lastTemperatureDisplayTime >= 10000) {
    displayTemperature();
    lastTemperatureDisplayTime = currentMillis;
  } else if (currentMillis - lastTemperatureDisplayTime <= 5000) {
    // Display gas levels every 2 seconds
    if (currentMillis - lastGasLevelsDisplayTime >= 2000) {
      displayGasLevels();
      lastGasLevelsDisplayTime = currentMillis;
    }
  } else {
    // Check for gas leakage every second
    if (currentMillis - lastGasLevelsDisplayTime >= 1000) {
      checkGasLeakage();
    }
  }
}

void displayTemperature() {
  float temperature = rtc.getTemperature();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.print(" C");
}

void displayGasLevels() {
  int lpg = mq2.readLPG();
  int co = mq2.readCO();
  int smoke = mq2.readSmoke();

  // Print raw sensor values for debugging
  Serial.print("Raw Sensor Values - LPG: ");
  Serial.print(lpg);
  Serial.print(", CO: ");
  Serial.print(co);
  Serial.print(", Smoke: ");
  Serial.println(smoke);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LPG:");
  lcd.print(lpg);
  lcd.print(" CO:");
  lcd.print(co);
  lcd.setCursor(0, 1);
  lcd.print("SMOKE:");
  lcd.print(smoke);
  lcd.print(" PPM");
}

void checkGasLeakage() {
  int lpg = mq2.readLPG();

  // Check for gas leakage
  if (lpg > LPG_THRESHOLD) {
    lcd.clear();
    lcd.print("Gas Leakage");
    lcd.setCursor(0, 1);
    lcd.print("Detected!");
    
    // Note the exact date and time in Serial Monitor
    DateTime now = rtc.now();
    Serial.print("Gas Leakage Detected at: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(":");
    Serial.print(now.minute(), DEC);
    Serial.print(":");
    Serial.println(now.second(), DEC);
  }
}


