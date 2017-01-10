#ifndef mand_h
#define mand_h

#include "component.h"
#include "scheduler.h"
#include "buttons.h"
#include "SmartMatrix_32x32.h"
#include <complex>

class Mand : public Component {

	public:
		Mand(Scheduler* sched, SmartMatrix* matrix, Buttons *buttons);
		~Mand();

		void begin();
		void update(unsigned taskID) override;

	private:
		Scheduler* sched;
		SmartMatrix* matrix;
		Buttons* buttons;
		unsigned drawTID, serialTID;

		double scale;
		std::complex<double> offset;
		int iters;

		void draw();
		void serial();
		std::complex<double> matToMand(double x, double y);
		int inSet(std::complex<double> c, int iters);
		rgb24 getColor(double t);
};

#endif
