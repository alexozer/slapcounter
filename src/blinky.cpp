#include "blinky.h"
#include "scheduler.h"

const rgb24 blankColor = {0, 0, 0};

Blinky::Blinky(Scheduler* s, uint16_t x, uint16_t y, uint16_t size, const rgb24& color, unsigned long togglePeriod): sched{s}, x{x}, y{y}, size{size}, togglePeriod{togglePeriod}, state{false}, toggleTaskID{-1}, coloringTaskID{-1} {
	col = color;
	toggleTaskID = sched->setInterval(this, togglePeriod);
}

void Blinky::setColoring(bool coloring) {
	if(coloring) {
		coloringTaskID = sched->setInterval(this, 5);
	} else {
		sched->removeTask(coloringTaskID);
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
	matrix.drawRectangle(x, y, x+size, y+size, state ? col : blankColor);
}

Blinky::~Blinky() {
	sched->removeTask(toggleTaskID);
	sched->removeTask(coloringTaskID);
}
