#pragma once

struct cData {
	int data;
	int uses;
	bool isUsed;
	cData() {
		this->data = 0;
		this->uses = 0;
		this->isUsed = false;
	}
};
class superCache {
	cData* cache;
	int size;
public:
	superCache(int size);
	void add(int data);
	int search(int data);
	bool inCache(int data) const;
	~superCache();

};

