template<class Object>
int TransposeList<Object>::find( const Object &obj ) {
  DListNode<Object> *found = DList<Object>::header->next;

  int i = 0;
  for ( ; found != NULL && found->item != obj;  found = found->next, ++i )
    ++DList<Object>::cost;

  if ( found == NULL )
    return -1; // not found

  if ( found == DList<Object>::header->next )
    return 0;  // no need to swap

  // remove found from the current position
  // insert found before previous
  // remember the current previous data

  DListNode<Object> *previous = found->prev;
  if(found->next != NULL){
    previous->next = found->next;
    found->next->prev = previous;
  }else{
    previous->next = NULL;
  }
  found->next = previous;
  found->prev = previous->prev;
  previous->prev->next = found;
  previous->prev = found;
  

  return i;
}
