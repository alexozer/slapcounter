#ifndef buttons_h
#define buttons_h

#include "Bounce2.h"
#include <Arduino.h>

class Buttons {

	public:
		Buttons();
		~Buttons();

		bool wasPushed(int button) const;
		unsigned long pushedAt(int button) const;
		void reset();
		void reset(int button);

	private:
		static volatile unsigned long pushTimes[];
		static volatile Bounce bounces[];

		static void onPush(int button);
		static void onPush0() { onPush(0); }
		static void onPush1() { onPush(1); }
		static void onPush2() { onPush(2); }

		// based on advice from http://savannah.nongnu.org/bugs/?22163
		class AtomicBlock {
			public:
				AtomicBlock(): sreg{SREG} { cli(); }
				~AtomicBlock() { asm("" ::: "memory"); SREG = sreg; }
			private:
				uint8_t sreg;
		};
};

#endif
