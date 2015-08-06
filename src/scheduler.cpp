#include "scheduler.h"
#include <Arduino.h>
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

unsigned Scheduler::Task::nextID = 1; // 0 is reserved as null
std::vector<unsigned> Scheduler::Task::oldIDs;

Scheduler::Task::Task(Component* compon, unsigned long interval, bool oneshot)
	:c{compon}, interval{interval}, lastMillis{millis()}, oneshot{oneshot} {
	if(oldIDs.size() == 0) {
		id = nextID++;
	} else {
		id = oldIDs.back();
		oldIDs.pop_back();
	}
}

void Scheduler::Task::run(unsigned long time) {
	reset(time);
	c->update(id);
}

unsigned Scheduler::setInterval(Component* c, unsigned long interval) {
	return addTask(c, interval, false);
}

unsigned Scheduler::setTimeout(Component* c, unsigned long timeout) {
	return addTask(c, timeout, true);
}

unsigned Scheduler::addTask(Component* c, unsigned long interval, bool oneshot) {
	tasks.push_back(unique_ptr<Task>(new Task(c, interval, oneshot)));

	return tasks.back()->getID();
}

void Scheduler::clearInterval(unsigned id) {
	deadTaskIDs.push_back(id);
}

void Scheduler::iterate() {
	cleanDeadTasks();

	// don't execute until all tasks ready NOW have been found
	static vector<vector<Task>::size_type> readyTaskIs;
	auto time = millis();
	for(vector<Task>::size_type i = 0; i != tasks.size(); ++i) {
		if(tasks[i]->isReady(time)) {
			readyTaskIs.push_back(i);
		}
	}

	for(auto i : readyTaskIs) {
		tasks[i]->run(time);
	}

	for(auto metaIt = readyTaskIs.rbegin(); metaIt != readyTaskIs.rend(); ++metaIt) {
		if(tasks[*metaIt]->isOneshot()) {
			tasks.erase(tasks.begin() + *metaIt);
		}
	}
	readyTaskIs.clear();
}

void Scheduler::reset() {
	auto time = millis();
	for(auto &t : tasks) {
		t->reset(time);
	}
}

void Scheduler::cleanDeadTasks() {
	for(auto id : deadTaskIDs) {
		auto it = tasks.begin();
		while(it != tasks.end()) {
			if((*it)->getID() == id) break;
			++it;
		}

		if(it != tasks.end()) {
			tasks.erase(it);
		}
	}
	deadTaskIDs.clear();
}
