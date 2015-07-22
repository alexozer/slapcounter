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
		static void isr();
};

#endif
