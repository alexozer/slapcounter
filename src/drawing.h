#ifndef drawing_h
#define drawing_h

#include "SmartMatrix_32x32.h"

class Drawing {
	public:
		virtual void draw(SmartMatrix& matrix) = 0;

		virtual ~Drawing() {};
};

#endif
