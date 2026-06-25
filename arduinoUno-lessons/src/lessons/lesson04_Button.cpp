#include <Arduino.h>

// Кнопка-перемикач (пін 2, INPUT_PULLUP) з антидребезгом
//   2 ─── button ─── GND   (INPUT_PULLUP: натиснуто = LOW)
//   8 ─── LED(+) ... LED(−) ─── GND

#define BTN 2
#define LED 8

bool on = false;
int last = HIGH;
unsigned long tc = 0;

void setup() {
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  int r = digitalRead(BTN);
  if (r == LOW && last == HIGH && millis() - tc > 50) {
    on = !on;
    digitalWrite(LED, on);
    tc = millis();
  }
  last = r;
}
