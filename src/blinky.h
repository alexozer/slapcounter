#ifndef blinky_h
#define blinky_h

#include "component.h"
#include "drawing.h"
#include "scheduler.h"
#include <SmartMatrix.h>

class Blinky : public Component, public Drawing {
	public:
		Blinky(Scheduler* s, uint16_t x, uint16_t y, uint16_t size, const rgb24& color, unsigned long togglePeriod);
		void setColoring(bool coloring);
		void update(unsigned reason) override;
		void draw(SmartMatrix& matrix) override;
		~Blinky();

	private:
		Scheduler* sched;
		uint16_t x, y, size;
		unsigned long togglePeriod;
		rgb24 col;
		bool state;
		unsigned toggleTaskID, coloringTaskID;
};

#endif
