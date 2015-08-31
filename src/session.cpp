#include "session.h"

constexpr unsigned long gpushInterval = 20;
constexpr int slapButton = 0;

Session::Session(Scheduler* sched, SmartMatrix* matrix, Buttons* buttons, Storage* stor):
	sched{sched},
	matrix{matrix},
	buttons{buttons},
	stor{stor},
	lapGoal{0}, currLap{0}, lastTime{0},
	mode{Mode::ready} {}

Session::~Session() {
	sched->clearInterval(bpushTaskID);
}

void Session::begin(int lapGoal) {
	// TODO check if there's enough storage space

	bpushTaskID = sched->setInterval(this, 20);
	this->lapGoal = lapGoal;
}

void Session::update(unsigned) {
	unsigned long time = buttons->pushedAt(slapButton);
	if(!time) return;

	buttons->reset();

	if(mode == Mode::ready) {
		currLap = 0;
		lastTime = time;
		lapTimes.clear();
		mode = Mode::active;
	} else if(mode == Mode::active) {
		uint16_t lapTimeCentis = millisToCentis(lastTime - time);
		lastTime = time;

		lapTimes.push_back(lapTimeCentis);
		++currLap;
		drawLapCount();
		drawLapTime();
		matrix->swapBuffers();

		if(currLap == lapGoal) {
			stor->writeSession(lapTimes);
			lapGoal = 0;
			mode = Mode::ready;
		}
	}
}

uint16_t Session::millisToCentis(unsigned long millis) {
	// better to round up than down
	if(millis % 10 > 0) {
		millis += 10;
	}

	return millis / 10;
}

void Session::drawLapCount() {
	// TODO
}

void Session::drawLapTime() {
	// TODO
}
