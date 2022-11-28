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
	vector<list<Athlete>> set; // use of list nested in vector allows for separate chaining to resolve conflicts

	int hash(Athlete& ath) {
		return stoi(ath.getID()) % CAPACITY; // hash function bases off modulo of unique ID of athletes by CAPACITY (pretty simple)
	}

	list<Athlete>::iterator search(Athlete& ath) { // returns iterator to the location of the Athlete (if it exists)
		int h = hash(ath);
		return find(set[h].begin(), set[h].end(), ath);
	}

	void rehash() {
	  size = 0;
		CAPACITY = max(2, CAPACITY); // make sure CAPACITY is at minimum 2 in any case
		vector<list<Athlete>> prev_set(move(set)); // using 
		set = vector<list<Athlete>>(CAPACITY);
		
		for (list<Athlete>& chain: prev_set) {
            for (Athlete& ath: chain)
				add(ath);
        }	
	}

public:
	HashSet() {
		size = 0;
		CAPACITY = 2;
		load_factor = 0.7;
		set.resize(CAPACITY);
	}
	
	void add(Athlete ath) {
		if (contains(ath))
			return;
		
		size++;
		int h = hash(ath);
		set[h].push_back(ath);
		
		if (size >= load_factor * CAPACITY) {
			CAPACITY *= 2;
			rehash();
		}
	}
	
	void remove(Athlete ath) { // double check logic if this actually makes sense to do
		int h = hash(ath);
		auto iter = search(ath);
		
		if (iter == set[h].end()) // not in set!
			return;
		
		size--;
		set[h].erase(iter);
		
		if (size <= 0.5 * load_factor * CAPACITY) { // check if we can reduce the CAPACITY of the hashset (to reduce used space)
			CAPACITY /= 2;
			rehash();
		}
	}
	
	bool contains(Athlete ath) {
		int h = hash(ath);
		return search(ath) != set[h].end();
	}
};