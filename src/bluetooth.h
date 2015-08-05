#ifndef bluetooth_h
#define bluetooth_h

#include "component.h"
#include "scheduler.h"
#include "SmartMatrix_32x32.h"

class Bluetooth : public Component {
	public:
		enum class Mode { disconnected, connecting, connected };

		Bluetooth(Scheduler* sched, SmartMatrix* matrix); 
		void setMode(Mode m);
		void update(unsigned) override;

	private:
		Scheduler* sched;
		SmartMatrix* matrix;

		Mode mode;

		unsigned animID;
		int currAnimFrame;
		std::vector<unsigned long> animTimeouts;

		std::vector<unsigned long> genAnimTimeouts(int statusLength, unsigned long period);
		void clearStatus();
};

#endif
