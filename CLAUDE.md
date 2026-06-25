# CLAUDE.md

Arduino Uno learning sketches, organized as a single PlatformIO project where
each lesson is an isolated, independently-buildable sketch.

## Layout

```
arduinoUno-lessons/
├── platformio.ini              # one [env:*] per lesson + shared [env] base
├── src/lessons/                # one .cpp per lesson (each has its own setup/loop)
│   ├── lesson01_LED.cpp        # blink LED on pin 8
│   ├── lesson02_RGB.cpp        # PWM RGB LED on pins 3/5/6
│   ├── lesson03_Buzzer.cpp     # passive buzzer tone() on pin 11
│   └── lesson04_Button.cpp     # debounced toggle button, pin 2 INPUT_PULLUP -> LED pin 8
└── test/                       # PlatformIO Unity tests, one folder per suite
    ├── test_button_logic/      # pure shouldToggle() debounce logic
    └── test_melody/            # buzzer melody invariants
```

## Build & test

All commands run from `arduinoUno-lessons/`. The `pio` CLI lives at
`%USERPROFILE%\.platformio\penv\Scripts\pio.exe` (not on PATH).

- Build one lesson: `pio run -e lesson04_Button`
- Upload to board: `pio run -e lesson04_Button -t upload`
- Compile tests only (no hardware): `pio test -e lesson04_Button --without-uploading --without-testing`
- Run tests on a connected Uno: `pio test -e lesson04_Button` (add `-f test_melody` for one suite)

## Conventions

- **One sketch per lesson.** Each lesson file is self-contained with its own
  `setup()`/`loop()` and starts with `#include <Arduino.h>`.
- **Per-lesson env.** Every lesson needs a matching block in `platformio.ini`:
  ```ini
  [env:lessonNN_Name]
  build_src_filter = -<*> +<lessons/lessonNN_Name.cpp>
  ```
  The `-<*>` excludes all other lessons so only that one sketch compiles.
- **Shared `[env]`** holds the board (`uno`), framework (`arduino`), and
  `lib_deps`. Note library registry owners differ from the Arduino org —
  e.g. Keypad is `chris--a/Keypad`, not `arduino-libraries/Keypad`.
- `default_envs` takes the bare env name (e.g. `lesson02_RGB`), no `env:` prefix.
- **Testable logic** is extracted into pure functions (see `shouldToggle()` in
  the button test) so it can be unit-tested without pins or timing.
- Wiring is documented as a comment block at the top of each lesson.
