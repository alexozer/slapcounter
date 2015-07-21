#include <vector>
using std::vector;
#include <Arduino.h>

#include "scheduler.h"

class Scheduler::Task {
	public:
		Task(Component* compon, unsigned long interval, bool oneshot);

		bool isReady() const {return millis() - lastMillis >= interval; }
		void run();
		unsigned getID() const { return id; }
		void reset() {lastMillis = millis(); }
		bool isOneshot() const { return oneshot; }

		~Task() {oldIDs.push_back(id);}

	private:
		unsigned id;
		Component* c;

		unsigned long interval;
		unsigned long lastMillis;
		bool oneshot;

		static unsigned nextID;
		static std::vector<unsigned> oldIDs;
};

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

void Scheduler::Task::run() {
	reset();
	c->update(id);
}

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
	deadTaskIDs.push_back(id);
}

void Scheduler::iterate() {
	cleanDeadTasks();

	// don't execute until all tasks ready NOW have been found
	static vector<vector<Task>::iterator> readyTaskIts;
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

void Scheduler::cleanDeadTasks() {
	for(auto id : deadTaskIDs) {
		auto it = tasks.begin();
		while(it != tasks.end()) {
			if(it->getID() == id) break;
			++it;
		}

		if(it != tasks.end()) {
			tasks.erase(it);
		}
	}
	deadTaskIDs.clear();
}
