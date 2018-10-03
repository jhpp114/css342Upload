// a Rational object holds one Rational number, one fraction

#ifndef RAT_H
#define RAT_H
#include <iostream>
using namespace std;

class Rational {                           // not fully commented
public:
   Rational(int = 0, int = 1);             // default constructor
   Rational add(const Rational &);
   Rational subtract(const Rational &);
   Rational multiply(const Rational &);
   Rational divide(const Rational &);
   void printRational();
   void printRationalAsFloat();
   
   //
   int getNumerator() const;
   int getDenominator() const;

   //overload the output and input
   //operator<< display error when denominator is 0
   //operator<< display 0 when the nominator is 0
   //display just numerator if denominator is 1
   //else just print numerator / denominator
   //use get function
   friend ostream& operator<<(ostream&, const Rational&);
   //get nominator and denominator from user
   //use printRational() 
   friend istream& operator>>(istream&, Rational&);

   //arithetic operators
   //add 2 object (in this case Rational) and return Rational temp
   Rational operator+(const Rational &) const;
   //subtract 2 object and return temp obj
   Rational operator-(const Rational &) const;
   //multipliy 2 object and return temp obj
   Rational operator*(const Rational &) const;
   //divide 2 object and return temp obj divide zero will terminate
   Rational operator/(const Rational &) const;

   // boolean comparison operators
   //check object > parameter, return false or true
   bool operator>(const Rational &) const; 
   
   //check object < parameter, return false or true
   //return true if parameter is bigger
   bool operator<(const Rational &) const;
   //check object >= 
   bool operator>=(const Rational &) const; 
   bool operator<=(const Rational &) const; 
   bool operator==(const Rational &) const; 
   bool operator!=(const Rational &) const; 

    // assignment operators
    //return adress of the object, but  with * it returns the value in object.
   Rational& operator+=(const Rational &); // current object += parameter
   
private:
   int numerator;
   int denominator;

   void reduce();                 // utility function, reduce to lowest terms
};

#include "rat.cpp" //include rat.cpp here so, I dont have to include rat.cpp in main()
#endif
