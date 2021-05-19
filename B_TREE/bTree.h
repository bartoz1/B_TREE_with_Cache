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
	bTree(int h);
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
	~bTree();
private:
	void addToCache(int data);	// dodanie wartosci do cacha
	void shiftCache();			// przesuniecie wartosci w cachu
	bool inCache(int data);		// szukanie wartosci w cachu
	int getLeafLvl();				// zwraca na ktorym poziomie sa liscie
	void printCache();
	void deleteChildren(bTNode* parent);
};

