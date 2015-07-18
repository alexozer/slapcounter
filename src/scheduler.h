#ifndef scheduler_h
#define scheduler_h

#include <vector>

#include "component.h"
#include "task.h"

class Scheduler {
	public:
		unsigned setInterval(Component* c, unsigned long interval); // returns task id
		void clearInterval(unsigned id);
		void iterate();
		void reset();

	private:
		std::vector<Task> tasks;
};

#endif
