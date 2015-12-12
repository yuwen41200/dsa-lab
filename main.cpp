/**
 * Threaded Binary Search Tree
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
	Node *n = new Node(value);
	Node *p = root;
	while (p) {
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
		else {
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
	}
	n->leftChild = head;
	n->rightChild = tail;
	root = n;
	size++;
}

void BinaryTree::remove(int value) {
	//TODO: delete a node
}

void BinaryTree::inOrder() {
	Node *p = root;
	while (!p->leftIsThread)
		p = p->leftChild;
	while (p != tail) {
		cout << p->value << " ";
		if (p->rightIsThread)
			p = p->rightChild;
		else
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
		if (p->leftIsThread)
			p = p->leftChild;
		else
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
	node = node->rightChild;
	while (!node->leftIsThread)
		node = node->leftChild;
	return node;
}

Node *BinaryTree::findPredecessor(Node *node) {
	node = node->leftChild;
	while (!node->rightIsThread)
		node = node->rightChild;
	return node;
}

int main(int argc, char **argv) {
	BinaryTree *binaryTree = new BinaryTree();
	binaryTree->insert(11);
	binaryTree->insert(20);
	binaryTree->insert(56);
	binaryTree->insert(47);
	binaryTree->insert(63);
	binaryTree->insert(38);
	binaryTree->insert(29);
	binaryTree->insert(51);
	binaryTree->inOrder();
	binaryTree->reverseInOrder();
	delete binaryTree;
	return 0;
}
