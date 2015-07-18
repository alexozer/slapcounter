#ifndef component_h
#define component_h

class Component {
	public:
		virtual void update(unsigned taskID) = 0;
		virtual ~Component() {};
};

#endif
