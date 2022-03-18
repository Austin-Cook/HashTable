#include <iostream>
#include "HashTable.h"
#include <fstream>

/*
 * Hash function for the Hash Table
 */
int string_hash(string const& value) {
  int result = 0;
  for (auto c : value) {
	result += int(c);
  }
  return result;
}

int main(int argc, char* argv[]) {
  HashTable<string> hashTable(&string_hash);

  //Store command line parameters
  string func;
  string item;
  if(argc == 2 || argc == 3) {
	func = argv[1];
  }
  if(argc == 3) {
	item = argv[2];
  }

  //Process commands
  while(func != "q") {
	if (func == "print") {
	  cout << "Printing" << endl << endl;
	  hashTable.print();
	} else if (func == "add") {
	  cout << "Adding" << endl << endl;
	  hashTable.add(item);
	} else if (func == "remove") {
	  cout << "Removing" << endl << endl;
	  hashTable.remove(item);
	}

	cout << "Enter function (print, add, remove, or q to quit): " << endl;
	cin >> func;
	if(func == "add" || func == "remove") {
	  cout << "Enter item: " << endl;
	  cin >> item;
	}
  }

  return 0;
}
