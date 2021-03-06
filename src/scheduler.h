#ifndef scheduler_h
#define scheduler_h

#include "component.h"
#include <Arduino.h>
#include <vector>
#include <memory>

class Scheduler {
	public:
		unsigned setInterval(Component* c, unsigned long interval); // returns task id
		unsigned setTimeout(Component* c, unsigned long timeout);
		void clearInterval(unsigned id);
		void iterate();
		void reset();

	private:
		class Task {
			public:
				Task(Component* compon, unsigned long interval, bool oneshot);

				bool isReady(unsigned long time) const {return time - lastMillis >= interval; }
				void run(unsigned long time);
				void reset(unsigned long time) { lastMillis = time; }
				unsigned getID() const { return id; }
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
		std::vector<std::unique_ptr<Task>> tasks;
		std::vector<unsigned> deadTaskIDs;

		unsigned addTask(Component* c, unsigned long time, bool oneshot);
		void cleanDeadTasks();
};

#endif
