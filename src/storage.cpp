#include <vector>
#include <EEPROM.h>
#include "storage.h"
using std::vector;

constexpr int romSize = 2048;
constexpr int headerAddr = 0;
constexpr uint16_t defaultPoolLen = 1000;

struct SessionMetadata {
	uint16_t year;
	uint8_t month, day, hour, minute;

	uint16_t poolLen, numLaps;
};

Storage::Storage() {
	EEPROM.get(headerAddr, header);
	if((unsigned)header.endAddr < sizeof(header)) {
		header = {sizeof(header), defaultPoolLen};
		writeHeader();
	}
}

bool Storage::writeSession(const vector<uint16_t>& lapTimes) {
	static SessionMetadata s;

	int space = sizeof(s) + lapTimes.size() * sizeof(uint16_t);
	if(romSize - header.endAddr < space) return false;

	// TODO init session date here
	s.poolLen = header.poolLen;
	s.numLaps = lapTimes.size();
	EEPROM.put(header.endAddr, s);
	header.endAddr += sizeof(s);

	for(auto time : lapTimes) {
		EEPROM.put(header.endAddr, time);
		header.endAddr += sizeof(time);
	}

	writeHeader();
	return true;
}

void Storage::setPoolLength(uint16_t l) {
	header.poolLen = l;
	writeHeader();
}

void Storage::writeHeader() {
	EEPROM.put(headerAddr, header);
}
