#include "bTNode.h"
#include <iostream>
bTNode::bTNode(int t) {
	isLeaf = false;

	this->minElem = t-1;
	keys = new int[2 * t - 1];
	childs = new bTNode * [2 * t];
	for (int i = 0; i < 2 * t; i++) childs[i] = nullptr;
	keysCount = 0;
}

bTNode::bTNode(int t, bool isLeaf) {
	this->isLeaf = isLeaf;
	this->minElem = t-1;
	keys = new int[2 * t - 1];
	childs = new bTNode * [2 * t];
	for (int i = 0; i < 2 * t; i++) childs[i] = nullptr;
	keysCount = 0;
}

int bTNode::search(int s) {
	int lvl = 0;
	for (int i = 0;i < this->keysCount;i++) {
		if (keys[i] == s)
			return ++lvl;
	}
	if (this->isLeaf)
		return -1;

	for (int i = 0;i < this->keysCount+1;i++) {
		int res = childs[i]->search(s);
		if (res != -1) {
			lvl += res;
			return ++lvl;
		}
	}
	return -1;
}
void bTNode::addKey(int key) {
	if (this->isLeaf == true) {
		for (int i = this->keysCount-1; i >= 0; i--) {
			if (this->keys[i] < key) {
				this->keys[i + 1] = key;
				//this->keysCount++;
				break;
			}
			if (i == 0) {
				this->keys[1] = this->keys[0];
				this->keys[0] = key;
				//this->keysCount++;
				break;
			}
			this->keys[i + 1] = this->keys[i];
		}
		this->keysCount++;
	}
	else {	// jezeli node nie jest lisciem
		int childIndx=0;
		for (int i = 0; i < this->keysCount; i++) {		// WYBRANIE INDEKSU DOCELOWEGO DZIECKA
			if (this->keys[i] < key)
				childIndx++;
		}

		// jezeli docelowe dziecko jest pelne
		if (this->childs[childIndx]->keysCount == (minElem+1) * 2 - 1) {
			splitNode(childIndx, this->childs[childIndx]);

			// wybor miejsca na dodawany klucz
			if (this->keys[childIndx] < key)
				childIndx++;
		}
		this->childs[childIndx]->addKey(key);

	}
	
}

void bTNode::splitNode(int indx, bTNode* toSplit) {
	bTNode* newNode = new bTNode(minElem+1, toSplit->isLeaf);
	/*std::cout << "przed splitem: \n";
	for (int i = 0; i < toSplit->keysCount; i++) {
		std::cout << toSplit->keys[i] << " ";
	}
	std::cout << "\n";
	*/
	int spliAt = (toSplit->keysCount) / 2;
	//przesuniecie dzieci i kluczy w rodzicu - miejsce na nowy
	for (int i = keysCount; i > indx; i--) {
		keys[i] = keys[i - 1];
		childs[i + 1] = childs[i];
	}
	keys[indx] = toSplit->keys[spliAt];
	this->keysCount++;
	childs[indx+1] = newNode;

	int iter = 0;
	// przepisanie polowy dzielonego Noda do nowego Noda
	for (int i = spliAt + 1; i < toSplit->keysCount; i++) {
		newNode->keys[iter] = toSplit->keys[i];
		newNode->childs[iter] = toSplit->childs[i];
		iter++;
	}
	newNode->childs[iter] = toSplit->childs[toSplit->keysCount];
	newNode->keysCount = iter;
	toSplit->keysCount -= (iter + 1);
	/*std::cout << ", ";
	std::cout << "po splicie: \n";
	std::cout << "this: \n";
	for (int i = 0; i < this->keysCount; i++) {
		std::cout << this->keys[i] << " ";
	}
	std::cout << "toSplit: \n";
	for (int i = 0; i < toSplit->keysCount; i++) {
		std::cout << toSplit->keys[i] << " ";
	}
	std::cout << "\n";
	std::cout << "nowy: \n";
	for (int i = 0; i < newNode->keysCount; i++) {
		std::cout << newNode->keys[i] << " ";
	}
	std::cout << "\n";*/
}

void bTNode::setLeaf() {
	this->isLeaf = true;
}
void bTNode::unSetLeaf() {
	this->isLeaf = false;
}

void bTNode::printNode() {
	int i;
	std::cout << "( ";
	for (i = 0; i < this->keysCount; i++) {
		if (!this->isLeaf)
			this->childs[i]->printNode();
		std::cout << this->keys[i] << " ";
	}
	if (!this->isLeaf)
		this->childs[i]->printNode();
	std::cout << ") ";
}

void bTNode::printNodeValues() {
	int i;
	//std::cout << "";
	for (i = 0; i < this->keysCount; i++) {
		if (!this->isLeaf)
			this->childs[i]->printNodeValues();
		std::cout << this->keys[i] << " ";
	}
	if (!this->isLeaf)
		this->childs[i]->printNodeValues();
}
