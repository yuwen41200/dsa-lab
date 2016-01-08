/**
 * Binomial Heap C++ Implementation
 * Author: Yu-wen Pwu, NCTU CS, Taiwan
 * Compilation: g++ -Wall -Wextra -Wpedantic -std=c++11 main.cpp -o main
 * Comments: I love Java coding style !!!
 *           I cannot accept any other coding styles !!!
 */

#include <iostream>
#include <limits>
using namespace std;

char uninitialized;
#define UNINITIALIZED ((Node *) &uninitialized)

class NonpositiveKeyException : public exception {
	const char *what() const noexcept {
		return "NONPOSITIVE_KEY_EXCEPTION\n";
	}
};

class Node {
public:
	Node();
	Node(int nid, int key);
private:
	Node *parent;  // parent
	Node *child;   // left child
	Node *sibling; // right sibling
	int nid;       // node id
	int key;       // key
	int degree;    // height of this subtree
	friend class BinomialHeap;
};

Node::Node() {
	parent = child = sibling = nullptr;
	nid = key = degree = 0;
}

Node::Node(int nid, int key) {
	parent = child = sibling = nullptr;
	this->nid = nid;
	this->key = key;
	this->degree = 0;
}

class BinomialHeap {
public:
	BinomialHeap();
	~BinomialHeap();
	void insert(int nid, int key);
	void merge(BinomialHeap *binomialHeap);
	void decreaseKey(int nid, int key);
	void deleteMin();
	int getMin();
	int getSize();
	int getSizeBelowKey(int key, Node *node = UNINITIALIZED);
private:
	Node *head; // the head of the binomial tree root list
	void deleteAll(Node *node);
};

BinomialHeap::BinomialHeap() {
	head = nullptr;
}

BinomialHeap::~BinomialHeap() {
	deleteAll(head);
}

/**
 * Insert a node into the binomial heap
 */
void BinomialHeap::insert(int nid, int key) {
	if (key <= 0) { // according to the spec, a nonpositive key is not allowed
		throw NonpositiveKeyException();
	}
	else {
		BinomialHeap *binomialHeap = new BinomialHeap();
		binomialHeap->head = new Node(nid, key); // construct another binomial heap with one node
		merge(binomialHeap); // and merge them together
		// do not delete "binomialHeap" !!
	}
}

/**
 * Merge two binomial heaps together
 */
void BinomialHeap::merge(BinomialHeap *binomialHeap) {
	// merge two binomial tree root lists
	if (!binomialHeap->head)
		return;
	if (!head) {
		head = binomialHeap->head;
		return;
	}
	Node *temp1 = head; // original binomial heap
	Node *temp2 = binomialHeap->head; // binomial heap to be merged
	Node *temp3; // new binomial heap
	if (temp1->degree < temp2->degree) { // decide the new head
		head = temp3 = temp1;
		temp1 = temp1->sibling;
	}
	else {
		head = temp3 = temp2;
		temp2 = temp2->sibling;
	}
	while (temp1 && temp2) {
		if (temp1->degree < temp2->degree) {
			temp3->sibling = temp1;
			temp3 = temp3->sibling;
			temp1 = temp1->sibling;
		}
		else {
			temp3->sibling = temp2;
			temp3 = temp3->sibling;
			temp2 = temp2->sibling;
		}
	}
	while (temp1) {
		temp3->sibling = temp1;
		temp3 = temp3->sibling;
		temp1 = temp1->sibling;
	}
	while (temp2) {
		temp3->sibling = temp2;
		temp3 = temp3->sibling;
		temp2 = temp2->sibling;
	}
	// from now on, we have a new binomial tree root list
	temp1 = nullptr; // previous node
	temp2 = head; // current node
	temp3 = head->sibling; // next node
	while (temp3) {
		if (temp2->degree != temp3->degree) { // their height are different, go next
			temp1 = temp2;
			temp2 = temp3;
			temp3 = temp3->sibling;
		}
		else if (temp3->sibling && temp2->degree == temp3->degree && temp3->degree == temp3->sibling->degree) {
			temp1 = temp2; // three binomial trees have the same height, go next
			temp2 = temp3;
			temp3 = temp3->sibling;
		}
		else if (temp2->key < temp3->key) { // combine two trees, "temp3" become a child of "temp2"
			temp2->sibling = temp3->sibling;
			temp3->parent = temp2;
			temp3->sibling = temp2->child;
			temp2->child = temp3;
			temp2->degree++;
			temp3 = temp2->sibling;
		}
		else { // combine two trees, "temp2" become a child of "temp3"
			if (temp1)
				temp1->sibling = temp3;
			else
				head = temp3;
			temp2->parent = temp3;
			temp2->sibling = temp3->child;
			temp3->child = temp2;
			temp3->degree++;
			temp2 = temp3;
			temp3 = temp3->sibling;
		}
	}
}

/**
 * Find a node with node id "nid" and decrease its key by "key"
 */
