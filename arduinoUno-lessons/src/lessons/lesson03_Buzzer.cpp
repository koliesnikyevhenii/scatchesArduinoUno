#include <Arduino.h>

// Пасивний buzzer: tone() замість ledcWriteTone (пін 11)
//   11 ─── buzzer(+) ... buzzer(−) ─── GND
//   (пасивний buzzer: + на пін 11, − на GND)

#define BUZ 11

int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup() {}

void loop() {
  for (int i = 0; i < 8; i++) {
    tone(BUZ, melody[i]);
    delay(300);
  }
  noTone(BUZ);
  delay(1500);
}
