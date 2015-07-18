#ifndef task_h
#define task_h

#include <vector>
#include <Arduino.h>
#include "component.h"

class Task {
	public:
		Task(Component* compon, unsigned long interval);

		bool isReady() const {return millis() - lastMillis >= interval; }
		void run();
		unsigned getID() const { return id; }
		void reset() {lastMillis = millis(); }

		~Task() {oldIDs.push_back(id);}

		typedef unsigned id_type;

	private:
		unsigned id;
		Component* c;

		unsigned long interval;
		unsigned long lastMillis;

		static unsigned nextID;
		static std::vector<unsigned> oldIDs;
};

#endif
