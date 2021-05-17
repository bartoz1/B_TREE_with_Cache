#pragma once
#include "bTNode.h"

class bTree {
public:
	int order;
	int minElem;
	int elements;
	bTNode* root;
	bTree(int h);
	void add(int data);
	void splitChild();
	void printTree();
	void printValues();
	void search(int x);
	void loadTree();
	bTNode* loadNode();
	
};

