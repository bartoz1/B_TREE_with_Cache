#pragma once
#include "bTNode.h"

class bTree {
public:
	int order;
	int minElem;
	int elements;
	bTNode* root;
	int* cache;
	int cacheSize;
	bTree(int t);
	void add(int data);
	void splitChild();
	void printTree();
	void printValues();
	void search(int x);
	int searchAndGetLvl(int x);
	void loadTree();
	bTNode* loadNode();
	void searchWithCache();
	void searchWithSuperCache();
	void delKey(int key);
	~bTree();
private:
	void addToCache(int data);	// dodanie wartosci do cacha
	void shiftCache();			// przesuniecie wartosci w cachu
	bool inCache(int data) const;		// szukanie wartosci w cachu
	int getLeafLvl() const;			// zwraca na ktorym poziomie sa liscie
	void deleteChildren(bTNode* parent);
	bTNode* getNodeWithKey(int key);
};

