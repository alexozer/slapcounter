#include "bluetooth.h"
#include "color.h"
#include <vector>
using std::vector;

constexpr int statusLength = 32;
constexpr unsigned long animPeriod = 1000;

const rgb24& statusColor = blue;

Bluetooth::Bluetooth(Scheduler* sched, SmartMatrix* matrix):
	sched{sched},
	matrix{matrix},
	mode{Mode::disconnected},
	animID{0},
	currAnimFrame{0},
	animTimeouts(genAnimTimeouts(statusLength, animPeriod)) {}

vector<unsigned long> Bluetooth::genAnimTimeouts(int statusLength, unsigned long period) {
	vector<unsigned long> timeouts;

	for(double x = 0, lastTimeout = 0; x != statusLength; ++x) {
		double dt = (asin(((x+1)/statusLength*2)-1)/(2*PI)+0.25)*period;
		timeouts.push_back(dt-lastTimeout);
		lastTimeout = dt;
	}

	for(int i = timeouts.size() - 1; i != -1; --i) {
		timeouts.push_back(timeouts[i] + 0); // add 0 so it doesn't act as a reference
	}

	return timeouts;
}

void Bluetooth::clearStatus() {
	matrix->drawFastHLine(0, statusLength - 1, 0, black);
}

void Bluetooth::setMode(Mode mode) {
	if(mode == this->mode) return;
	this->mode = mode;
	clearStatus();

	switch(mode) {
		case Mode::connected:
			matrix->drawPixel(0, 0, statusColor);
			// fallthrough

		case Mode::disconnected:
			matrix->swapBuffers();
			break;

		case Mode::connecting:
			currAnimFrame = 0;
			update(0);
			break;
	}
}

void Bluetooth::update(unsigned) {
	if(mode != Mode::connecting) return;

	clearStatus();

	if(currAnimFrame == 2 * statusLength) {
		currAnimFrame = 0;
	}

	if(currAnimFrame < statusLength) {
		matrix->drawPixel(currAnimFrame, 0, statusColor);
	} else {
		matrix->drawPixel(statusLength - (currAnimFrame - statusLength) - 1, 0, statusColor);
	}

	matrix->swapBuffers();
	sched->setTimeout(this, animTimeouts[currAnimFrame]);
	++currAnimFrame;
}
