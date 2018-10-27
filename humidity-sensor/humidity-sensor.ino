#include <Arduino.h>

#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22
#define LDRPIN 0
#define RLED 13
#define YLED 12
#define GLED 11
#define BRIGHT 2
#define DIM 1
#define DARK 0

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(LDRPIN, INPUT);
  pinMode(RLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);

  digitalWrite(RLED, LOW);
  digitalWrite(YLED, LOW);
  digitalWrite(GLED, LOW);
}

void loop() {
  int lval   = analogRead(LDRPIN);
  int light  = DARK;
  float hum  = dht.readHumidity();
  float temp = dht.readTemperature();

  delay(2000);

  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (isnan(lval)) {
    Serial.println("Failed to read from photocell!");
    return;
  }

  if (lval >= 900) {
    light = DARK;
  } else if (light >= 700) {
    light = DIM;
  } else {
    light = BRIGHT;
  }

  if (light != DARK) {
    if (temp <= 20) {
      digitalWrite(RLED, LOW);
      digitalWrite(YLED, LOW);
      digitalWrite(GLED, HIGH);
    } else if (temp <= 25) {
      digitalWrite(RLED, LOW);
      digitalWrite(YLED, HIGH);
      digitalWrite(GLED, LOW);
    } else {
      digitalWrite(RLED, HIGH);
      digitalWrite(YLED, LOW);
      digitalWrite(GLED, LOW);
    }
  } else {
      digitalWrite(RLED, LOW);
      digitalWrite(YLED, LOW);
      digitalWrite(GLED, LOW);
  }

  Serial.print("l:");
  Serial.print(light);
  Serial.print("::h:");
  Serial.print(hum);
  Serial.print("::t:");
  Serial.println(temp);
}
