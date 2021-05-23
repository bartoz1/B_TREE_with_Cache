#pragma once
class bTNode {
public:
	bool isLeaf;
	int minElem;
	int keysCount;
	int* keys;
	bTNode** childs;
	bTNode(int t);
	bTNode(int t, bool isLeaf);
	int search(int s);	// szukanie wartosci w obecnym nodzie i nastepnie wywolanie wyszukiwania w dzieciach
	void setLeaf();
	void addKey(int key);
	void removeKey(int key);
	void splitNode(int indx, bTNode* toSplit);
	void printNode();
	void printNodeValues();
	~bTNode();

friend class bTree;
};

