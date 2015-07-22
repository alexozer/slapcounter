#include "buttons.h"
#include <Arduino.h>

const int pins[] = {11, 12, 15};
constexpr int numButtons = sizeof(pins) / sizeof(pins[0]);

volatile unsigned long Buttons::pushTimes[numButtons] = {};

Buttons::Buttons() {
	for(auto pin : pins) {
		pinMode(pin, INPUT_PULLUP);
	}
	delayMicroseconds(10);

	attachInterrupt(pins[0], Buttons::onPush0, FALLING);
	attachInterrupt(pins[1], Buttons::onPush1, FALLING);
	attachInterrupt(pins[2], Buttons::onPush2, FALLING);
}

Buttons::~Buttons() {
	for(auto pin : pins) {
		detachInterrupt(pin);
	}
}

bool Buttons::wasPushed(int button) const {
	return pushedAt(button);
}

unsigned long Buttons::pushedAt(int button) const {
	auto sregBackup = SREG;
	noInterrupts();
	unsigned long time = pushTimes[button];
	SREG = sregBackup;

	return time;
}

void Buttons::reset() {
	auto sregBackup = SREG;
	noInterrupts();

	for(int i = 0; i != numButtons; ++i) {
		Buttons::pushTimes[i] = 0;
	}

	SREG = sregBackup;
}

void Buttons::onPush(int button) {
	if(!pushTimes[button]) {
		pushTimes[button] = millis();
	}
}
