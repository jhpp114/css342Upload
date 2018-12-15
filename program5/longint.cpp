#include "longint.h"

//3 constructors
//using namespace std;
//constructor 1
LongInt::LongInt(const string str){
    int i = 0;
    negative = false; //set to +
    digits.clear(); //clearing digits
    
    //contains - then negative
    if(str[i] == '-'){
        negative = true; //if - negatative should be true
        ++i;
    }
    else{
        negative = false;
    }
    //just get numbers don't add back the letters (abcd etc..)
    for(i = 0; i < str.length(); i++){
        if( (str[i] >= '0') && (str[i] <= '9')){
            digits.addBack(str[i]);
        }
    }
    
}

//constructor 2 copy constructor
LongInt::LongInt(const LongInt& rhs){
    digits.clear(); //clear the digit
    digits = rhs.digits; //copy
    negative = rhs.negative; //copy
}

//constructor 3 initialize 0
LongInt::LongInt(){
    digits.clear(); //clear the digit
    digits.addFront('0');
    negative = false; //can be 0
}

//deconsonstructor use deque
LongInt::~LongInt(){
    // while(!digits.isEmpty()){
    //     //digits.removeFront();
    //     digits.clear();
    // }
    
    digits.~Deque();
}

//operator+
//four different cases
/*
B+A
-(A+B)
B-A
A-B
*/
LongInt LongInt::operator+(const LongInt& rhs) const{
    LongInt sumResult; //result store
    int carry = 0;
    int result = 0;
    //left just this
    //right rhs
    LongInt tempLHS = *this;
    LongInt tempRHS = rhs;

    Deque<char> left = digits;
    Deque<char> right = rhs.digits;

    sumResult.digits.clear();
    if(left.size() < right.size()){
        sumResult = rhs + *this;
    }//case -A + -B = -(A+B)
    else if(negative && rhs.negative){
        tempLHS.negative = false;
        tempRHS.negative = false;
        sumResult = tempLHS + tempRHS; //just add
        sumResult.negative = true; // make this true so negative at the end
    }//case -A + B = B - A
    else if(negative && !rhs.negative){
        tempLHS.negative = false;
        sumResult = rhs -tempLHS;
    }//case A + -B = A - B
    else if(!negative && rhs.negative){
        tempRHS.negative = false;
        sumResult = *this - tempRHS;
    }
    else{
        //sum all until it reaches the highest right digit
        //ascii code 48 
        while(!right.isEmpty()){
            int r = right.removeBack() - 48;
            int l = left.removeBack() - 48;
            result = (r+l+carry) % 10;
            carry = (r+l+carry) / 10;
            sumResult.digits.addFront(result + 48);
        }
        //if there is value left then add to left
        while( (carry > 0) && (!left.isEmpty())){
            int l = left.removeBack() - 48;
            result = (l + carry) % 10;
            carry = (l + carry) / 10;
            sumResult.digits.addFront(result + 48);
        }
        //carry greater than 0
        if(carry > 0){
            sumResult.digits.addFront(carry + 48);
        }
        //add remaining values
        while(!left.isEmpty()){
            char l = left.removeFront();
            sumResult.digits.addFront(l);
        }
    }
    return sumResult;
}//end of operator+

//operator -
/*
-A - -B = B - A
-A - B = -(A+B)
+A - -B = A+B
A-B 
*/
LongInt LongInt::operator-(const LongInt& rhs) const{
    LongInt subResult;
    int result = 0;
    int carry = 0;

    LongInt tempLHS = *this;
    LongInt tempRHS = rhs;
    
    Deque<char> left = digits;
    Deque<char> right = rhs.digits;

    subResult.digits.clear();

    if(left.size() < right.size()){
        subResult = rhs + *this;
    }
    //negative negative
    else if(negative && rhs.negative){
        tempLHS.negative = false;
        tempRHS.negative = false;
        subResult = tempLHS - tempRHS;
    }
    //negative not negative
    else if(negative && !rhs.negative){
        tempLHS.negative = false;
        subResult = tempLHS + tempRHS;
        subResult.negative = true;
    }
    //not negative negative
    else if(!negative && rhs.negative){
        tempRHS.negative = false;
        subResult = tempLHS + tempRHS;
    }
    else{
        int low = 0;
        int high = 0;
        while(!left.isEmpty()){
            high = left.removeBack() - 48;
            if(!right.isEmpty()){
                low = right.removeBack() - 48;
            }
            else{
                low = 0;
            }

            if(carry == 1){
                high--;
                carry--;
            }

            if(high < low && !left.isEmpty()){
                high+=10;
                carry++;
            }
            if( (high-low) < 0 && left.isEmpty()){
                result = (high-low)  * -1;
                subResult.negative = true;
            }
            else{
                result = high - low;
            }
            subResult.digits.addFront(result + 48);
        }
    }
    return subResult;
}

