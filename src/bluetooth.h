#ifndef bluetooth_h
#define bluetooth_h

#include "component.h"
#include "drawing.h"
#include "scheduler.h"
#include "display.h"

class Bluetooth : public Component, public Drawing {
	public:
		enum class Mode { disconnected, connecting, connected };

		Bluetooth(Scheduler* sched, Display* disp): 
			sched{sched}, disp{disp},
			mode{Mode::disconnected}, statusNeedsUpdate{true},
			currAnimFrame{0} {
			disp->addDrawing(this);
		};
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

		void clearStatus(SmartMatrix& matrix);
};

#endif
