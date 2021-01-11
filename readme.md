Hq clock for arduino
===

This library provides a clock with an hq definition from microseconds to weeks.

Each instance of the HqClock class needs to be updated as often as possible
ie by calling its update method in the loop function

Functions
---

these functions can be used for get time information.

- `uint64_t getTime(long delta = 0)` like Arduino's micros() but with 64 bit precision
- `unsigned getMicos(long delta = 0)`
- `uint64_t getMillisTotal(long delta = 0)`
- `unsigned getMillis(long delta = 0)`
- `uint64_t getSecondsTotal(long delta = 0)`
- `uint8_t getSeconds(long delta = 0)`
- `uint64_t getMinutesTotal(long delta = 0)`
- `uint8_t getMinutes(long delta = 0)`
- `uint64_t getHoursTotal(long delta = 0)`
- `uint8_t getHours(long delta = 0)`
- `uint64_t getDaysTotal(long delta = 0)`
- `uint8_t getDays(long delta = 0)`
- `uint8_t getWeeks(long delta = 0)`
- `uint64_t delta(unsigned long curr)` calculate time difference, use it with Arduinio's `micros()`

Functions like getXXXTotal returns the selected intervall of time passed since the clock started.
Functons like getXXX returns the module between the above value and the next intervall.

Handlers
---

You can extend the HqClock class and override these method

- `virtual uint8_t onWeek(long currentDelta)`
- `virtual uint8_t onDay(long currentDelta)`
- `virtual uint8_t onHour(long currentDelta)`
- `virtual uint8_t onMinute(long currentDelta)`
- `virtual uint8_t onSecond(long currentDelta)`
- `virtual uint16_t onMillis(long currentDelta)`



