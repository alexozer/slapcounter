#ifndef bluetooth_h
#define bluetooth_h

#include "component.h"
#include "drawing.h"
#include "scheduler.h"
#include "display.h"

class Bluetooth : public Component, public Drawing {
	public:
		enum class Mode { disconnected, connecting, connected };

		Bluetooth(Scheduler* sched, Display* disp); 
		void setMode(Mode m);
		void update(unsigned) override;
		void draw(SmartMatrix& matrix) override;
		~Bluetooth() { disp->removeDrawing(this); }

	private:
		Scheduler* sched;
		Display* disp;
		Mode mode;
		bool statusNeedsUpdate;
		int currAnimFrame;
		std::vector<unsigned long> animTimeouts;

		std::vector<unsigned long> genAnimTimeouts(int statusLength, unsigned long period);
		void clearStatus(SmartMatrix& matrix);
};

#endif
