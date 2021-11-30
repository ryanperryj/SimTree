#include "Node.h"
#include <iostream>


int main() {

	Node p(0);
	Node c1(&p), c2(&p);

	std::printf("p: %p c1: %p c2 %p\n", &p, &c1, &c2);

	p.Process();

	// c1, c2, p

	return 0;
}