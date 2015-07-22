#include "display.h"
#include "scheduler.h"
#include <SmartMatrix.h>
#include <algorithm>

constexpr unsigned long drawInterval = 1000 / 60; // roughly 60fps

Display::Display(Scheduler* s): sched{s} {
	mat.begin();
	mat.setBrightness(10);
	drawTaskID = s->setInterval(this, drawInterval);
}

void Display::update(unsigned taskID) {
	if(taskID != drawTaskID) return;

	for(auto d : drawings) {
		d->draw(mat);
	}
	mat.swapBuffers();
}

void Display::addDrawing(Drawing* d) {
	drawings.push_back(d);
}

void Display::removeDrawing(Drawing* d) {
	auto it = std::find(drawings.begin(), drawings.end(), d);
	if(it != drawings.end()) {
		drawings.erase(it);
	}
}
