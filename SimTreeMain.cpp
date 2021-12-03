#include "Node.h"

class A : public Node {
private:

public:
	using Node::Node;

	void GetInputs() {
		std::cout << label << " inputs got.\n";
	}

	void Process() {
		std::cout << label << " processed.\n";
	}
};

class B : public Node {
public:
	using Node::Node;

	void GetInputs() {
		std::cout << label << " inputs got.\n";
	}

	virtual void Process() {

		std::cout << label << " processed.\n";
	}
};

class C : public Node {
public:
	using Node::Node;

	void GetInputs() {
		std::cout << label << " inputs got.\n";
	}

	virtual void Process() {

		std::cout << label << " processed.\n";
	}
};

class D : public Node {
public:
	using Node::Node;

	void GetInputs() {
		std::cout << label << " inputs got.\n";
	}

	virtual void Process() {

		std::cout << label << " processed.\n";
	}
};

class E : public Node {
public:
	using Node::Node;

	void GetInputs() {
		std::cout << label << " inputs got.\n";
	}

	virtual void Process() {

		std::cout << label << " processed.\n";
	}
};

class F : public Node {
public:
	using Node::Node;

	void GetInputs() {
		std::cout << label << " inputs got.\n";
	}

	virtual void Process() {

		std::cout << label << " processed.\n";
	}
};

class G : public Node {
public:
	using Node::Node;

	void GetInputs() {
		std::cout << label << " inputs got.\n";
	}

	virtual void Process() {

		std::cout << label << " processed.\n";
	}
};

class H : public Node {
public:
	using Node::Node;

	void GetInputs() {
		std::cout << label << " inputs got.\n";
	}

	virtual void Process() {

		std::cout << label << " processed.\n";
	}
};

int main() {
	Node* a = new A("a", 0);

	Node* c = new B("c", a);
	Node* g = new G("g", c);
	Node* h = new H("h", c);

	Node* b = new B("b", a, c);
	Node* e = new E("e", b);
	Node* f = new F("f", b);
	Node* d = new D("d", b, std::vector<Node*>({e, f}));

	a->Propagate();

	std::cin.get();

	return 0;
}