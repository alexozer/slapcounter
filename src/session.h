#ifndef session_h
#define session_h

#include "component.h"
#include "buttons.h"
#include "scheduler.h"
#include "storage.h"
#include "SmartMatrix_32x32.h"
#include <vector>

class Session : public Component {

	public:
		Session(Scheduler* sched, SmartMatrix* matrix, Buttons* buttons, Storage* stor);
		~Session();
		
		void begin(int lapGoal);
		void update(unsigned) override;

	private:
		Scheduler* sched;
		SmartMatrix* matrix;
		Buttons* buttons;
		Storage* stor;

		int lapGoal;
		int currLap;

		unsigned bpushTaskID;

		unsigned long lastTime; // in milliseconds
		std::vector<uint16_t> lapTimes; // in centiseconds

		enum class Mode { ready, active };
		Mode mode;

		uint16_t millisToCentis(unsigned long millis);
		void drawLapCount();
		void drawLapTime();
};

#endif
