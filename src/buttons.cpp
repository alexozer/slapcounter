#include "buttons.h"
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const int pins[] = {11, 12, 15};
constexpr int numButtons = sizeof(pins) / sizeof(pins[0]);

volatile unsigned long Buttons::pushTimes[numButtons] = {};

Buttons::Buttons() {
	for(auto pin : pins) {
		pinMode(pin, INPUT_PULLUP);
	}
	delayMicroseconds(10);

}

void Buttons::reset() {
	for(int i = 0; i != numButtons; ++i) {
		Buttons::pushTimes[i] = 0;
	}
}

SIGNAL(PCINT0_vect) {
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
			Buttons::setPushTime(i, time);
		}
	}
	SREG = sregBackup;
}
