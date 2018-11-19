#include <vector>
#include <math.h> // may need to use pow( )
using namespace std;

template <class Comparable>
void mergeImproved( vector<Comparable> &a ) {

  int size = a.size( );
  vector<Comparable> b( size );  // this is only one temporary array.     

  // implement a nonrecursive mergesort only using vectors a and b.

  int first1 = 0; //left first
  int last1 = 0; //left last
  int first2 = 0; //right first 
  int last2 = 0; //right last

  for(int i = 1; i < size; i*=2){
    for(int j = 0; j < size - i; j += 2 * i){
        //divide and conqur
		first1 = j;
        last1 = j + i -1;
        first2 = last1 + 1;
		last2 = fmin(2*i + j -1, size -1);
        int index = first1;

        while(first1 <= last1 && first2 <= last2){
            if(a[first1] < a[first2]){
                b[index] = a[first1];
                first1++;
            }else{
                b[index] = a[first2];
                first2++;
            }
            index++;
        }//end of while loop

        while(first1 <= last1){
            b[index] = a[first1];
            first1++;
            index++;
        }

        while(first2 <= last2){
            b[index] = a[first2];
            first2++;
            index++;
        }

        for(index = j; index <= last2; index++){
            a[index] = b[index];
        }//end of copy loop


    }//end of second for loop
  }//end of for first for loop
}
