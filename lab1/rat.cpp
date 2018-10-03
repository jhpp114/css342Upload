// a Rational object holds one Rational number, one fraction
#include "rat.h"

//------------------------------ Rational ------------------------------------
// default constructor:  parameters are numerator and denominator respectively
// if the number is negative, the negative is always stored in the numerator
Rational::Rational(int n, int d) {
   numerator = d < 0 ? -n : n;
   denominator = d < 0 ? -d : d;
   reduce();
}

//--------------------------------- add --------------------------------------
// overloaded +: addition of 2 Rationals, current object and parameter
Rational Rational::add(const Rational& a) {
   Rational t;

   t.numerator = a.numerator * denominator + a.denominator * numerator;
   t.denominator = a.denominator * denominator;
   if (denominator != 0) t.reduce();

   return t;
}

//------------------------------ subtract ------------------------------------
// subtraction of 2 Rationals, current object and parameter

Rational Rational::subtract(const Rational& s) {
   Rational t;

   t.numerator = s.denominator * numerator - denominator * s.numerator;
   t.denominator = s.denominator * denominator;
   if (denominator != 0) t.reduce();

   return t;
}

//------------------------------ multiply ------------------------------------
// multiplication of 2 Rationals, current object and parameter
Rational Rational::multiply(const Rational& m) {
   Rational t;

   t.numerator = m.numerator * numerator;
   t.denominator = m.denominator * denominator;
   if (denominator != 0) t.reduce();

   return t;
}

//-------------------------------- divide ------------------------------------
// division of 2 Rationals, current object and parameter,
// division by zero is unreliable
Rational Rational::divide(const Rational& v) {
   Rational t;

   t.numerator = v.denominator * numerator;
   t.denominator = denominator * v.numerator;
   if (denominator != 0) t.reduce();

   return t;
}

//---------------------------- printRational ---------------------------------
void Rational::printRational() {
   if (denominator == 0)
      cout << endl << "DIVIDE BY ZERO ERROR!!!" << endl;
   else if (numerator == 0)
      cout << 0;
   else
      cout << numerator << "/" << denominator;
}

//------------------------ printRationalAsFloat ------------------------------
void Rational::printRationalAsFloat() {  
   if (denominator == 0)
      cout << endl << "DIVIDE BY ZERO ERROR!!!" << endl;
   else
      cout << float(numerator) / float(denominator);
}

//-------------------------------- reduce ------------------------------------
// reduce fraction to lowest terms
void Rational::reduce() {
   int n = numerator < 0 ? -numerator : numerator;
   int d = denominator;
   int largest = n > d ? n : d;

   int gcd = 0;                                 // greatest common divisor

   for (int loop = largest; loop >= 2; loop--)
      if (numerator % loop == 0 && denominator % loop == 0) {
         gcd = loop;
         break;
      }

   if (gcd != 0) {
      numerator /= gcd;
      denominator /= gcd;
   }
}
   //-------------getNumberator & getDenominator----------------------------------
   //getNumerator will simply return numerator in integer form
int Rational::getNumerator() const{
         return numerator;
   }
   //getDenominator will simply return denominator in integer form
int Rational::getDenominator() const{
         return denominator;
   }
   
   //----------------------------friend << >> stream in and out-------------------
   //operator<< display error when denominator is 0
   //operator<< display 0 when the nominator is 0
   //display just numerator if denominator is 1
   //else just print numerator / denominator
   //use get function
std::ostream& operator<<(std::ostream& output, const Rational& obj){
      if(obj.getDenominator() == 0){
            output << "Error Denominator != 0";
      }else if(obj.getNumerator() == 0){
            output << obj.getNumerator();
      }else if(obj.getDenominator() == 1){
            output << obj.getNumerator();
      }else{
            output << obj.getNumerator() << "/" << obj.getDenominator();
      }
      return output;
}
   //get nominator and denominator from user
   //use printRational() 
std::istream& operator>>(std::istream& input, Rational& obj){
      input >> obj.numerator >> obj.denominator;
      obj.printRational();
      cout << endl;
}

   //----------------------------operator overloading-----------------------------
   //add 2 objects and return temp obj
   //use get Functions
   //create obj temp and store value
   //return temp 
Rational Rational::operator+(const Rational &addObj) const{
      Rational temp;
      temp.numerator = (getNumerator() * addObj.getDenominator()) + (getDenominator() * addObj.getNumerator());
      temp.denominator = getDenominator() * addObj.getDenominator(); 
      if(temp.getDenominator() != 0){
            temp.reduce();
      }
      return temp;
}

   //subtract 2 object and return temp obj
   //use get function
   //create obj temp and store value
   //return temp 
Rational Rational::operator-(const Rational &subObj) const{
      Rational temp;
      temp.numerator = (getNumerator() * subObj.getDenominator()) - (getDenominator() * subObj.getNumerator());
      temp.denominator = getDenominator() * subObj.getDenominator();
      if(temp.getDenominator() != 0){
            temp.reduce();
      }
      return temp;
}

   //multipliy 2 object and return temp obj
   //use get function
   //create obj temp and store value
   //return temp 
Rational Rational::operator*(const Rational &mulObj) const{
      Rational temp;
      temp.numerator = getNumerator() * mulObj.getNumerator();
      temp.denominator = getDenominator() * mulObj.getDenominator();
      if(temp.getDenominator() != 0){
            temp.reduce();
      }
      return temp;
}

   //divide 2 object and return temp obj 
   //divide zero will terminate
   //use get function
Rational Rational::operator/(const Rational &divObj) const{
      Rational temp;
      if(divObj.getNumerator() != 0){
      temp.numerator = getNumerator() * divObj.getDenominator();
      temp.denominator = getDenominator() * divObj.getNumerator();
      temp.reduce();
      }else{
            return 0;
      }
      return temp;
}

    //----------------boolean comparison operators------------------------
    //compare a>b
    //return  true if a is bigger than b
    //since it is fraction, try to get float decimal and compare
bool Rational::operator>(const Rational &compareObj) const{
      return (float (getNumerator())/getDenominator() > float(compareObj.getNumerator())/compareObj.getDenominator());
}
   // compare a<b
   //return true if a is smaller than b
bool Rational::operator<(const Rational &compareObj) const{
      return (float (getNumerator())/getDenominator() < float(compareObj.getNumerator())/compareObj.getDenominator());
}
      //compare a>=b
      //return true if a is bigger or equal to b
bool Rational::operator>=(const Rational &compareObj) const{
      return (float (getNumerator())/getDenominator() >= float(compareObj.getNumerator())/compareObj.getDenominator());
}
      //compare a <= b
      //return true if b is equal or bigger than a
bool Rational::operator<=(const Rational &compareObj) const{
      return (float (getNumerator())/getDenominator() <= float(compareObj.getNumerator())/compareObj.getDenominator());
}
      //compare a == b
      //return true if two objects are equal
bool Rational::operator==(const Rational &compareObj) const{
     return (float (getNumerator())/getDenominator() == float(compareObj.getNumerator())/compareObj.getDenominator());
}
      //compare a != b
      //return true if objects are not same
bool Rational::operator!=(const Rational &compareObj) const{
     return (float (getNumerator())/getDenominator() != float(compareObj.getNumerator())/compareObj.getDenominator());
}

//---------------assignment operators --------------------------------
//
Rational& Rational::operator+=(const Rational &addToObj){
      this->numerator = (getDenominator() * addToObj.getNumerator()) + (getNumerator() * addToObj.getDenominator());
      this->denominator = (getDenominator() * addToObj.getDenominator());
      if(this->denominator != 0){
            this->reduce();
      }
      return *this;
}



