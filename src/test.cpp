#include "test.h"

#include "scheduler.h"
#include "buttons.h"
#include "color.h"
#include "bluetooth.h"

#include "SmartMatrix_32x32.h"
#include <Arduino.h>
#include <vector>
using std::vector;

Scheduler sched;
SmartMatrix matrix;

void initMatrix() {
	matrix.begin();
	matrix.setBrightness(2);
}

void wait() {
	while(!Serial.available());
	while(Serial.read() != -1);
}

void blink() {
	constexpr int pin = 13;
	pinMode(pin, OUTPUT);
	while(true) {
		digitalWrite(pin, HIGH);
		Serial.println("LED on");
		delay(100);

		digitalWrite(pin, LOW);
		Serial.println("LED off");
		delay(100);
	}
}

void testButtons() {
	Serial.println("testing buttons polling");

	Buttons buttons(&sched);

	const rgb24 colors[] = {red, green, blue};

	while(true) {
		sched.iterate();
		for(int i = 0; i != 3; ++i) {
			if(buttons.wasPushed(i)) {
				Serial.print("Button ");
				Serial.print(i);
				Serial.print(" pushed at ");
				Serial.print(buttons.pushedAt(i));
				Serial.println(" milliseconds");

				matrix.fillScreen(colors[i]);
				matrix.swapBuffers();
				buttons.reset(i);
			}
		}
	}
}

void testBluetooth() {
	Serial.println("testing bluetooth");

	Bluetooth bt(&sched, &matrix);
	Buttons buttons(&sched);

	while(true) {
		sched.iterate();

		if(buttons.wasPushed(0)) {
			bt.setMode(Bluetooth::Mode::disconnected);
			buttons.reset(0);
		} else if(buttons.wasPushed(1)) {
			bt.setMode(Bluetooth::Mode::connecting);
			buttons.reset(1);
		} else if(buttons.wasPushed(2)) {
			bt.setMode(Bluetooth::Mode::connected);
			buttons.reset(2);
		}
	}
}

void runTests() {
	Serial.begin(9600);
	initMatrix();
	//wait();

	//blink();
	//testButtons();
	testBluetooth();
}
