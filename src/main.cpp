#define DEBUG

#ifdef DEBUG
#include "test.h"
int main() {
	runTests();
}

#else
#include "slapcounter.h"
SlapCounter sc;
int main() {
	sc.run();
}

#endif
