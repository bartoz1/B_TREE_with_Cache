#include "bTree.h"
#include <iostream>
#include <string>
#include "superCache.h"

bTree::bTree(int t) {
	order = t;
	elements = 0;
	minElem = t - 1;
	root = nullptr;
	cache = nullptr;
	cacheSize = 0;
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
		if (root->search(x) != -1)
			std::cout << x << " +" << '\n';
		else
			std::cout << x<<" -\n";
	}
}
int bTree::searchAndGetLvl(int x) {
	int lvl;
	if (root == nullptr)
		lvl = -1;
	else {
		lvl = root->search(x);		
	}
	return lvl;
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

void bTree::searchWithCache() {
	int sumNoCache = 0;
	int sumCache = 0;
	std::cin >> cacheSize;
	cache = new int[cacheSize];
	int nbr, searchRes;
	char ctrl='a';
	while (ctrl != '\n') {
		std::cin >> nbr;
		std::cin.get(ctrl);		// wczytanie spacji lub konca linii
		searchRes = searchAndGetLvl(nbr);
		if (searchRes == -1) 
			searchRes = getLeafLvl();

		sumNoCache += searchRes;
		
		if (!inCache(nbr)) {
			sumCache += searchRes;
			addToCache(nbr);
		}
	}
	std::cout << "NO CACHE: " << sumNoCache << " CACHE: " << sumCache << '\n';
}

void bTree::addToCache(int data) {
	shiftCache();
	cache[0] = data;
}

void bTree::shiftCache() {
	for (int i = cacheSize - 2; i >= 0; i--) {
		cache[i + 1] = cache[i];
	}
}

bool bTree::inCache(int data) const{
	for (int i = 0; i < cacheSize; i++) {
		if (cache[i] == data)
			return true;
	}
	return false;
}

int bTree::getLeafLvl() const{
	int lvl = 0;
	bTNode* checker = root;
	while (checker != nullptr) {
		lvl++;
		if (checker->isLeaf)
			break;
		checker = checker->childs[0];
	}
	return lvl;
}

void bTree::searchWithSuperCache() {
	int sumNoCache = 0;
	int sumCache = 0;
	std::cin >> cacheSize;
	superCache superCache(cacheSize);
	int nbr, searchRes;
	char ctrl = 'a';
	while (ctrl != '\n') {
		std::cin >> nbr;
		std::cin.get(ctrl);		// wczytanie spacji lub konca linii
		searchRes = searchAndGetLvl(nbr);

		if (searchRes == -1) {
			searchRes = getLeafLvl();;
		}

		if (!superCache.inCache(nbr)) {		// nie ma w cachu
			sumCache += searchRes;
			superCache.add(nbr);
		}

		sumNoCache += searchRes;
	}
	std::cout << "NO SUPER_CACHE: " << sumNoCache << " SUPER_CACHE: " << sumCache << '\n';
}

void bTree::delKey(int key) {
	bTNode* del = getNodeWithKey(key);
	if (del == nullptr)
		return;

	if (del->isLeaf && del->keysCount > 1) {
		del->removeKey(key);
	}
}

bTree::~bTree() {
	if (root != nullptr) 
		deleteChildren(root);
	
}
void bTree::deleteChildren(bTNode* parent) {
	for (int i = 0; i < parent->keysCount + 1; i++) {
		if (parent->childs[i] != nullptr) {
			deleteChildren(parent->childs[i]);
			delete parent->childs[i];
			parent->childs[i] = nullptr;
		}
	}
}

bTNode* bTree::getNodeWithKey(int key) {
	if (root == nullptr)
		return nullptr;

	bTNode* tmp1 = root;
	bTNode* found = nullptr;

	while (tmp1 != nullptr) {
		for (int i = 0;i < tmp1->keysCount; i++) {	// sprawdzenie wszystkich kluczy w tmp1
			if (tmp1->keys[i] == key) {
				found = tmp1;
				break;
			}
		}
		// wybieramy wlasciwe dziecko
		for (int i = 0;i < tmp1->keysCount; i++) {
			if (tmp1->keys[i] > key) {
				tmp1 = tmp1->childs[i];
				break;
			}
			if (i == tmp1->keysCount - 1) {
				tmp1 = tmp1->childs[i+1];
				break;
			}
		}
	}

	return found;
}
