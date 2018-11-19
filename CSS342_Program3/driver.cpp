#include <iostream>
#include <vector>
#include <sys/time.h>
#include <fstream>
#include <stdlib.h>
#include "mergesort.cpp"
#include "quicksort.cpp"
#include "mergeImproved.cpp"

using namespace std;

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

//performance evaluation function
int elapsed( timeval &startTime, timeval &endTime ) {
  return ( endTime.tv_sec - startTime.tv_sec ) * 1000000 
    + ( endTime.tv_usec - startTime.tv_usec );
}

//main function
int main( int argc, char* argv[] ) {  
  struct timeval startTime, endTime;

//===============Just output improved mergesort program (when #items = 30)==========
/*
  Read me! 
  From here to 
  below to "End of Read me" is 
  Just for printing output for when number of items = 30
  So, uncomment "Everything" till "End of Read me"
  If you think it is unnecessary
*/
  //verify arguments
  if(argc != 2){
    cerr << "usage: quicksort size" << endl;
    return -1;
  }

  //verify an array size
  int size = atoi(argv[1]);
  if(size <= 0){
    cerr << "array size must be positive" << endl;
    return -1;
  }
  
  //array generation
  srand(1);
  vector<int> items(size);
  initArray(items, size);
  cout << "initial:" << endl;
  printArray(items, "items");

  //mergesort
  mergeImproved(items);
  cout << "sorted:" << endl;
  printArray(items, "items");


/*
  End of Read Me
  Uncomment all these "Above" if you don't need
  to just output improved mergesort program (when #items = 30)
  ./aout 30
*/ 


//====================To create compare.txt that contains data of compare running time=============
/*
  Compare running time among recurisve, improved mergesort and quicksort
*/
//file generate
  ofstream outfile;
  outfile.open("compare.txt"); //Create an output file with "compare.txt" filename.
  outfile<<"size \t\t Recursive Mergesort \t\t Improved Mergesort \t\t Usual Quicksort \n";
  
  int sizeForCompare = 20;
  int rnd = 1;

  // array generation
  //looping [20, 1000]
  while(sizeForCompare <= 1000){
 
  // array generation
    srand(sizeForCompare);
    vector<int> item1Compare(sizeForCompare);
    initArray(item1Compare,sizeForCompare);

  //require 2 more vector for other two sorting algorithm
    vector<int> item2Compare = item1Compare; //copy elements
    vector<int> item3Compare = item1Compare; //copy elements
  
  //assign variable for name
    int usualMerge, improvedMerge, usualQuick;

  //get time of three sorting algorithm
  
    gettimeofday(&startTime, 0);
    mergesort(item1Compare);
    gettimeofday(&endTime, 0);
    usualMerge = elapsed(startTime, endTime);

    gettimeofday(&startTime, 0);
    mergeImproved(item2Compare);
    gettimeofday(&endTime, 0);
    improvedMerge = elapsed(startTime, endTime);
    
    gettimeofday(&startTime,0);
    quicksort(item3Compare);
    gettimeofday(&endTime, 0);
    usualQuick = elapsed(startTime, endTime);

  //write down Data of running time for each algorithms on "Compare.txt" 
    outfile << sizeForCompare << "\t\t" << usualMerge << "\t\t" << improvedMerge << "\t\t"<<usualQuick << endl;
    
    sizeForCompare+=20; //increment size by 20
  }
 
  outfile.close();
  /*
    End of Comparing sorting running time.
  */

  return 0; 
}//end of main function



