// temporary implementation of HashSet using separate chaining
#include <vector>
#include <list>
#include <algorithm>
#include "Athlete.h"
using namespace std;

class HashSet {
	private:
	int size, CAPACITY;
	double load_factor; // if size >= LF * CAPACITY we will double CAPACITY
	vector<list<int>> table; // use of list nested in vector allows for separate chaining to resolve conflicts

	int hash(int key) {
		return key % CAPACITY; // hash function we're using is very simple
	}

	list<int>::iterator search(int key) {
		int h = hash(key);
		return find(table[h].begin(), table[h].end(), key);
	}

	void rehash() {
	  size = 0;
		CAPACITY = max(2, CAPACITY); // make sure CAPACITY is at minimum 2 in any case
		vector<list<int>> old_table(move(table)); // change!
		table = vector<list<int>>(CAPACITY);
		
		for (list<int>& chain: old_table)
			for (int& key: chain)
				add(key);
	}

public:
	HashSet() {
		size = 0;
		CAPACITY = 2;
		load_factor = 0.75;
		table.resize(CAPACITY);
	}
	
	void add(int key) {
		if (contains(key))
			return;
		
		size++;
		int h = hash(key);
		table[h].push_back(key);
		
		if (size >= load_factor * CAPACITY) {
			CAPACITY *= 2;
			rehash();
		}
	}
	
	void remove(int key) {
		int h = hash(key);
		auto it = search(key);
		
		if (it == table[h].end())
			return;
		
		size--;
		table[h].erase(it);
		
		if (size <= 0.5 * load_factor * CAPACITY) {
			CAPACITY /= 2;
			rehash();
		}
	}
	
	bool contains(int key) {
		int h = hash(key);
		return search(key) != table[h].end();
	}
};