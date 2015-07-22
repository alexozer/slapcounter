#include "slapcounter.h"
#include "blinky.h"
#include <Arduino.h>

SlapCounter sc;

SlapCounter::SlapCounter(): disp(&sched) {}

void SlapCounter::run() {
	Blinky b0(&sched, 0, 0, 10, rgb24{127, 0, 127}, 250),
		   b1(&sched, 4, 4, 15, rgb24{0, 127, 255}, 750),
		   b2(&sched, 21, 21, 10, rgb24{255, 127, 0}, 82),
		   b3(&sched, 0, 30, 1, rgb24{0, 255, 0}, 400);

	b1.setColoring(true);

	disp.addDrawing(&b0);
	disp.addDrawing(&b1);
	disp.addDrawing(&b2);
	disp.addDrawing(&b3);

	while(true) {
		sched.iterate();
	}
}

int main() {
	sc.run();
}

