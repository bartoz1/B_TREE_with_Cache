#include "superCache.h"

superCache::superCache(int size) {
	cache = new cData[size];
	this->size = size;
}

void superCache::add(int data) {
	bool alreadyIn = false;
	int where;

	where = search(data);

	if (where != -1)
		alreadyIn = true;
	
	if (!alreadyIn) {	 // jezeli wartosci nie ma w cachu	
		for (int i = 0; i < size; i++) {	// wybranie wolnego miejsca
			if (cache[i].isUsed == false) {	
				where = i;
				cache[i].isUsed = true;
				break;
			}
		}

		if (where == -1) {	// jezeli nie znaleziono wolnego miejsca
			int min = 99999;
			int minI = -1;
			for (int i = 0; i < size; i++) {
				if (cache[i].isUsed && cache[i].uses <= min) {
					min = cache[i].uses;
					minI = i;
				}
			}
			where = minI;
		}

		if (where != -1) {	// jezeli znaleziono miejsce
			cache[where].data = data;
			cache[where].uses = 1;
			cache[where].isUsed = true;
		}
	}
}
// sprawdzenie czy wartosc jest juz caschu
int superCache::search(int data) {
	for (int i = 0; i < size; i++) {	
		if (cache[i].data == data) {
			cache[i].uses++;
			return i;
		}
	}
	return -1;
}

bool superCache::inCache(int data) {
	for (int i = 0; i < size; i++) {
		if (cache[i].data == data) {
			return true;
		}
	}
	return false;
}
