#include <vector>
using std::vector;
#include <cmath>

#include "bluetooth.h"

constexpr int statusLength = 6;
constexpr unsigned long animPeriod = 1000;
const rgb24 blankColor = {0, 0, 0},
	  statusColor = {0, 0, 255};

vector<unsigned long> genAnimTimeouts(int statusLength, unsigned long period) {
	vector<unsigned long> timeouts;

	double lastTimeout = 0;
	for(double x = 0; x != statusLength; ++x) {
		double dt = std::acos(((x+1)/statusLength*2)-1)/(2*PI)*period;
		timeouts.push_back(dt-lastTimeout);
		lastTimeout = dt;
	}

	double halfPeriod = period / 2;
	for(auto it = timeouts.crbegin(); it != timeouts.crend(); ++it) {
		timeouts.push_back(*it + halfPeriod);
	}

	return timeouts;
}

const vector<unsigned long> animTimeouts = genAnimTimeouts(statusLength, animPeriod);

void Bluetooth::clearStatus(SmartMatrix& matrix) {
	matrix.drawFastHLine(0, statusLength - 1, 0, blankColor);
}

void Bluetooth::setMode(Mode m) {
	mode = m;
	statusNeedsUpdate = true;

	if(m == Mode::connecting) {
		currAnimFrame = 0; 
		update(0);
	}
}

void Bluetooth::update(unsigned taskID) {
	if(mode != Mode::connecting) return;

	sched->setTimeout(this, animTimeouts[currAnimFrame++]);
	if(currAnimFrame == 2 * statusLength) currAnimFrame = 0;

	statusNeedsUpdate = true;
}

void Bluetooth::draw(SmartMatrix& matrix) {
	if(!statusNeedsUpdate) return;

	clearStatus(matrix);

	switch(mode) {
		case Mode::disconnected:
			break;

		case Mode::connected:
			matrix.drawPixel(0, 0, statusColor);
			break;

		case Mode::connecting:
			if(currAnimFrame < statusLength) {
				matrix.drawPixel(currAnimFrame, 0, statusColor);
			} else {
				matrix.drawPixel(statusLength - (currAnimFrame - statusLength) - 1);
			}
			break;
	}

	statusNeedsUpdate = false;
}
