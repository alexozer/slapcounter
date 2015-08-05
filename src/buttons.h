#ifndef buttons_h
#define buttons_h

#include "component.h"
#include "scheduler.h"
#define BOUNCE_LOCK_OUT
#include "Bounce2.h"
#include <Arduino.h>

class Buttons : public Component {

	public:
		Buttons(Scheduler* sched);

		void update(unsigned) override;
		bool wasPushed(int button) const;
		unsigned long pushedAt(int button) const;
		void reset();
		void reset(int button);

	private:
		Scheduler* sched;

		static constexpr int pins[] = {11, 12, 15};
		static constexpr int numButtons = sizeof(pins) / sizeof(pins[0]);

		unsigned long pushTimes[numButtons];
		Bounce bounces[numButtons];
};

#endif
