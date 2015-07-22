#include "buttons.h"
#include <Arduino.h>

const int pins[] = {11, 12, 15};
constexpr int numButtons = sizeof(pins) / sizeof(pins[0]);

volatile unsigned long Buttons::pushTimes[numButtons] = {};

Buttons::Buttons() {
	for(auto pin : pins) {
		pinMode(pin, INPUT_PULLUP);
		attachInterrupt(pin, Buttons::isr, FALLING);
	}
	delayMicroseconds(10);
}

Buttons::~Buttons() {
	for(auto pin : pins) {
		detachInterrupt(pin);
	}
}

void Buttons::reset() {
	for(int i = 0; i != numButtons; ++i) {
		Buttons::pushTimes[i] = 0;
	}
}

void Buttons::isr() {
	// read pin state as early as possible
	static bool pinState[numButtons];
	for(int i = 0; i != numButtons; ++i) {
		pinState[i] = digitalRead(pins[i]);
	}

	unsigned long time = millis();
	auto sregBackup = SREG;
	cli();
	for(int i = 0; i != numButtons; ++i) {
		if(pinState[i]) {
			pushTimes[i] = time;
		}
	}
	SREG = sregBackup;
}
