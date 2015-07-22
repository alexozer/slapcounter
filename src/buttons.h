#ifndef buttons_h
#define buttons_h

class Buttons {

	public:
		Buttons();

		static void setPushTime(int button, unsigned long time) {
			pushTimes[button] = time;
		}
		bool wasPushed(int button) const { return pushTimes[button]; }
		unsigned long pushedAt(int button) const { return pushTimes[button]; }
		void reset();

	private:
		static volatile unsigned long pushTimes[];
};

#endif
