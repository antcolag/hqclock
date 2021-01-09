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
