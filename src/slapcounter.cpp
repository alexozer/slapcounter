#include "slapcounter.h"
#include <Arduino.h>

void SlapCounter::run() {
	while(true) {
		sched.iterate();
	}
}
