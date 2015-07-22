#ifndef drawing_h
#define drawing_h

#include <SmartMatrix.h>

class Drawing {
	public:
		virtual void draw(SmartMatrix& matrix) = 0;

		virtual ~Drawing() {};
};

#endif
