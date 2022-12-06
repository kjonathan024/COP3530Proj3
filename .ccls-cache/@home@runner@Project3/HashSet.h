#pragma once
#include "Athlete.h"
#include <algorithm>
#include <forward_list>
#include <vector>

using namespace std;

class HashSet {
private:
  int size, CAPACITY;
  double load_factor; // if size >= LF * CAPACITY we will double CAPACITY
  vector<forward_list<Athlete>> set; // use of list nested in vector allows for
                                     // separate chaining to resolve conflicts

  int hash(Athlete &ath) {
    return stoi(ath.getID()) %
           CAPACITY; // hash function bases off modulo of unique ID of athletes
                     // by CAPACITY (pretty simple)
  }

  int hash(string& id) {
      return stoi(id) % CAPACITY;
  }

  void rehash() {
    size = 0;
    CAPACITY =
        max(2, CAPACITY); // make sure CAPACITY is at minimum 2 in any case
    vector<forward_list<Athlete>> prev_set = set;
    set = vector<forward_list<Athlete>>(CAPACITY);

    for (forward_list<Athlete> &chain : prev_set) {
      for (Athlete &ath : chain)
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

    if (size >= load_factor *
                    CAPACITY) { // check if we need to increase CAPACITY of set!
      CAPACITY *= 2;
      rehash();
    }
  }

  forward_list<Athlete>::iterator
  search(Athlete& ath) { // returns iterator to the location of the Athlete (if it exists)
    int h = hash(ath);
    for (auto iter = set[h].begin(); iter != set[h].end(); iter++)
        {
            if (*iter == ath)
                return iter;
        }
    return set[h].end();
  }

   forward_list<Athlete>::iterator searchID(string id) { 
    int h = hash(id);
    for (auto iter = set[h].begin(); iter != set[h].end(); iter++)
        {
            if (iter->getID() == id)
                return iter;
        }
    return set[h].end();
  }

  bool contains(Athlete ath) {
    int h = hash(ath);
    return search(ath) != set[h].end();
  }
};