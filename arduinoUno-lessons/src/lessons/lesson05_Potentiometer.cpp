#include <Arduino.h>

#define POT A0
#define LED 3

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() { analogWrite(LED, map(analogRead(POT), 0, 1023, 0, 255)); }