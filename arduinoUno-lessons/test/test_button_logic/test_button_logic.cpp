#include <Arduino.h>
#include <unity.h>

// ---- Logic under test ----------------------------------------------------
// Pure decision function extracted from lesson04_Button so it can be tested
// without real hardware. Returns true when a press should toggle the state:
// a HIGH->LOW edge that happens after the debounce window.
static bool shouldToggle(int reading, int last, unsigned long now,
                         unsigned long lastChange, unsigned long debounceMs) {
  return reading == LOW && last == HIGH && (now - lastChange) > debounceMs;
}

// ---- Tests ---------------------------------------------------------------
void test_press_edge_after_debounce_toggles(void) {
  // HIGH -> LOW, 60ms after last change, 50ms debounce -> should toggle
  TEST_ASSERT_TRUE(shouldToggle(LOW, HIGH, 1060, 1000, 50));
}

void test_press_within_debounce_ignored(void) {
  // Same edge but only 30ms elapsed -> bounce, ignore
  TEST_ASSERT_FALSE(shouldToggle(LOW, HIGH, 1030, 1000, 50));
}

void test_held_button_does_not_retrigger(void) {
  // Already LOW (held), no new edge -> no toggle
  TEST_ASSERT_FALSE(shouldToggle(LOW, LOW, 2000, 1000, 50));
}

void test_release_does_not_toggle(void) {
  // LOW -> HIGH (release) -> no toggle
  TEST_ASSERT_FALSE(shouldToggle(HIGH, LOW, 2000, 1000, 50));
}

// ---- Runner --------------------------------------------------------------
void setup() {
  delay(2000); // give the serial monitor time to attach
  UNITY_BEGIN();
  RUN_TEST(test_press_edge_after_debounce_toggles);
  RUN_TEST(test_press_within_debounce_ignored);
  RUN_TEST(test_held_button_does_not_retrigger);
  RUN_TEST(test_release_does_not_toggle);
  UNITY_END();
}

void loop() {}
