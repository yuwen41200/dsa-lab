/**
 * Threaded Binary Search Tree C++ Implementation
 * Author: Yu-wen Pwu, NCTU CS, Taiwan
 * Compilation: g++ -Wall -Wextra -Wpedantic --std=c++11 main.cpp -o main
 */

#include <iostream>
using namespace std;

class Node {
public:
	Node();
	Node(int value);
private:
	Node *leftChild, *rightChild;
	bool leftIsThread, rightIsThread;
	int value;
	friend class BinaryTree;
};

class BinaryTree {
public:
	BinaryTree();
	~BinaryTree();
	void insert(int value);
	void remove(int value);
	void inOrder();
	void reverseInOrder();
private:
	Node *root, *head, *tail;
	int size;
	void deleteAll(Node *node);
	Node *findSuccessor(Node *node);
	Node *findPredecessor(Node *node);
};

Node::Node() {
	leftChild = rightChild = nullptr;
	leftIsThread = true;
	rightIsThread = true;
}

Node::Node(int value) {
	this->value = value;
	leftChild = rightChild = nullptr;
	leftIsThread = true;
	rightIsThread = true;
}

BinaryTree::BinaryTree() {
	head = new Node();
	tail = new Node();
	head->rightChild = tail;
	tail->leftChild = head;
	root = nullptr;
	size = 0;
}

BinaryTree::~BinaryTree() {
	if (root)
		deleteAll(root);
	if (head)
		delete head;
	if (tail)
		delete tail;
}

void BinaryTree::insert(int value) {
	// creating a new node
	Node *n = new Node(value);
	Node *p = root;
	while (p) {
		// going to the left subtree
		if (value < p->value) {
			if (p->leftIsThread) {
				n->rightChild = p;
				n->leftChild = p->leftChild;
				p->leftChild = n;
				p->leftIsThread = false;
				size++;
				return;
			}
			else {
				p = p->leftChild;
			}
		}
		// going to the right subtree
		else if (value > p->value) {
			if (p->rightIsThread) {
				n->leftChild = p;
				n->rightChild = p->rightChild;
				p->rightChild = n;
				p->rightIsThread = false;
				size++;
				return;
			}
			else {
				p = p->rightChild;
			}
		}
		// the node already exists
		else {
			return;
		}
	}
	// the tree is empty
	n->leftChild = head;
	n->rightChild = tail;
	root = n;
	size++;
}

void BinaryTree::remove(int value) {
	// the tree is empty
	if (!root)
		return;
	// finding the node in the tree
	Node *p = root, *q = nullptr;
	bool goRight = true;
	while (p) {
		if (value < p->value) {
			if (p->leftIsThread) {
				return;
			}
			else {
				q = p;
				p = p->leftChild;
				goRight = false;
			}
		}
		else if (value > p->value) {
			if (p->rightIsThread) {
				return;
			}
			else {
				q = p;
				p = p->rightChild;
				goRight = true;
			}
		}
		else {
			break;
		}
	}
	// case 1. the node has no children
	if (p && q && p->leftIsThread && p->rightIsThread) {
		if (goRight) {
			q->rightIsThread = true;
			q->rightChild = p->rightChild;
			if (!p->rightChild->leftIsThread)
				p->rightChild->leftChild = q;
		}
		else {
			q->leftIsThread = true;
			q->leftChild = p->leftChild;
			if (!p->leftChild->rightIsThread)
				p->leftChild->rightChild = q;
		}
		delete p;
		size--;
	}
	// case 2. the node has right subtree
	else if (p && q && p->leftIsThread) {
		// ...
	}
	// case 3. the node has left subtree
	else if (p && q && p->rightIsThread) {
		// ...
	}
	// case 4. the node has two subtrees
	else if (p && q) {
		remove(n);
		// ...
	}
	// case 5. the node is the root of the tree
	else {
		remove(n);
		a = b;
		// ...
	}
}

void BinaryTree::inOrder() {
	Node *p = root;
	while (!p->leftIsThread)
		p = p->leftChild;
	while (p != tail) {
		cout << p->value << " ";
		p = findSuccessor(p);
	}
	cout << endl;
}

void BinaryTree::reverseInOrder() {
	Node *p = root;
	while (!p->rightIsThread)
		p = p->rightChild;
	while (p != head) {
		cout << p->value << " ";
		p = findPredecessor(p);
	}
	cout << endl;
}

void BinaryTree::deleteAll(Node *node) {
	if (!node->leftIsThread && node->leftChild)
		deleteAll(node->leftChild);
	if (!node->rightIsThread && node->rightChild)
		deleteAll(node->rightChild);
	delete node;
}

Node *BinaryTree::findSuccessor(Node *node) {
	if (node->rightIsThread) {
		node = node->rightChild;
	}
	else {
		node = node->rightChild;
		while (!node->leftIsThread)
			node = node->leftChild;
	}
	return node;
}

Node *BinaryTree::findPredecessor(Node *node) {
	if (node->leftIsThread) {
		node = node->leftChild;
	}
	else {
		node = node->leftChild;
		while (!node->rightIsThread)
			node = node->rightChild;
	}
	return node;
}

int main(int argc, char **argv) {
	BinaryTree *binaryTree = new BinaryTree();
	binaryTree->insert(11); // 11
	binaryTree->insert(20); // 11, 20
	binaryTree->insert(56); // 11, 20, 56
	binaryTree->insert(47); // 11, 20, 47, 56
	binaryTree->insert(63); // 11, 20, 47, 56, 63
	binaryTree->insert(25); // 11, 20, 25, 47, 56, 63
	binaryTree->insert(38); // 11, 20, 25, 38, 47, 56, 63
	binaryTree->insert(60); // 11, 20, 25, 38, 47, 56, 60, 63
	binaryTree->insert(29); // 11, 20, 25, 29, 38, 47, 56, 60, 63
	binaryTree->insert(51); // 11, 20, 25, 29, 38, 47, 51, 56, 60, 63
	binaryTree->insert(47); // duplicate
	binaryTree->insert(11); // duplicate
	binaryTree->remove(63); // 11, 20, 25, 29, 38, 47, 51, 56, 60
	binaryTree->remove(11); // 20, 25, 29, 38, 47, 51, 56, 60
	binaryTree->remove(51); // 20, 25, 29, 38, 47, 56, 60
	binaryTree->remove(47); // 20, 25, 29, 38, 56, 60
	binaryTree->remove(47); // not found
	binaryTree->remove(32); // not found
	binaryTree->inOrder();
	binaryTree->reverseInOrder();
	delete binaryTree;
	return 0;
}
