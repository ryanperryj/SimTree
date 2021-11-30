#include "Node.h"


int main() {
	Node a("a");

	Node c("c");
	a.AddSubTreeHeadNode(&c);
	Node g("g");
	Node h("h");
	c.AddSubTreeHeadNode(&g);
	c.AddSubTreeHeadNode(&h);

	Node b("b", &c);
	Node e("e");
	Node f("f");
	b.AddSubTreeHeadNode(&e);
	b.AddSubTreeHeadNode(&f);
	Node d("d", std::vector<Node*>({ &e, &f }));


	a.Process();

	return 0;
}