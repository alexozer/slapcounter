#ifndef display_h
#define display_h

#include <vector>

#include "component.h"
#include "scheduler.h"
#include "drawing.h"

class Display : public Component {
	public:
		Display(Scheduler* s);
		void update(unsigned taskID) override;
		void addDrawing(Drawing* d);
		void removeDrawing(Drawing* d);
		~Display() { sched->removeTask(drawTaskID); }

	private:
		SmartMatrix mat;
		unsigned drawTaskID;
		Scheduler* sched;
		std::vector<Drawing*> drawings;
};

#endif
