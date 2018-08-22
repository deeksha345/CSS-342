//Already defined function 
template <class Object>
Deque<Object>::Deque( ) {                          // the constructor
  front = back = NULL;
}

//Already defined function 
template <class Object>
Deque<Object>::Deque( const Deque &rhs ) {         // the copy constructor
  front = back = NULL;
  *this = rhs;
}

//Already defined function 
template <class Object>
Deque<Object>::~Deque( ) {                         // the destructor
  clear( );
}

//Already defined function 
template <class Object>
bool Deque<Object>::isEmpty( ) const {             // check if a deque is empty
  return front == NULL;
}

//Already defined function 
template <class Object>
int Deque<Object>::size( ) const {                 // retrieves # deque nodes
  int i = 0;
  for ( DequeNode *ptr = front; ptr != NULL; ptr = ptr->next ) // traverse que
    ++i;

  return i;
}

//Already defined function 
template <class Object>
const Object &Deque<Object>::getFront( ) const {   // retrieve the front node
  if ( isEmpty( ) )
    throw "empty queue";
  return front->item;
}

//Already defined function 
template <class Object>
const Object &Deque<Object>::getBack( ) const {    // retrieve the tail node
  if ( isEmpty( ) )
    throw "empty queue";
  return back->item;
}

//Already defined function 
template <class Object>
void Deque<Object>::clear( ) {          // clean up all entries.
  while (!isEmpty())                 // dequeue till the queue gets empty.
  {
	  removeFront();
  }
}

/*
Pre-condition: obj to be inserted isnt null
Post-condition: obj is added to the front of the deque
*/
template <class Object>
void Deque<Object>::addFront( const Object &obj ) {// add a new node to  front
	if (isEmpty()) //add first node in empty deque
	{
		DequeNode *newNode = new DequeNode;
		newNode->item = obj;
		front = newNode;
		back = front;
	}
	else //add obj before first node in deque 
	{
		DequeNode *newNode = new DequeNode;
		DequeNode *frontNode = front;
		newNode->item = obj;
		newNode->next = frontNode;
		frontNode->prev = newNode;
		newNode->prev = NULL;
		front = newNode;
	}
}

/*
Pre-condition: obj to be inserted isnt null
Post-condition: obj is added to the end of the deque
*/
template <class Object>
void Deque<Object>::addBack( const Object &obj ) { // add a new node to tail
	if (isEmpty()) //add first node in empty deque 
	{
		DequeNode *newNode = new DequeNode;
		newNode->item = obj;
		front = newNode;
		back = front;
	}
	else //add obj after last node in deque 
	{
		DequeNode *newNode = new DequeNode;
		DequeNode *tailNode = back;
		newNode->item = obj;
		newNode->next = NULL;
		tailNode->next = newNode;
		newNode->prev = tailNode;
		back = newNode;
	}
}

/*
Pre-condition: obj to be inserted isnt null
Post-condition: the first node of the deque is removed 
*/
template <class Object>
Object Deque<Object>::removeFront( ) {  // remove the front node
	if (!isEmpty())
	{
		if (size() == 1) //removing from a deque of one node
		{
			Object returnItem = front->item;
			delete front;
			front = NULL;
			back = NULL;
			return returnItem;
		}
		else //remove first node in deque of over 1 node 
		{
			DequeNode *frontNode = front;
			Object returnItem = frontNode->item;
			frontNode->next->prev = NULL;
			front = frontNode->next;
			frontNode->next = NULL;
			delete frontNode;
			return returnItem;
			
		}
	}
}

/*
Pre-condition: obj to be inserted isnt null
Post-condition: the first node of the deque is removed
*/
template <class Object>
Object Deque<Object>::removeBack( ) {   // remove the tail node
	if (!isEmpty())
	{
		if (size() == 1) //removing from a deque of one node
		{
			Object returnItem = front->item;
			delete front;
			front = NULL;
			back = NULL;
			return returnItem;
		}
		else //remove last node in deque of over 1 node 
		{
			DequeNode *tailNode = back;
			Object returnItem = tailNode->item;
			tailNode->prev->next = NULL;
			back = tailNode->prev;
			tailNode->prev = NULL;
			delete tailNode;
			return returnItem;
		}
	}
}

//Already defined function 
template <class Object>
const Deque<Object> &Deque<Object>::operator=( const Deque &rhs ) { // assign
  if ( this != &rhs ) { // avoid self assignment
    clear( );
	int i = 2; //FOR TESTING PURPOSES REMOVE WHEN DONE 
	for (DequeNode *rptr = rhs.front; rptr != NULL; rptr = rptr->next)
	{
		addBack(rptr->item);
		i++; //FOR TESTING PURPOSES REMOVE WHEN DONE 
	}
  }
  return *this;
}


