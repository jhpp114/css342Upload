// a Rational object holds one Rational number, one fraction

#ifndef RAT_H
#define RAT_H
#include <iostream>
using namespace std;

class Rational {                           // not fully commented
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

public:
   Rational(int = 0, int = 1);             // default constructor
   //a.add function
   //create an object that return the value after add a object to parameter object
   Rational add(const Rational &);
   //create an object that return the value after subtract a object to parameter object
   Rational subtract(const Rational &);
   //create an object that return the value after multiply a object to parameter object
   Rational multiply(const Rational &);
   //create an object that return the value after divide a object to parameter object
   Rational divide(const Rational &);

    //print numerator / denominator form
    //have condition
    //if denominator is zero, print out error
    //if the numerator is 0 print out 0
   void printRational();

   //print the fraction to float type decimal number
   //have one condition, if denaminator is zero print error
   void printRationalAsFloat();
   
   //return int value of numerator
   int getNumerator() const;
   //return int value of denominator
   int getDenominator() const;

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
   bool operator<(const Rational &) const;

   //check object >= parameter, return false or true
   bool operator>=(const Rational &) const; 

   //check object <= parameter, return false or true
   bool operator<=(const Rational &) const; 

   //check object == parameter, return false or true
   bool operator==(const Rational &) const; 

   //check object != parameter, return false or true
   bool operator!=(const Rational &) const; 

    // assignment operators
    //return adress of the object, but  with * it returns the value in object.
   Rational& operator+=(const Rational &); // current object += parameter
   
private:
   int numerator;
   int denominator;

   void reduce();                 // utility function, reduce to lowest terms
};


#endif //rat_h
