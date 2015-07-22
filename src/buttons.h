#ifndef buttons_h
#define buttons_h

class Buttons {

	public:
		Buttons();
		~Buttons();

		bool wasPushed(int button) const;
		unsigned long pushedAt(int button) const;
		void reset();

	private:
		static volatile unsigned long pushTimes[];

		static void onPush(int button);
		static void onPush0() { onPush(0); }
		static void onPush1() { onPush(1); }
		static void onPush2() { onPush(2); }
};

#endif
