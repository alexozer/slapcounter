#ifndef slapcounter_h
#define slapcounter_h

#include "scheduler.h"
#include "SmartMatrix_32x32.h"

class SlapCounter {
	public:
		void run();

	private:
		Scheduler sched; // pointer as sched is also owned by components
		SmartMatrix matrix;
};

#endif
