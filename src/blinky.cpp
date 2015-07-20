#include "blinky.h"
#include "scheduler.h"
#include "color.h"

Blinky::Blinky(Scheduler* s, uint16_t x, uint16_t y, uint16_t size, const rgb24& color, unsigned long togglePeriod): sched{s}, x{x}, y{y}, size{size}, togglePeriod{togglePeriod}, state{false}, toggleTaskID{0}, coloringTaskID{0} {
	col = color;
	toggleTaskID = sched->setInterval(this, togglePeriod);
}

void Blinky::setColoring(bool coloring) {
	if(coloring) {
		coloringTaskID = sched->setInterval(this, 5);
	} else {
		sched->clearInterval(coloringTaskID);
	}
}

void Blinky::update(unsigned taskID) {
	if(taskID == toggleTaskID) {
		state = !state;
	} else if(taskID == coloringTaskID) {
			col.red += 5;
			col.green -= 2;
			col.blue += 7;
	}
}

void Blinky::draw(SmartMatrix& matrix) {
	matrix.drawRectangle(x, y, x+size, y+size, state ? col : black);
}

Blinky::~Blinky() {
	sched->clearInterval(toggleTaskID);
	sched->clearInterval(coloringTaskID);
}
