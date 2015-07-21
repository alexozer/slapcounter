#ifndef scheduler_h
#define scheduler_h

#include <vector>
#include "component.h"

class Scheduler {
	public:
		unsigned setInterval(Component* c, unsigned long interval); // returns task id
		unsigned setTimeout(Component* c, unsigned long timeout);
		void clearInterval(unsigned id);
		void iterate();
		void reset();

	private:
		class Task;
		std::vector<Task> tasks;
		std::vector<unsigned> deadTaskIDs;

		unsigned addTask(Component* c, unsigned long time, bool oneshot);
		void cleanDeadTasks();
};

#endif
