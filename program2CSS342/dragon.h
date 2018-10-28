#ifndef DRAGON_H
#define DRAGON_H
#include "Turtle.h"
#include<iostream>

class Dragon: public Turtle{
    public:
    //default constructor set to 0.0
    //initialize Turtle class constructor
    Dragon(float xInit = 0.0, float yInit = 0.0, float angleInit = 0.0); 
    
    
    /*
        left curve
        parameter, level(how many times of recursion), distance (amount of length to draw)
        base case level is bigger than zero
        use of recursion
        turn 90 degree
        use rightCurve function
        turn 90 degree
    */
    void leftCurve(int l, float d); // draw a level-l left curve with distance d

    /*
        right curve
        Use Functions from Turtle cass (turn degree, draw)
        parameter, level(how many times of recursion), distance (amount of length to draw)
        basis case level is bigger than zero
        Turn -90 as description mentioned
        left curve
        turn -90
        right curve
    */
    void rightCurve(int l, float d); // draw a level-l right curve with distance d

    
};
#endif //DRAGON_H
