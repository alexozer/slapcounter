#ifndef storage_h
#define storage_h

#include <vector>
#include <Arduino.h>

class Storage {
	public:
		Storage();

		// writeSession() returns false if there's no room left
		bool writeSession(const std::vector<uint16_t>& lapTimes);

		void setPoolLength(uint16_t l);

	private:
		struct {
			int endAddr;
			uint16_t poolLen;
		} header;

		void writeHeader();
};

#endif
