#pragma once
class bTNode {
public:
	bool isLeaf;
	int minElem;
	int keysCount;
	int* keys;
	bTNode** childs;
	bTNode(int order);
	bTNode(int order, bool isLeaf);
	int search(int s);	// szukanie wartosci w obecnym nodzie i nastepnie wywolanie wyszukiwania w dzieciach
	void setLeaf();
	void unSetLeaf();
	void addKey(int key);
	void splitNode(int data, bTNode* toSplit);
	void printNode();
	void printNodeValues();

friend class bTree;
};