//friend istream
//override istream
istream& operator>>(istream& in, LongInt& rhs){
    string input;
    in >> input; //put 
    LongInt temp(input);
    rhs = temp;
  
    return in;
}
//override ostream
ostream& operator<<(ostream& out, const LongInt& rhs){
    Deque<char> temp = rhs.digits;
    char lead;
    if( (rhs.digits.size() == 1) && (rhs.digits.getFront() == '0')){
        cout << '0';
    }
    else{
        if(rhs.negative == true){
            out << '-';
        }
        lead = temp.removeFront();
        while(lead == '0'){
            lead = temp.removeFront();
        }
        out << lead;
        while(!temp.isEmpty()){
            out << temp.removeFront();
        }
    }
    
    return out;
}

//assign operator
const LongInt& LongInt::operator=(const LongInt& rhs){
    digits = rhs.digits;
    negative = rhs.negative;
    return *this;
}

//boolean operator
bool LongInt::operator<(const LongInt& rhs) const{
    bool check = true;
    //same return false
    if(*this == rhs){
        check = false;
    }
    //case negative and negative
    else if(negative && rhs.negative){
        LongInt left = *this;
        LongInt right = rhs;
        left.negative = false;
        right.negative = false;
        check = (left > right);
    }
    //case negative positive pos is always bigger
    else if(negative && !rhs.negative){
        check = true;
    }
    //check pos and negative > 
    else if(!negative && rhs.negative){
        check = false;
    }
    else{
        if(digits.size() == rhs.digits.size()){
            Deque<char> left = digits;
            Deque<char> right = rhs.digits;
            while(!left.isEmpty() && check == true){
                int l = left.removeFront() - '0';
                int r = right.removeFront() - '0';
                if(l > r){
                    check = false;
                }
            }//end of while
        }//end of if statement
        else if(digits.size() < rhs.digits.size()){
            check = true;
        }else{
            check = false;
        }
    }
    return check;
}

bool LongInt::operator<=( const LongInt & rhs ) const{
    bool check = false;
    //equal or <
    if( (*this == rhs) || (*this < rhs)){
        check = true;
    }
    else{
        check = false;
    }

    return check;
}

bool LongInt::operator>( const LongInt & rhs ) const{
    bool check = true;
    //same false
    if(*this == rhs){
        check = false;
    }
    //negative negative
    else if(negative && rhs.negative){
        LongInt tempLHS = *this;
        LongInt tempRHS = rhs;
        tempLHS.negative = false;
        tempRHS.negative = false;
        check = (tempLHS < tempRHS);
    }
    //neagative positve
    else if(negative && !rhs.negative){
        check = false;
    }
    //positive negative
    else if(!negative && rhs.negative){
        check = true;
    }
    else{
        if(digits.size() == rhs.digits.size()){
            Deque<char> left = digits;
            Deque<char> right = rhs.digits;
            for(int i = 0; i < left.size(); i++){
                int l = left.removeFront() - '0';
                int r = right.removeFront() - '0';
                if(l < r){
                    check = false;
                }
            }//end of for
        }//end of if
        else if(digits.size() > rhs.digits.size()){
            check = true;
        }
        else{
            check = false;
        }
    }
    return check;
}

bool LongInt::operator>=( const LongInt & rhs ) const{
    bool check = false;
    //same or > 
    if((*this == rhs) || (*this > rhs)){
        check = true;
    }else{
        check = false;
    }

    return check;
}

bool LongInt::operator==( const LongInt & rhs ) const{
    bool check = true;
    Deque<char> left = digits;
    Deque<char> right = rhs.digits;
    if(left.size() == right.size()){
        if(negative != rhs.negative){
            check = false;
        }
        else{
            while( (!left.isEmpty()) && (check == true) ){
                int l = left.removeFront() - '0';
                int r = right.removeFront() - '0';
                if(l != r){
                    check = false;
                }//end of if
            }//end of while
        }//end of else
    }
    else{
        check = false;
    }
    return check;
}

bool LongInt::operator!=( const LongInt & rhs ) const{
    return !(*this == rhs);
}
