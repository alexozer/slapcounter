#include "battery.h"
#include "color.h"
#include "SmartMatrix_32x32.h"

constexpr unsigned matrixSize = 32;
constexpr unsigned long checkInterval = 10000;
constexpr unsigned batteryCap = 6;

constexpr unsigned redFadeInterval = 1000/60; // about 60fps

const rgb24 dimRed = {127, 0, 0};

Battery::Battery(Scheduler* sched, SmartMatrix* matrix):
	sched{sched},
	matrix{matrix},
	level{0},
	redFadeDirection{false},
	redFadeID{0} {

	redShade = red;
	checkIntervalID = sched->setInterval(this, checkInterval);
}

void Battery::update(unsigned intervalID) {
	clearStatus();

	if(intervalID == checkIntervalID) {
		// TODO check battery level here
		
		if(level > 1) {
			sched->clearInterval(redFadeID);
			redFadeID = 0;
			matrix->drawFastHLine(matrixSize - level, matrixSize - 1, 0, green);
			matrix->swapBuffers();
		} else {
			if(redFadeID == 0) {
				redFadeID = sched->setInterval(this, redFadeInterval);
			}
		}
	} else if(intervalID == redFadeID) {
		updateRedShade();
	}
}

void Battery::updateRedShade() {
	if(redFadeDirection) {
		if(redShade.red == red.red) {
			redFadeDirection = false;
		}
	} else {
		if(redShade.red == dimRed.red) {
			redFadeDirection = true;
		}
	}

	if(redFadeDirection) {
		redShade.red += 4;
	} else {
		redShade.red -= 4;
	}

	matrix->drawPixel(matrixSize - 1, 0, redShade);
	matrix->swapBuffers();
}

void Battery::clearStatus() {
	matrix->drawFastHLine(matrixSize - batteryCap, matrixSize - 1, 0, black);
}

void Battery::setLevel(unsigned l) {
	level = l;
	update(checkIntervalID);
}

Battery::~Battery() {
	sched->clearInterval(checkIntervalID);
	sched->clearInterval(redFadeID);
}
