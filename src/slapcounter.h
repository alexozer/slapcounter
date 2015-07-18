#ifndef slapcounter_h
#define slapcounter_h

#include "scheduler.h"
#include "display.h"
#include "blinky.h"

class SlapCounter {
	public:
		SlapCounter();
		void run();

	private:
		Scheduler sched; // pointer as sched is also owned by components
		Display disp;
};

#endif
