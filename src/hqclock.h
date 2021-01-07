#ifndef __HQCLOCK
#define __HQCLOCK

#include <Arduino.h>

#ifdef ARDUINO_AVR_NANO
const long MICROSECONDS = 1002;
#else
const long MICROSECONDS = 1000;
#endif

struct HqClock
{
	unsigned long low = 0;
	unsigned long high = 0;

	uint64_t getTime(long delta = 0) {
		return (((uint64_t) high + (low > (low + delta))) << 32) | (low + delta);
	}

	unsigned getMicos(long delta = 0) {
		return getTime(delta) % MICROSECONDS;
	}

	uint64_t getMillisTotal(long delta = 0){
		return getTime(delta) / MICROSECONDS;
	}

	unsigned getMillis(long delta = 0){
		return getMillisTotal(delta) % 1000;
	}

	uint64_t getSecondsTotal(long delta = 0){
		return getMillisTotal(delta) / 1000;
	}

	uint8_t getSeconds(long delta = 0){
		return getSecondsTotal(delta) % 60;
	}

	uint64_t getMinutesTotal(long delta = 0){
		return getSecondsTotal(delta) / 60;
	}

	uint8_t getMinutes(long delta = 0){
		return getMinutesTotal(delta) % 60;
	}

	uint64_t getHoursTotal(long delta = 0){
		return (getMinutesTotal(delta) / 60);
	}

	uint8_t getHours(long delta = 0){
		return getHoursTotal(delta) % 24;
	}

	uint64_t getDaysTotal(long delta = 0){
		return getHoursTotal(delta) / 24;
	}

	uint8_t getDays(long delta = 0){
		return getDaysTotal(delta) % 7;
	}

	uint8_t getWeeks(long delta = 0){
		return getDaysTotal(delta) / 7;
	}

	uint64_t delta(unsigned long curr) {
		return getTime(curr - low) - getTime();
	}

	virtual uint8_t onWeek(long currentDelta){
		return getWeeks(currentDelta);
	}

	virtual uint8_t onDay(long currentDelta){
		auto d = getWeeks(currentDelta) - getWeeks();
		if(d){
			onWeek(currentDelta);
		}
		return d;
	}

	virtual uint8_t onHour(long currentDelta){
		auto d = getDaysTotal(currentDelta) - getDaysTotal();
		if(d){
			onDay(currentDelta);
		}
		return d;
	}

	virtual uint8_t onMinute(long currentDelta){
		auto d = getHoursTotal(currentDelta) - getHoursTotal();
		if(d){
			onHour(currentDelta);
		}
		return d;
	}

	virtual uint8_t onSecond(long currentDelta){
		auto d = getMinutesTotal(currentDelta) - getMinutesTotal();
		if(d){
			onMinute(currentDelta);
		}
		return d;
	}

	virtual uint16_t onMillis(long currentDelta){
		auto d = getSecondsTotal(currentDelta) - getSecondsTotal();
		if(d){
			onSecond(currentDelta);
		}
		return d;
	}

	virtual uint64_t update() {
		auto currentDelta = delta(micros());
		auto d = getMillisTotal(currentDelta) - getMillisTotal();
		if(d) {
			onMillis(currentDelta);
		}
		auto t = getTime(currentDelta);
		high = t >> 32;
		low = (unsigned long) t;
		return d;
	}
};

#endif


