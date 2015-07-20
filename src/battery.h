#ifndef battery_h
#define battery_h

#include "component.h"
#include "drawing.h"
#include "scheduler.h"
#include "display.h"

class Battery : public Component, public Drawing {
	public:
		Battery(Scheduler* sched, Display* disp);
		void update(unsigned) override;
		void draw(SmartMatrix& matrix) override;
		void setLevel(unsigned l);
		~Battery();

	private:
		Scheduler* sched;
		Display* disp;
		unsigned checkIntervalID;
		bool statusNeedsUpdate;
		unsigned level;

		rgb24 redShade;
		bool redFadeDirection;
		unsigned redFadeID;

		void clearStatus(SmartMatrix& matrix);
		void updateRedShade();
};

#endif
