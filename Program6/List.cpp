 /*
@file List.cpp
*/

#include "List.h"

/*
Default list constructor that initialzies header to NULL.
*/
List::List()
{
	header = NULL; 
}

/*
Copy list constructor that creates a deep copy identical list of the list passed in as an argument. 
It is assumed that the argument passed in is an initialized list. 
*/
List::List(List &rhs)
{
	*this = rhs;
}

/*
Dafault list destructor that calls the clear function to deallocate all memory for the list then deletes the header. 
*/
List::~List() {
	clear();           // delete items starting 1st
	delete header;    // delete heaeder pointer
}

/*
Overloaded operator= function.
This is a helper function called on by the copy constructor to make a deep copy of the list passed in.
It is assumed that the argument passed in is an initialized list.
*/
List &List::operator=(const List &rhs) { 
	if (!rhs.isEmpty() && this != &rhs) // avoid self-assignment
	{ 
		clear();           // deallocate old items

		Node *copiedNode;
		for (copiedNode = rhs.header; copiedNode->next != NULL; copiedNode = copiedNode->next) 
		{
			append(copiedNode->item); //add item to calling object 
		}
		append(copiedNode->item); //add final item to calling object
	}
	return *this;
}

/*
Pre-condition: it is assumed that the calling object is a list. 
Post-condition: returns true if the list is empty.
*/
bool List::isEmpty() const 
{
	return (header == NULL);
}

/*
Pre-condition: assumed that the calling object is a list.
Post-condition: returns an int for the number of items in the list.
*/
int List::size() const
{
	if (isEmpty()) return 0; 
	else
	{  
		Node *newNode = header;
		int i = 1;
		for (; newNode->next != NULL; newNode = newNode->next, i++) {}
		return i;
	}
}

/*
Pre-condition: assumed that the calling object is a list.
Post-condition: clears all the nodes in the list and deletes the header. 
*/
void List::clear()
{
	if (!isEmpty())
	{
		Node *newNode = header; 
		Node *del;
		while (newNode->next != NULL)
		{
			del = newNode;
			newNode = newNode->next;
			delete del;
		}
		delete header;
		header = NULL;
	}
}

/*
Pre-condition: assumed that the obj passed in is an int 
Post-condition: appends the int passed in to the end of the list 
*/
void List::append(const int &obj)
{
	if (isEmpty()) //append at first node 
	{
		header = new Node();
		header->item = obj;
		header->next = NULL;
		return;
	}
	else //append at end of list 
	{
		Node *lastNode = goToPrevIndex(size() + 1);
		Node *newNode = new Node();
		newNode->item = obj;
		lastNode->next = newNode;
		newNode->next = NULL;
	} 
}

/*
Helper method 
Pre-condition: assumed that the argument passed in is an int 
Post-condition: returns a pointer to the node directly before the index passed in
*/
Node* List::goToPrevIndex(int index) 
{
	if (!isEmpty())
	{
		Node *newNode = header;
		for (int i = 0; i < index-1 && newNode->next != NULL; newNode = newNode->next, i++) {}
		return newNode;
	}
}

/*
Pre-condition: assumed that the arguments passed in are ints
Post-condition: returns true if obj was successfully inserted at the index specified 
*/
bool List::insert(const int &obj, int index)
{
	if (index > size() - 1 || index < 0) return false; //inserting at index that is out of range
	else if (index == 0) //inserting at first node
	{
		if (isEmpty()) //when list is empty 
		{
			header = new Node();
			header->item = obj;
			header->next = NULL;
		}
		else //when list isnt empty 
		{
			Node *oldHead = header; 
			header = new Node();
			header->item = obj;
			header->next = oldHead;
		}
	}
	else if (index == size() - 1) //inserting after last node
	{
		append(obj); 
		return true;
	}
	else //inserting somewhere in the middle 
	{
		Node *insert = new Node();
		insert->item = obj;
		Node *prevNode = goToPrevIndex(index);
		insert->next = prevNode->next;
		prevNode->next = insert;
		return true;
	}
	return false;
}

/*
Pre-condition: assumed that the argument passed in is an int
Post-condition: returns true if the obj was successfully removed from the list 
*/
bool List::remove(const int &obj)
{
	if (isEmpty()) return false;
	else
	{
		Node *remove = header;
		for (int i = 0; i < size(); remove = remove->next, i++)
		{
			if (remove->item == obj)
			{
				if (remove == header)  //obj is the first item in the list
				{
					header = header->next;
					delete remove;
					return true;
				}
				else if (remove->next == NULL) //obj is the last item in the list 
				{
					Node *newNode = goToPrevIndex(size()-1);
					newNode->next = NULL;
					delete remove;
					return true;
				}
				else //obj is in the middle of list 
				{
					Node *newNode = goToPrevIndex(i);
					newNode->next = remove->next;
					delete remove;
					return true;
				}
			}
		}
	}
	return false;
}

/*
Pre-condition: assumed that the calling object is an initialized list 
Post-condition: prints out the contents of the list in a single line 
*/
void List::print() const
{
	if (!isEmpty())
	{
		cout << "List contents:" << endl;
		Node *newNode;
		for (newNode = header; newNode->next != NULL; newNode = newNode->next)
		{
			cout << newNode->item << " ";
		}
		cout << newNode->item;
		cout << endl;
	}
}

/*
Heler method for the reverseRecursive(Node *, Node *, Node *) method 
*/
void List::reverseRecursive()
{
	reverseRecursive(header, header->next, NULL);
}

/*
Pre-condition: assumed that the calling object is an initialzied list. ptrOne is initialized to header. 
ptrTwo is initialized to header->next. prevNode is initialized to NULL.
Post-condition: uses recursion to reverse the order of the list
*/
void List::reverseRecursive(Node *ptrOne, Node *ptrTwo, Node *prevNode)
{
	if (!isEmpty())
	{
		if (ptrTwo != NULL) 
		{
			if (ptrTwo->next != NULL) //reassemble link and recurse 
			{
				Node *t1 = ptrTwo;
				Node *t2 = ptrTwo->next;
				ptrOne->next = prevNode;
				prevNode = ptrOne;
				reverseRecursive(t1, t2, prevNode);
			}
			else //base case 
			{
				ptrTwo->next = ptrOne;
				ptrOne->next = prevNode;
				header = ptrTwo;
			}
		}
	}
}

/*
Pre-condition: assumed that the calling object is an initialzied list
Post-condition: reverses the order of the list iteratively 
*/
void List::reverseIterative()
{
	if (!isEmpty())
	{
		Node *curNode = header;

		Node *prevNode = new Node();
		prevNode = NULL;

		Node *nextNode = new Node();
		nextNode = NULL;

		while (curNode != NULL) //reverse links of list 
		{
			nextNode = curNode->next;
			curNode->next = prevNode;
			prevNode = curNode;
			curNode = nextNode;
		}
		header = prevNode; //set header to "last" node which is now the first node in list 
	}
}

