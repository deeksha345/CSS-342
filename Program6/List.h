/*
@file List.h
Header file for the list class 
Is a list of functions used to create, delete, modify, and display the list 
*/

#ifndef LIST_H
#define LIST_H

#include <iostream> 

using namespace std;

struct Node {                  // a list node
	int item;
	Node *next;
};

class List {
public:
	List();                                             // the constructor
	List(List &);                                       // the copy constructor
	~List();                                            // the destructor

	bool isEmpty() const;                               // checks if a list is empty.
	int size() const;                                   // retrieves # list nodes;
	void clear();                                       // clean up all list entries.
	bool insert(const int &, int);                      // insert a new object at the following index 
	void append(const int &);                           //appends obj to end of list 
	Node* goToPrevIndex(int);                           //returns a pointer to the node before index 
	bool remove(const int &);                          // remove a given object
	List &operator=(const List &);                    // assignment
	void print() const;                              // show the data structure
	void reverseRecursive(Node *, Node *, Node *);  //reverses the order of obj list recursively 
	void reverseIterative();                       //reverses the order of obj list iteratively 
	void reverseRecursive();                      //helper method 
	Node *header;                                // header
};

#endif
