#ifndef battery_h
#define battery_h

#include "component.h"
#include "scheduler.h"
#include "SmartMatrix_32x32.h"

class Battery : public Component {
	public:
		Battery(Scheduler* sched, SmartMatrix* matrix);
		void update(unsigned) override;
		void setLevel(unsigned l);
		~Battery();

	private:
		Scheduler* sched;
		SmartMatrix* matrix;
		unsigned checkIntervalID;
		unsigned level;

		rgb24 redShade;
		bool redFadeDirection;
		unsigned redFadeID;

		void clearStatus();
		void updateRedShade();
};

#endif
