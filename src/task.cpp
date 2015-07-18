#include <vector>
#include <Arduino.h>

#include "task.h"

unsigned Task::nextID = 0;
std::vector<unsigned> Task::oldIDs;

Task::Task(Component* compon, unsigned long interval)
	:c{compon}, interval{interval}, lastMillis{millis()}
{
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