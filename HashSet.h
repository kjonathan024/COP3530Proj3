// temporary implementation of HashSet using separate chaining
#include <vector>
#include <forward_list>
#include <algorithm>
#include "Athlete.h"
using namespace std;

class HashSet {
private:
    int size, CAPACITY;
	double load_factor; // if size >= LF * CAPACITY we will double CAPACITY
	vector<forward_list<Athlete>> set; // use of list nested in vector allows for separate chaining to resolve conflicts

	int hash(Athlete& ath) {
		return stoi(ath.getID()) % CAPACITY; // hash function bases off modulo of unique ID of athletes by CAPACITY (pretty simple)
	}

	void rehash() {
	  size = 0;
		CAPACITY = max(2, CAPACITY); // make sure CAPACITY is at minimum 2 in any case
		vector<forward_list<Athlete>> prev_set = set; 
		set = vector<forward_list<Athlete>>(CAPACITY);
		
		for (forward_list<Athlete>& chain: prev_set) {
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
		set[h].push_front(ath);
		
		if (size >= load_factor * CAPACITY) { // check if we need to increase CAPACITY of set!
			CAPACITY *= 2;
			rehash();
		}
	}
	
	void remove(Athlete ath) { // in here for now as base functionality but likely don't need for our project
		int h = hash(ath);
		
		if (!contains(ath)) // not in set!
			return;
		
		size--;
		set[h].remove(ath); //delete from list
		
		if (size <= 0.5 * load_factor * CAPACITY) { // check if we can reduce the CAPACITY of the hashset (to reduce used space)
			CAPACITY /= 2;
			rehash();
		}
	}

	forward_list<Athlete>::iterator search(Athlete& ath) { // returns iterator to the location of the Athlete (if it exists)
		int h = hash(ath);
		return find(set[h].begin(), set[h].end(), ath);
	}
	
	bool contains(Athlete ath) {
		int h = hash(ath);
		return search(ath) != set[h].end();
	}
};