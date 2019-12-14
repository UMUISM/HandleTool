#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal.h>

#define ECHO 11
#define TRIG 10

LiquidCrystal lcd(7, 8, 6, 5, 4, 3);
DHT dht(9, DHT11);
int Button = LOW;

double GetLength() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(1);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  double distance = pulseIn(ECHO, HIGH);
  distance /= 58;
  return distance;
}

void setup() {
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("STARTING     ^_^");
  lcd.setCursor(0, 1);
  lcd.print("By GloomyGhost");
  delay(2000);
  lcd.clear();
}

void loop() {
  while (1) {
    int Button = digitalRead(12);
    if (Button != HIGH) {
      double h = dht.readHumidity();
      double t = dht.readTemperature();
      lcd.setCursor(0, 0);
      lcd.print("Tempture: ");
      lcd.print(t);
      lcd.print("C");
      lcd.setCursor(0, 1);
      lcd.print("Humidity: ");
      lcd.print(h);
      lcd.print("%");
    } else {
      double length = GetLength();
      lcd.setCursor(0, 0);
      lcd.print("LEN: ");
      lcd.print(length);
      lcd.print("CM");
    }
    delay(1000);
    lcd.clear();
  }
}