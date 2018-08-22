/*
@file driver.cpp
This is the driver file for the list class that contains tests for the functions in the list class 
*/

#include <iostream>
#include "List.h"

using namespace std;

int main()
{
	List *intList = new List();

	//tests for append
	intList->append(3);
	intList->append(9);
	intList->append(5);
	cout << "intList ";
	intList->print();
	cout << endl;

	//test to see if goToPrevNode performs properly
	cout << "Node at index 1: " << (intList->goToPrevIndex(2))->item << endl;
	cout << "Node at index 0: " << (intList->goToPrevIndex(1))->item << endl;
	cout << endl;
	
	//tests for insert
	intList->insert(6, 0);
	intList->insert(4, 1);
	intList->insert(1, 2);
	intList->insert(3, 2);
	intList->insert(6, 3);
	intList->insert(3, 3);
	intList->insert(9, 4);
	intList->insert(7, 4);
	intList->insert(2, 5);
	intList->insert(8, intList->size() - 1);
	cout << "intList ";
	intList->print();
	cout << endl;

	//test for copy constructor 
	List *intList2 = new List(*intList);
	cout << "intList ";
	intList->print();
	cout << "intList2 ";
	intList2->print();
	cout << endl;

	//test to append the intList2 to see if intList is altered (intList shouldnt be altered because copy constructor makes deep copy)
	intList2->append(8);
	cout << "intList ";
	intList->print();
	cout << "intList2 ";
	intList2->print();
	cout << endl;

	//test for size
	cout << "Size of intList: " << intList->size() << endl;
	cout << "Size of intList2: " << intList2->size() << endl;
	cout << endl;

	//test for clear 
	intList->clear();
	cout << "Is intList empty? " << intList->isEmpty() << endl;
	cout << endl;

	//test for remove 
	intList2->remove(6);
	intList2->remove(8);
	intList2->remove(8);
	cout << "intList2 ";
	intList2->print();
	cout << endl;

	//test for iterative reversal 
	cout << "intList2 reversed iteratively ";
	intList2->reverseIterative();
	intList2->print();
	cout << endl;

	//test for recursive reversal 
	cout << "intList2 reversed recursively ";
	intList2->reverseRecursive();
	intList2->print();
	cout << endl;

	intList2->clear();
	cout << "Is intList2 empty? " << intList->isEmpty() << endl;
	cout << endl;
}