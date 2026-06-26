#include <Arduino.h>
#include <DHT.h>

// Lesson 06 - Light sensor night-light + DHT11 temperature/humidity
//
// Wiring:
//   Photoresistor (LDR) module AO -> A0
//   Relay module IN              -> pin 8  (active LOW)
//   DHT11 DATA                   -> pin 4
//   All modules: VCC -> 5V, GND -> GND

// --- піни ---
const int PIN_LDR   = A0;   // AO фоторезистора (аналог 0..1023)
const int PIN_RELAY = 8;    // IN реле (активне LOW)
const int PIN_DHT   = 4;    // DATA DHT11

#define DHT_TYPE DHT11
DHT dht(PIN_DHT, DHT_TYPE);

// --- налаштування ---
const int  DARK_THRESHOLD = 300;  // більше = темніше (підбери під приміщення)
const int  HYSTERESIS     = 50;   // щоб реле не "дрижало" на межі
const unsigned long DHT_INTERVAL = 2000;  // DHT11 не частіше 1 раз/2с

bool lightOn = false;
unsigned long lastDht = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, HIGH);  // HIGH = вимкнено (реле активне LOW)
  dht.begin();
  Serial.println(F("Старт: нічник + DHT11"));
}

void loop() {
  int ldr = analogRead(PIN_LDR);   // 0..1023

  // гістерезис: вмикаємо коли темно, вимикаємо коли стало світліше

  if (!lightOn && ldr > DARK_THRESHOLD + HYSTERESIS) {
    lightOn = true;
    digitalWrite(PIN_RELAY, LOW);   // LOW = увімкнено
  } else if (lightOn && ldr < DARK_THRESHOLD - HYSTERESIS) {
    lightOn = false;
    digitalWrite(PIN_RELAY, HIGH);  // HIGH = вимкнено
  }

  // DHT11 читаємо рідше, щоб не блокувати логіку світла
  unsigned long now = millis();
  if (now - lastDht >= DHT_INTERVAL) {
    lastDht = now;
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    Serial.print(F("LDR=")); Serial.print(ldr);
    Serial.print(F("  Light=")); Serial.print(lightOn ? F("ON") : F("OFF"));
    if (isnan(t) || isnan(h)) {
      Serial.println(F("  DHT11: помилка читання"));
    } else {
      Serial.print(F("  T=")); Serial.print(t, 1); Serial.print(F("C"));
      Serial.print(F("  H=")); Serial.print(h, 0); Serial.println(F("%"));
    }
  }

  delay(50);
}
