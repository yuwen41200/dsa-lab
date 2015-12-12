/**
 * Threaded Binary Search Tree
 * Author: Yu-wen Pwu, NCTU CS, Taiwan
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
	void reverseOrder();
private:
	Node *root, *head, *tail;
	int size;
	void deleteAll(Node *node);
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
	//TODO: travel the tree from head to tail
}

void BinaryTree::reverseOrder() {
	//TODO: travel the tree from tail to head
}

void BinaryTree::deleteAll(Node *node) {
	if (!node->leftIsThread && node->leftChild)
		deleteAll(node->leftChild);
	if (!node->rightIsThread && node->rightChild)
		deleteAll(node->rightChild);
	delete node;
}
