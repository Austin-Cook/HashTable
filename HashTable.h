//
// Created by austi_eef6ewn on 3/17/2022.
//

#ifndef HASH_TABLE_HASH_TABLE_H
#define HASH_TABLE_HASH_TABLE_H

#include <iostream>
#include <string>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
using namespace std;

template<class T>
class HashTable {
	int capacity;
	int size;
	list<T>* table;
	int (*hash)(string const&);

public:

	HashTable(int (*hash)(string const&)) : capacity(10), size(0), hash(hash) {
	  // Each slot is initialized with default value of list<T>
	  //  which is an empty list
	  table = new list<T>[capacity];
	  load_table();
	}
	~HashTable() {
	  save_table();
	  delete[] table;
	}

	string to_string() const {
	  stringstream ss;
	  for (int i = 0; i < capacity; i++) {
		ss << i << ": ";
		for (auto item : table[i]) {
		  ss << item << ",";
		}
		ss << endl;
	  }
	  return ss.str();
	}

	void print() const {
	  cout << to_string() << endl;
	}

	bool add(string const& value) {
	  if (size > capacity * 0.8) {
		_grow();
	  }

	  int pos = hash(value) % capacity;

	  // Is this item already in the table?
	  list<T> &bucket = table[pos];
	  bool found = (std::find(bucket.begin(), bucket.end(), value) != bucket.end());

	  if (found) {
		return false;
	  }

	  bucket.push_back(value);
	  size++;
	  return true;
	}

	bool remove(string const& value) {
	  int pos = hash(value) % capacity;

	  auto &bucket = table[pos];

	  auto iter = std::find(bucket.begin(), bucket.end(), value);

	  if (iter == bucket.end()) {
		return false;
	  }

	  bucket.erase(iter);
	  size--;
	  return true;
	}

	bool contains(string const& value) {
	  int pos = hash(value) % capacity;

	  // Is this item already in the table?
	  auto &bucket = table[pos];
	  return (std::find(bucket.begin(), bucket.end(), value) != bucket.end());
	}

	void _grow() {
	  auto old_table = table;
	  auto old_capacity = capacity;
	  capacity *= 2;
	  table = new list<T>[capacity];
	  size = 0;
	  for (int i = 0; i < old_capacity; i++) {
		for (auto item : old_table[i]) {
		  add(item);
		}
	  }
	  delete[] old_table;
	}

	void load_table() {
	  ifstream inFile("saveFile.txt");
		if(inFile.is_open()) {
		  while(!inFile.eof()) {
			T item;
			getline(inFile, item);
			if(item != "") {
			  add(item);
			}
		  }
		  inFile.close();
		} else {
		  cerr << "Error opening file" << endl;
	  }
	}

	void save_table() {
	  ofstream outFile("saveFile.txt");
	  if(outFile.is_open()) {
		for (int i = 0; i < capacity; i++) {
		  for (auto item: table[i]) {
			outFile << item << endl;
		  }
		}
		outFile.close();
	  } else {
		cerr << "Error opening file" << endl;
	  }
	}
};

#endif //HASH_TABLE_HASH_TABLE_H