void BinomialHeap::decreaseKey(int nid, int key) {
// TODO
}

/**
 * Delete the smallest node in the binomial heap
 */
void BinomialHeap::deleteMin() {
	if (!head)
		return;
	// find the address of the smallest node
	int min = head->key;
	Node *ptrMin = head;
	Node *ptrMinPrev = nullptr;
	Node *temp = head;
	while (temp->sibling) { // traverse the binomial tree root list
		if (temp->sibling->key < min) { // each binomial tree is also a min heap
			min = temp->sibling->key;
			ptrMin = temp->sibling;
			ptrMinPrev = temp;
		}
		temp = temp->sibling;
	}
	// remove that binomial tree from the root list
	if (ptrMinPrev)
		ptrMinPrev->sibling = ptrMin->sibling;
	else
		head = ptrMin->sibling;
	// reverse the list of the children of that binomial tree
	Node *prev = nullptr;
	Node *curr = ptrMin->child;
	Node *next;
	while (curr) {
		next = curr->sibling;
		curr->sibling = prev;
		curr->parent = nullptr;
		prev = curr;
		curr = next;
	}
	// delete the root of that binomial tree
	delete ptrMin;
	// merge them back to the original binomial heap
	BinomialHeap *binomialHeap = new BinomialHeap();
	binomialHeap->head = prev; // construct another binomial heap with the new root list
	merge(binomialHeap); // and merge them together, do not delete "binomialHeap" !!
}

/**
 * Return the node id of the smallest node
 */
int BinomialHeap::getMin() {
	Node *temp = head;
	int min = numeric_limits<int>::max();
	int nid = -1;
	while (temp) { // traverse the binomial tree root list
		if (temp->key < min) { // each binomial tree is also a min heap
			min = temp->key;
			nid = temp->nid;
		}
		temp = temp->sibling;
	}
	return nid;
}

/**
 * Return the number of nodes in the binomial heap
 */
int BinomialHeap::getSize() {
	Node *temp = head;
	int size = 0;
	while (temp) { // traverse the binomial tree root list
		size += 1 << temp->degree; // each binomial tree has (2^degree) nodes
		temp = temp->sibling;
	}
	return size;
}

/**
 * Return the number of nodes that are less than or equal to "key"
 */
int BinomialHeap::getSizeBelowKey(int key, Node *node) {
	node = (node == UNINITIALIZED) ? head : node;
	int size = 0;
	if (node) {
		size += getSizeBelowKey(key, node->sibling);
		if (node->key <= key) {
			size++; // if this node is larger than "key", no need to check its children
			size += getSizeBelowKey(key, node->child);
		}
	}
	return size;
}

void BinomialHeap::deleteAll(Node *node) {
	if (node) {
		deleteAll(node->sibling);
		deleteAll(node->child);
		delete node;
	}
}

int main() {
	try {
		BinomialHeap *a = new BinomialHeap();
		a->insert(1, 60);
		a->insert(2, 20);
		a->insert(3, 30);
		a->insert(4, 70);
		a->insert(5, 50);
		cout << "a->getMin() = " << a->getMin() << endl; // 2
		cout << "a->getSize() = " << a->getSize() << endl; // 5
		cout << "a->getSizeBelowKey(50) = " << a->getSizeBelowKey(50) << endl; // 3
		BinomialHeap *b = new BinomialHeap();
		b->insert(6, 15);
		b->insert(7, 35);
		b->insert(8, 85);
		cout << "b->getMin() = " << b->getMin() << endl; // 6
		cout << "b->getSize() = " << b->getSize() << endl; // 3
		cout << "b->getSizeBelowKey(55) = " << b->getSizeBelowKey(55) << endl; // 2
		a->merge(b);
		cout << "a->getMin() = " << a->getMin() << endl; // 6
		cout << "a->getSize() = " << a->getSize() << endl; // 8
		cout << "a->getSizeBelowKey(60) = " << a->getSizeBelowKey(60) << endl; // 6
		a->insert(0, 0); // NONPOSITIVE_KEY_EXCEPTION
		a->decreaseKey(4, 37);
		a->decreaseKey(2, 11);
		a->decreaseKey(2, 11);
		a->decreaseKey(3, 17);
		cout << "a->getMin() = " << a->getMin() << endl; // 3
		cout << "a->getSize() = " << a->getSize() << endl; // 7
		cout << "a->getSizeBelowKey(45) = " << a->getSizeBelowKey(45) << endl; // 4
		a->deleteMin();
		a->deleteMin();
		a->deleteMin();
		cout << "a->getMin() = " << a->getMin() << endl; // 7
		cout << "a->getSize() = " << a->getSize() << endl; // 4
		cout << "a->getSizeBelowKey(40) = " << a->getSizeBelowKey(40) << endl; // 1
		delete a;
	}
	catch (exception& e) {
		cout << e.what();
	}
	return 0;
}
