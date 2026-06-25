#include <Arduino.h>
#include <unity.h>

// Melody from lesson03_Buzzer (C-major scale, Hz).
static int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
static const int melodyLen = sizeof(melody) / sizeof(melody[0]);

void test_melody_has_eight_notes(void) {
  TEST_ASSERT_EQUAL_INT(8, melodyLen);
}

void test_melody_is_ascending(void) {
  for (int i = 1; i < melodyLen; i++) {
    TEST_ASSERT_TRUE_MESSAGE(melody[i] > melody[i - 1], "notes must rise");
  }
}

void test_notes_are_audible_range(void) {
  // tone() on an Uno is reliable roughly 31 Hz .. a few kHz
  for (int i = 0; i < melodyLen; i++) {
    TEST_ASSERT_GREATER_THAN_INT(31, melody[i]);
    TEST_ASSERT_LESS_THAN_INT(5000, melody[i]);
  }
}

void setup() {
  delay(2000);
  UNITY_BEGIN();
  RUN_TEST(test_melody_has_eight_notes);
  RUN_TEST(test_melody_is_ascending);
  RUN_TEST(test_notes_are_audible_range);
  UNITY_END();
}

void loop() {}
