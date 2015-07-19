#include <vector>
using std::vector;
#include <Arduino.h>

#include "scheduler.h"
#include "task.h"

unsigned Scheduler::setInterval(Component* c, unsigned long interval) {
	return addTask(c, interval, false);
}

unsigned Scheduler::setTimeout(Component* c, unsigned long timeout) {
	return addTask(c, timeout, true);
}

unsigned Scheduler::addTask(Component* c, unsigned long interval, bool oneshot) {
	tasks.push_back(Task(c, interval, oneshot));

	return tasks.back().getID();
}

void Scheduler::clearInterval(unsigned id) {
	auto it = tasks.begin();
	while(it != tasks.end()) {
		if(it->getID() == id) break;
		++it;
	}

	if(it != tasks.end()) {
		tasks.erase(it);
	}
}

void Scheduler::iterate() {
	static vector<vector<Task>::iterator> readyTaskIts;

	// don't execute until all tasks ready NOW have been found
	for(auto it = tasks.begin(); it != tasks.end(); ++it) {
		if(it->isReady()) {
			readyTaskIts.push_back(it);
		}
	}

	for(auto &it : readyTaskIts) {
		it->reset();
		it->run();
	}

	for(auto metaIt = readyTaskIts.rbegin(); metaIt != readyTaskIts.rend(); ++metaIt) {
		if((*metaIt)->isOneshot()) {
			tasks.erase(*metaIt);
		}
	}

	readyTaskIts.clear();
}

void Scheduler::reset() {
	for(auto &t : tasks) {
		t.reset();
	}
}
