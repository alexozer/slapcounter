#include "buttons.h"
#include <Arduino.h>

constexpr int Buttons::pins[];
constexpr unsigned long pollInterval = 10;
constexpr int bounceInterval = 5;

Buttons::Buttons(Scheduler* sched): sched{sched} {
	for(int i = 0; i != numButtons; ++i) {
		pinMode(pins[i], INPUT_PULLUP);
		bounces[i].attach(pins[i]);
		bounces[i].interval(bounceInterval);
	}
	delayMicroseconds(10);

	sched->setInterval(this, pollInterval);
}

void Buttons::update(unsigned) {
	for(auto& b : bounces) {
		b.update();
	}

	for(int i = 0; i != numButtons; ++i) {
		if(bounces[i].fell()) {
			pushTimes[i] = millis();
		}
	}
}

bool Buttons::wasPushed(int button) const {
	return pushedAt(button);
}

unsigned long Buttons::pushedAt(int button) const {
	return pushTimes[button];
}

void Buttons::reset() {
	for(int i = 0; i != numButtons; ++i) {
		Buttons::pushTimes[i] = 0;
	}
}

void Buttons::reset(int button) {
	Buttons::pushTimes[button] = 0;
}
