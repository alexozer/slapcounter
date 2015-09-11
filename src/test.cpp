#include "test.h"

#include "scheduler.h"
#include "buttons.h"
#include "color.h"
#include "bluetooth.h"
#include "session.h"

#include "SmartMatrix_32x32.h"
#include <Arduino.h>
#include <vector>
using std::vector;

Scheduler sched;
SmartMatrix matrix;

void initMatrix() {
	matrix.begin();
	matrix.setBrightness(7);
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

void testBigFont() {
	Serial.println("testing big font");

	matrix.drawString(2, 2, green, "04", 4);
	matrix.drawString(0, 27, blue, "5:11");
	matrix.drawString(17, 27, blue, "5:11");

	matrix.swapBuffers();
}

void testSession() {
	Serial.println("testing session");

	Buttons buttons(&sched);
	Session session(&sched, &matrix, &buttons, nullptr);
	session.begin();
	Serial.println("initialized session");
	while(true) { sched.iterate(); }
}

void runTests() {
	Serial.begin(9600);
	initMatrix();
	//wait();

	//blink();
	//testButtons();
	//testBluetooth();
	//testBigFont();
	testSession();
}
