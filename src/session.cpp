#include "session.h"
#include "color.h"
#include "cstdlib"

constexpr int slapButton = 0;

constexpr int lapCountScale = 2, lapCountX = 0, lapCountY = 0;
const fontChoices lapCountFont = font8x13;
constexpr int timeX1 = 0, timeX2 = 21, timeY = 27;
const rgb24 timeColor = blue,
	  lapCountColor = {0, 175, 0},
	  puncColor = red,
	  timeBorderColor = {175, 100, 0};

constexpr int charWidth = 3, charHeight = 5;

Session::Session(Scheduler* sched, SmartMatrix* matrix, Buttons* buttons, Storage* stor):
	sched{sched},
	matrix{matrix},
	buttons{buttons},
	stor{stor},
	lapGoal{0}, currLap{0}, lastTime{0},
	mode{Mode::ready} {}

Session::~Session() {
	stop();
}

void Session::begin() {
	// TODO check if there's enough storage space

	bpushTaskID = sched->setInterval(this, 20);
	timerTaskID = sched->setInterval(this, 35);
}

void Session::update(unsigned taskID) {
	if(taskID == bpushTaskID && buttons->wasPushed(slapButton)) {
		onSlap();
	}
	redraw();
}

void Session::stop() {
	sched->clearInterval(bpushTaskID);
	sched->clearInterval(timerTaskID);
}

uint16_t Session::millisToCentis(unsigned long millis) {
	// better to round up than down
	if(millis % 10 > 0) {
		millis += 10;
	}

	return millis / 10;
}

void Session::onSlap() {
	unsigned long time = buttons->pushedAt(slapButton);
	int lapTimeCentis = millisToCentis(time - lastTime);
	lapTimes.push_back(lapTimeCentis);

	lastTime = time;
	++currLap;
	buttons->reset();
}

void Session::redraw() {
	clearDisplay();

	drawLapCount();
	drawTime(timeX1, timeY, millisToCentis(millis() - lastTime), timeColor, true);
	drawTime(timeX2, timeY, lapTimes.size() ? lapTimes.back() : 0, timeColor, false);
	drawTimeBorder();

	matrix->swapBuffers();
}

void Session::drawLapCount() {
	matrix->setFont(lapCountFont);

	char text[3] = {};
	text[0] = currLap / 10 + '0';
	text[1] = currLap % 10 + '0';
	matrix->drawString(lapCountX, lapCountY, lapCountColor, text, lapCountScale);

	matrix->setFont(font3x5);
}

void Session::drawTime(int x, int y, uint16_t centis, const rgb24& color, bool drawCentis) {
	int extraCentis = centis % 100;
	centis /= 100;
	int seconds = centis % 60;
	int minutes = centis / 60;

	// draw punctuation
	matrix->drawChar(x + charWidth - 1, y, puncColor, ':');
	if(drawCentis) {
		matrix->drawChar(x + 3*charWidth + 1, y, puncColor, '.');
	}

	// draw minutes
	matrix->drawChar(x, y, color, minutes + '0');
	x += charWidth + 1;

	// draw seconds
	matrix->drawChar(x, y, color, seconds / 10 + '0');
	x += charWidth + 1;
	matrix->drawChar(x, y, color, seconds % 10 + '0');
	x += charWidth + 1;

	if(drawCentis) {
		// draw centis
		matrix->drawChar(x, y, color, extraCentis / 10 + '0');
		x += charWidth + 1;
		matrix->drawChar(x, y, color, extraCentis % 10 + '0');
	}
}

void Session::drawTimeBorder() {
	matrix->drawFastHLine(0, 31, 26, timeBorderColor);
	matrix->drawFastVLine(20, 26, 31, timeBorderColor);
}

void Session::clearDisplay() {
	matrix->fillRectangle(0, 1, 31, 31, black);
}
