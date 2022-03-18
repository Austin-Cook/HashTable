//
// Created by austi_eef6ewn on 3/17/2022.
//

#include <iostream>
#include "HashTable.h"

int string_hash(string const& value) {
  int result = 0;
  for (auto c : value) {
	result += int(c);
  }
  return result;
}

int main() {
  cout << "In test.cpp" << endl;

  HashTable<string> myTable(&string_hash);

  //Test print
  myTable.print();

  //Test add
  myTable.add("One");
  myTable.add("Two");
  myTable.add("Three");
  myTable.add("Four");
  myTable.add("Five");
  myTable.add("Six");
  myTable.add("Seven");
  myTable.add("Eight");
  myTable.add("Nine");
  myTable.add("Ten");
  myTable.add("Ten");		//Test duplicate value
  myTable.print();

  //Test remove
  myTable.remove("One");
  myTable.remove("Two");
  myTable.remove("Three");
  myTable.remove("Four");
  myTable.remove("Five");
  myTable.print();

  return 0;
}