#include <Arduino.h>

int pulseSpeed = 5;
int ldrPin = 0;
int redLed = 11;
int greenLed = 10;
int blueLed = 9;

int ambientLite;
int power = 150;

float RGB[3];
float CommonMathVariable = 180/PI;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
}

void loop() {
  for (float x = 0; x < PI; x = x + 0.00001) {
    RGB[0] = power * abs(sin(x * (CommonMathVariable)));
    RGB[1] = power * abs(sin((x + PI/3) * (CommonMathVariable)));
    RGB[2] = power * abs(sin((x + (2 * PI) / 3) * (CommonMathVariable)));
    ambientLite = analogRead(ldrPin);

    if (ambientLite > 600) {
      analogWrite(redLed, RGB[0]);
      analogWrite(blueLed, RGB[1]);
      analogWrite(greenLed, RGB[2]);
    } else {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, LOW);
      digitalWrite(blueLed, LOW);
    }

    for (int i = 0; i < 3; i++) {
      if (RGB[i] < 1) {
        delay (20 * pulseSpeed);
      } else if (RGB[i] < 5) {
        delay (10 * pulseSpeed);
      } else if (RGB[i] < 10) {
        delay (2 * pulseSpeed);
      } else if (RGB[i] < 100) {
        delay (1 * pulseSpeed);
      }

      delay(1);
    }
  }
}
