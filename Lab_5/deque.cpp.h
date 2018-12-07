template <class Object>
Deque<Object>::Deque( ) {                          // the constructor
  front = back = NULL;
}

template <class Object>
Deque<Object>::Deque( const Deque &rhs ) {         // the copy constructor
  front = back = NULL;
  *this = rhs;
}

template <class Object>
Deque<Object>::~Deque( ) {                         // the destructor
  clear( );
}

template <class Object>
bool Deque<Object>::isEmpty( ) const {             // check if a deque is empty
  return front == NULL;
}

template <class Object>
int Deque<Object>::size( ) const {                 // retrieves # deque nodes
  int i = 0;
  for ( DequeNode *ptr = front; ptr != NULL; ptr = ptr->next ) // traverse que
    ++i;

  return i;
}

template <class Object>
const Object &Deque<Object>::getFront( ) const {   // retrieve the front node
  if ( isEmpty( ) )
    throw "empty queue";
  return front->item;
}

template <class Object>
const Object &Deque<Object>::getBack( ) const {    // retrieve the tail node
  if ( isEmpty( ) )
    throw "empty queue";
  return back->item;
}

template <class Object>
void Deque<Object>::clear( ) {          // clean up all entries.
  while ( !isEmpty( ) )                 // dequeue till the queue gets empty.
    removeFront( );
}

template <class Object>
void Deque<Object>::addFront( const Object &obj ) {// add a new node to  front
  // Implement the function body.

  //create node
  DequeNode *newNode = new DequeNode;
  newNode->item = obj; //item
  newNode->next = front; 
  newNode->prev = NULL;
  
  //if it is empty
  if(isEmpty()){
    back = newNode;
  }
  //if it is not empty
  else{
    front->prev = newNode;
  }
  //set front to newnode
  front = newNode;
}

template <class Object>
void Deque<Object>::addBack( const Object &obj ) { // add a new node to tail
  // Implement the function body.

  //create node
  DequeNode *newNode = new DequeNode;
  newNode->item = obj;
  newNode->next = NULL;
  newNode->prev = back;
  
  //if it is empty
  if(isEmpty()){
    front = newNode;
  }
  //not empty
  else{
    back->next = newNode;
  }
  //set newnode to back
  back = newNode;
}

template <class Object>
Object Deque<Object>::removeFront( ) {  // remove the front node
  //reuse function getfront
  Object F_Item = getFront();
  DequeNode *temp = front;
  //if it has 1
  if(front == back){
    front = back = NULL;
  }
  
  else{
    front = front->next;
    front->prev = NULL;
  }
  
  delete temp;
  return F_Item;
}

template <class Object>
Object Deque<Object>::removeBack( ) {   // remove the tail node
  // Implement the function body.

  //reuse the function getBack
  Object B_Item = getBack();
  DequeNode *temp = back;

  //if it has 1
  if(back == front){
    back = front = NULL;
  }
  else{
    back->prev->next = NULL;
    back = back->prev;
  }
 
  delete temp;
  return B_Item;
}

template <class Object>
const Deque<Object> &Deque<Object>::operator=( const Deque &rhs ) { // assign
  if ( this != &rhs ) { // avoid self assignment
    clear( );
    for ( DequeNode *rptr = rhs.front; rptr != NULL; rptr = rptr->next )
      addBack( rptr->item );
  }
  return *this;
}


