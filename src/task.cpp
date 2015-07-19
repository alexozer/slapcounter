#include <vector>
#include <Arduino.h>

#include "task.h"

unsigned Task::nextID = 1; // 0 is reserved as null
std::vector<unsigned> Task::oldIDs;

Task::Task(Component* compon, unsigned long interval, bool oneshot)
	:c{compon}, interval{interval}, lastMillis{millis()}, oneshot{oneshot} {
	if(oldIDs.size() == 0) {
		id = nextID++;
	} else {
		id = oldIDs.back();
		oldIDs.pop_back();
	}
}

void Task::run() {
	reset();
	c->update(id);
}
