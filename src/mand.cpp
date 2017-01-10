#include "mand.h"
#include "color.h"
using std::complex;

Mand::Mand(Scheduler* sched, SmartMatrix* matrix, Buttons *buttons):
	sched{sched}, matrix{matrix}, buttons{buttons},
	scale{1}, offset{0, 0}, iters{15} {}

Mand::~Mand() {
	//sched->clearInterval(drawTID);
	sched->clearInterval(serialTID);
}

void Mand::begin() {
	//drawTID = sched->setInterval(this, 1000/30);
	serialTID = sched->setInterval(this, 1000/60);
}

constexpr int dim = 32;
constexpr double scaleFactor = 1.05;
constexpr double offsetInc = 0.1;

void Mand::update(unsigned taskID) {
	if(taskID == drawTID) {
		draw();
	} else if(taskID == serialTID) {
		serial();
		draw();
	}
}

void Mand::draw() {
	matrix->fillScreen(black);

	for(int x = 0; x != dim; ++x) {
		for(int y = 0; y != dim; ++y) {
			auto pt = matToMand(x, y);
			pt.real(pt.real()/scale);
			pt.imag(pt.imag()/scale);
			pt -= offset;

			int n = inSet(pt, iters);
			double t = (double)n / (double)iters;
			matrix->drawPixel(x, y, getColor(t));
		}
	}

	matrix->swapBuffers();
}

void Mand::serial() {
	while(Serial.available()) {
		switch(Serial.read()) {
			case '=':
				scale *= scaleFactor;
				break;
			case '-':
				scale /= scaleFactor;
				break;
			case 'h':
				offset.real(offset.real()+(offsetInc / scale));
				break;
			case 'l':
				offset.real(offset.real()-(offsetInc / scale));
				break;
			case 'j':
				offset.imag(offset.imag()+(offsetInc / scale));
				break;
			case 'k':
				offset.imag(offset.imag()-(offsetInc / scale));
				break;
			case 'i':
				++iters;
				break;
			case 'd':
				--iters;
				if(iters < 0) iters = 0;
				break;
		}
	}
}

complex<double> Mand::matToMand(double x, double y) {
	return complex<double>{((x / (dim-1)) - 0.5) * 2, ((((dim-1)-y) / 31) - 0.5) * 2};
}

int Mand::inSet(complex<double> c, int iters) {
	complex<double> z;

	for(int i = 0; i != iters; ++i) {
		z = z * z + c;
		if(z.real() * z.real() + z.imag() + z.imag() > 4) {
			return i;
		}
	}

	return iters;
}

const rgb24 colors[] = {black, red, orange, yellow, green, blue, white};
constexpr int numColors = sizeof(colors) / sizeof(colors[0]);

rgb24 Mand::getColor(double t) {
	t *= 0.999; // so t != 1
	double tScaled = t * numColors;
	int color1 = (int) tScaled;
	int color2 = (color1 + 1) % numColors;

	double tt = tScaled - color1;
	double it = 1 - tt;

	rgb24 c;
	c.red = colors[color1].red * it + colors[color2].red * tt;
	c.green = colors[color1].green * it + colors[color2].green * tt;
	c.blue = colors[color1].blue * it + colors[color2].blue * tt;

	return c;
}
