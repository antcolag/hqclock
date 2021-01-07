#include <hqclock.h>

#define PIN 13

struct SecBlink : HqClock
{
  uint8_t onSecond(long currentDelta = 0) {
    digitalWrite(PIN, getSecondsTotal() % 2);
    return HqClock::onSecond(currentDelta);
  }
};

auto blink = SecBlink();

void setup() {
  pinMode(PIN, OUTPUT)
}

void loop()
{
  blink.update();
}
