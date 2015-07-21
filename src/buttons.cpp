#include <EnableInterrupt.h>
#include "buttons.h"

const int pins[] = {11, 12, 15};
constexpr int numButtons = sizeof(pins) / sizeof(pins[0]);

volatile unsigned long Buttons::pushTimes[numButtons] = {};

Buttons::Buttons() {
	enableInterrupt(pins[0], Buttons::onPush0, FALLING);
	enableInterrupt(pins[1], Buttons::onPush1, FALLING);
	enableInterrupt(pins[2], Buttons::onPush2, FALLING);
}

Buttons::~Buttons() {
	for(auto pin : pins) {
		disableInterrupt(pin);
	}
}

void Buttons::reset() {
	for(int i = 0; i != numButtons; ++i) {
		Buttons::pushTimes[i] = 0;
	}
}

void Buttons::onPush(int button) {
	if(!pushTimes[button]) {
		pushTimes[button] = millis();
	}
}
