#ifndef cuauv_h
#define cuauv_h

#include "component.h"
#include "scheduler.h"
#include "SmartMatrix_32x32.h"

class Cuauv : public Component {

	public:
		Cuauv(Scheduler *sched, SmartMatrix *matrix);
		~Cuauv();
		void begin();
		void update(unsigned taskID) override;
		void stop();

	private:
		Scheduler *sched;
		SmartMatrix *matrix;

		unsigned rotateTID, colorTID, drawTID, reverseTID, textFadeTID;
		
		// propellor rotation
		double frame;
		bool direction;

		// propellor color
		rgb24 color;
		double colorLerp;
		int colorI;

		// text fade
		double textFadeLerp;

		void drawBitmap(int x, int y, int width, const rgb24& color, const char* str);
		void draw();
		void rotate();
		void colorize();
		void drawText();
};

#endif
