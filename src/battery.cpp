#include <SmartMatrix.h>
#include "battery.h"

constexpr unsigned matrixSize = 32;
constexpr unsigned long checkInterval = 10000;
constexpr unsigned batteryCap = 6;

constexpr unsigned redFadeInterval = 1000/60; // about 60fps

const rgb24 blankColor = {0, 0, 0};
const rgb24 redColor = {255, 0, 0};
const rgb24 dimRedColor = {127, 0, 0};
const rgb24 greenColor = {0, 255, 0};

Battery::Battery(Scheduler* sched, Display* disp):
	sched{sched}, disp{disp}, statusNeedsUpdate{true},
	level{0}, redFadeDirection{false}, redFadeID{0} {

	redShade = redColor;
	checkIntervalID = sched->setInterval(this, checkInterval);
	disp->addDrawing(this);
}

void Battery::update(unsigned intervalID) {
	if(intervalID == checkIntervalID) {
		// check battery level here

		if(level <= 1) {
			redFadeID = sched->setInterval(this, redFadeInterval);
		} else {
			sched->clearInterval(redFadeID);
			redFadeID = 0;
		}
	} else if(intervalID == redFadeID) {
		updateRedShade();
	}

	statusNeedsUpdate = true;
}

void Battery::updateRedShade() {
	if(redFadeDirection) {
		if(redShade.red == redColor.red) {
			redFadeDirection = false;
		}
	} else {
		if(redShade.red == dimRedColor.red) {
			redFadeDirection = true;
		}
	}

	if(redFadeDirection) {
		++redShade.red;
	} else {
		--redShade.red;
	}
}

void Battery::draw(SmartMatrix& matrix) {
	if(!statusNeedsUpdate) return;

	clearStatus(matrix);
	if(level <= 1) {
		matrix.drawPixel(matrixSize - 1, 0, redShade);
	} else {
		matrix.drawFastHLine(matrixSize - level, matrixSize - 1, 0, greenColor);
	}

	statusNeedsUpdate = false;
};

void Battery::clearStatus(SmartMatrix& matrix) {
	matrix.drawFastHLine(matrixSize - batteryCap, matrixSize - 1, 0, blankColor);
}

void Battery::setLevel(unsigned l) {
	level = l;
}

Battery::~Battery() {
	sched->clearInterval(checkIntervalID);
	disp->removeDrawing(this);
}
