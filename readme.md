Hq clock for arduino
===

This is a clock library that provides high definition time in a range from microseconds to weeks.

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

Usage
---

Create an HqClock instance in order to call the methods it provides
```
#include <hqclock.h>

#define PIN 13

// create the instance
auto clockInstance = HqClock();

void setup() {
  Serial.begin(9600);
}

void loop()
{
  // update clock time
  clockInstance.update();
  
  // print the amount of microseconds since started
  Serial.println((double) clockInstance.getTime());
}
```
As you can see the instance of the HqClock class needs to be updated at least before calling its other methods.

Also you can extend the HqClock class overriding some of its on* methods

```
#include <hqclock.h>

#define PIN 13

struct SecBlink : HqClock
{
  uint8_t onSecond(long currentDelta) {
    digitalWrite(PIN, getSecondsTotal(currentDelta) % 2);
    return HqClock::onSecond(currentDelta);
  }
};

auto blinkTimer = SecBlink();

void setup() {
  pinMode(PIN, OUTPUT);
}

void loop()
{
  blinkTimer.update();
}

```

In this case you have to update the instance as often as possible in order to have an accurate timing of execution for your onSecond handler
