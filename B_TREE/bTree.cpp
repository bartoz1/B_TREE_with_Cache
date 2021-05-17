#include "bTree.h"
#include <iostream>
#include <string>

bTree::bTree(int t) {
	order = t;
	elements = 0;
	minElem = t - 1;
	root = nullptr;
}

void bTree::add(int data) {
	if (root == nullptr) {	// brak elementow
		root = new bTNode(order, true);
		root->keys[0] = data;
		root->keysCount = 1;
	}
	else {
		if (root->keysCount >= order * 2 - 1) {		// brak miejsca w roocie

			bTNode* newRoot = new bTNode(order, false);
			newRoot->childs[0] = root;
			newRoot->splitNode(0, root);

			if (data > newRoot->keys[0])
				newRoot->childs[1]->addKey(data);
			else
				newRoot->childs[0]->addKey(data);
			root = newRoot;
		}
		else {
			root->addKey(data);
		}


	}
}

void bTree::printTree() {
	if (root != nullptr) {
		std::cout << order << "\n";
		root->printNode();

	}
	else
		std::cout << "null\n";
}
void bTree::printValues() {
	if (root != nullptr)
		root->printNodeValues();
	else
		std::cout << "null";
	std::cout << "\n";
}
void bTree::search(int x) {
	if (root == nullptr)
		std::cout << x<<" -\n";
	else {
		if(root->search(x) == true)
			std::cout << x<<" +\n";
		else
			std::cout << x<<" -\n";
	}
}

void bTree::loadTree() {
	std::string odp;
	std::cin >> odp;

	//std::cin.get();		// wczytanie spacji lub konca linii
	if (odp == "(") {
		root = loadNode();
	}
}
bTNode* bTree::loadNode() {
	bool hasChild = false;
	int iKey = 0;		// iterator kluczy 
	int iChil = 0;		// iterator dzieci
	bTNode* newNode = new bTNode(order, false);
	std::string odp;
	char control;
	while (odp != ")") {
		std::cin.get(control);		// wczytanie spacji lub konca linii
		if (control == '\n') {
			if (!hasChild)
				newNode->setLeaf();
			newNode->keysCount = iKey;
			break;
		}
		std::cin >> odp;
		if (odp == "(") {
			newNode->childs[iChil] = loadNode();
			iChil++;
			hasChild = true;
		}
		else if (odp == ")") {		// koniec obecnego noda
			if (!hasChild)			// jezeli nie ma dzieci to jest lisciem
				newNode->setLeaf();
			newNode->keysCount = iKey;
		}
		else {	// wczytanie danych
			newNode->keys[iKey] = std::stoi(odp);
			iKey++;
		}
	}
	return newNode;
}
