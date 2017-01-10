#ifndef matrix_h
#define matrix_h

#include "SmartMatrix_32x32.h"

class Matrix : public SmartMatrix {
	public:
		void drawString(int16_t x, int16_t y, const rgb24& charColor, const rgb24& backColor, const char text[], int16_t pxSize);
};

#endif
