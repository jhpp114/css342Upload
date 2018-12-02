template<class Object>
SList<Object>::SList( ) {
  init( );
}

template<class Object>
SList<Object>::SList( const SList &rhs ) {
  init( );
  *this = rhs;                                   // then assign rhs to this.
}

template<class Object> 
void SList<Object>::init( ) {
  for ( int i = 0; i < LEVEL; i++ ) {  // for each level
    // create the left most dummy nodes;
    header[i] = new SListNode<Object>;
    header[i]->prev = NULL;
    header[i]->down = ( i > 0 ) ? header[i - 1] : NULL;
    header[i]->up = NULL;
    if ( i > 0 ) header[i - 1]->up = header[i];

    // create the right most dummy nodes;
    header[i]->next = new SListNode<Object>;
    header[i]->next->next = NULL;
    header[i]->next->prev = header[i];
    header[i]->next->down = ( i > 0 ) ? header[i - 1]->next : NULL;
    header[i]->next->up = NULL;
    if ( i > 0 ) header[i - 1]->next->up = header[i]->next;
  }

  // reset cost.
  cost = 0;
}

template<class Object>
SList<Object>::~SList( ) {
  clear( );                                      // delete items starting 1st
  for ( int i = 0; i < LEVEL; i++ ) {
    delete header[i]->next;                      // delete the right most dummy
    delete header[i];                            // delete the left most dummy
  }
}

template<class Object>
bool SList<Object>::isEmpty( ) const {
  return ( header[0]->next->next == NULL );
}

template<class Object>
int SList<Object>::size( ) const {
  SListNode<Object> *p = header[0]->next; // at least the right most dummy
  int size = 0;

  for ( ; p->next != NULL; p = p->next, ++size );   
  return size;
}

template<class Object>
void SList<Object>::clear( ) {
// for each level, iterate from the first to last item.

     for ( int i = 0; i < LEVEL; i++ ) { 

      // Implement the rest by yourself //
      SListNode<Object> *items = header[i]->next; //first item
      //if next node is not NULL
      while(items->next != NULL){  
        SListNode<Object> *del = items;
        items = items->next; //connect to next item for delete
        delete del; // delete the current node
      }
      header[i]->next = items;
     }                                      
}

template<class Object>
void SList<Object>::insert( const Object &obj ) {
  // right points to the level-0 item before which a new object is inserted.
  SListNode<Object> *right = searchPointer( obj );
  SListNode<Object> *up = NULL;
  SListNode<Object> *down = NULL;

  if ( right->next != NULL && right->item == obj )  
    // there is an identical object
    return;

  // Implement the rest by yourself /////////////////////////////////////////
  SListNode<Object> *newNode = new SListNode<Object>; //create node
  newNode->item = obj; //put item
  newNode->down = NULL;
  newNode->up = NULL;
  newNode->next = right; //connect node
  newNode->prev = right->prev; //connect node
  right->prev = newNode; //connect node
  newNode->prev->next = newNode; //connect node

  down = newNode;

  int randomNumber = rand()%2; //random number generate
  
  int currentLevel = 0; //current level to limit the upper must less than LEVEL 
  while(randomNumber == 1 && ++currentLevel < LEVEL){
    
    up = new SListNode<Object>;
    //if null next
    while(right->up == NULL){
      right = right->next;
    }
    //not null upup
    right = right->up;
  
    up->item = obj; //put element
    up->down = down; //connect the node
    up->up = NULL;
    up->next = right; //connect the node
    up->prev = right->prev; //connect the node
    right->prev = up; //connect the node
    up->prev->next = up; //connect the node
    down->up = up;
    down = up;
    //check again for random number
    randomNumber = rand()%2;
  }
}

template<class Object> 
bool SList<Object>::find( const Object &obj ) {
  // p oints to the level-0 item close to a given object
  SListNode<Object> *p = searchPointer( obj );

  return ( p->next != NULL && p->item == obj );     // true if obj was found
}

template<class Object>
SListNode<Object> *SList<Object>::searchPointer( const Object &obj ) {
  SListNode<Object> *p = header[LEVEL - 1];     // start from the top left
  while ( p->down != NULL ) {                   // toward level 0
    p = p->down;                                // shift down once
    cost++;

    if ( p->prev == NULL ) {                    // at the left most item
      if ( p->next->next == NULL )              // no intermediate items
        continue;
      else {                                    // some intermadiate items
        if ( p->next->item <= obj )             // if 1st item <= obj
          p = p->next;                          // shift right to item 1
        cost++;
      }
    }

    while ( p->next->next != NULL && p->next->item <= obj ) {
      // shift right through intermediate items as far as the item value <= obj
      p = p->next;
      cost++;
    }
  }

  // now reached the bottom. shift right once if the current item < obj
  if ( p->prev == NULL || p->item < obj ) {
    p = p->next;
    cost++;
  }
  return p; // return the pointer to an item >= a given object.
}

template<class Object>
void SList<Object>::remove( const Object &obj ) {
  // p points to the level-0 item to delete
  SListNode<Object> *p = searchPointer( obj );      

  // validate if p is not the left most or right most and exactly contains the
  // item to delete
  if ( p->prev == NULL || p->next == NULL || p->item != obj )
    return;

  // Implement the rest by yourself /////////////////////////////////////////

  //Erase that up is not null
  if(p->up == NULL){
    SListNode<Object> *del = p;
    del->next->prev = del->prev;
    del->prev->next = del->next;
    delete del;
  }
  //Erase and Look till up is null
  while(p->up != NULL){
    SListNode<Object> *del = p; //make a temp to delete
    p = p->up; //move up
    del->next->prev = del->prev; //connect the node
    del->prev->next = del->next; //connect the node
    delete del;
  }

}

template<class Object>
const SList<Object> &SList<Object>::operator=( const SList &rhs ) {
  if ( this != &rhs ) { // avoid self-assignment
    clear( );           // deallocate old items
    
    int index;
    SListNode<Object> *rnode;
    for ( index = 0, rnode = rhs.header[0]->next; rnode->next != NULL;
	  rnode = rnode->next, ++index )
      insert( rnode->item );

    cost = rhs.cost;
  }
  return *this;
}

template<class Object>
int SList<Object>::getCost( ) const {
  return cost;
}

template<class Object>
void SList<Object>::show( ) const {
  cout << "contents:" << endl;
  for ( SListNode<Object> *col = header[0]; col != NULL; col = col->next ) {
    SListNode<Object> *row = col;
    for ( int level = 0; row != NULL && level < LEVEL; level++ ) {
      if ( row->prev == NULL )
	cout << "-inf\t";
      else if ( row->next == NULL )
	cout << "+inf\t";
      else
	cout << row->item << "\t";
      row = row->up;
    }
    cout << endl;
  }
}

