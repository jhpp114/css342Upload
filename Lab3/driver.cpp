#include <iostream>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <fstream>
#include "bubblesort.cpp"
#include "insertionsort.cpp"
#include "selectionsort.cpp"

// array initialization with random numbers
void initArray( vector<int> &array, int randMax ) {
  int size = array.size( );

  for ( int i = 0; i < size; ) {
    int tmp = ( randMax == -1 ) ? rand( ) : rand( ) % randMax;
    bool hit = false;
    for ( int j = 0; j < i; j++ ) {
      if ( array[j] == tmp ) {
        hit = true;
        break;
      }
    }
    if ( hit )
      continue;
    array[i] = tmp;
    i++;
  }
}

// array printing
void printArray( vector<int> &array, char arrayName[] ) {
  int size = array.size( );

  for ( int i = 0; i < size; i++ )
    cout << arrayName << "[" << i << "] = " << array[i] << endl;
}

int elapsed( timeval &startTime, timeval &endTime ) {
  return ( endTime.tv_sec - startTime.tv_sec ) * 1000000 
    + ( endTime.tv_usec - startTime.tv_usec );
}

int main( int argc, char* argv[] ) {
  ofstream outfile;
  outfile.open("compare.txt"); //Create an output file with "compare.txt" filename.
  outfile<<"size \t bubble \t insertion \t selection \n";
  int size = 20;
  int rnd = 1;
  struct timeval startTime, endTime;
  
  while(size <= 5000){
    
    srand(size); //random number
    vector<int> items(size); //create vector with size, size will be increase till equal to 5000
    initArray(items, size); //use given function store elements to the vector
    vector<int> item2 = items; //copy the vector
    vector<int> item3 = items; //copy the vector
    
    int bubbleTime, insertTime, selectionTime; //create variable for elapsed
    
    //get time for bubble sort
    gettimeofday( &startTime, 0 );
    bubblesort( items);
    gettimeofday( &endTime, 0 );
    bubbleTime = elapsed( startTime, endTime );

    //get time for insertion sort
    gettimeofday( &startTime, 0 );
    insertionsort( item2);
    gettimeofday( &endTime, 0 );
    insertTime = elapsed( startTime, endTime );
    
    //get time for selection sort
    gettimeofday( &startTime, 0 );
    selectionsort( item3);
    gettimeofday( &endTime, 0 );
    selectionTime = elapsed( startTime, endTime );
`
    //print
    outfile << size << "\t\t" << bubbleTime << "\t\t" << insertTime << "\t\t" << selectionTime << "\n";
    size+=20; //size increase  
  }

  // Complete your program here. You can use while or for statement. 
  //Size should be increment by 20 until the size of array becomes 5,000
  
  // Random generation will need the following method.
  /*
  srand(number)
  */
  
  // Here is the example to get the time for a bubblesort.
  ///////////////////////////////////
  /*gettimeofday( &startTime, 0 );
   bubblesort( items1);
   gettimeofday( &endTime, 0 );
   int e_time = elapsed( startTime, endTime );
  */
  
 
	outfile.close();

  return 0;
}
