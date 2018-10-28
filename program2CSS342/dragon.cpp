#include "dragon.h"

/*
Dragon class Constructor
It has responsible to initialize Turtle class constructor since inherit Turtle class
Use initializer to initialize Turtle class
*/
Dragon::Dragon(float xInit, float yInit, float angleInit)
:Turtle(xInit, yInit, angleInit)
{}//end of constructor

//left curve
//Use Functions from Turtle class (turn degree, draw)
//parameter, level(how many times of recursion), distance (amount of length to draw)
//basis case level is bigger than zero
//use recursion
//turn 90 degree
//use rightCurve function
//turn 90 degree
void Dragon::leftCurve(int level, float distance){
    if(level > 0){
        leftCurve(level-1, distance);
        turn(90);
        rightCurve(level-1, distance);
        turn(90);
    }else{
        draw(distance);
    }
}

//right curve
//Use Functions from Turtle cass (turn degree, draw)
//parameter, level(how many times of recursion), distance (amount of length to draw)
//basis case level is bigger than zero
//Turn -90 as description mentioned
//left curve
//turn -90
//right curve
void Dragon::rightCurve(int level, float distance){
    if(level > 0){
        turn(-90);
        leftCurve(level-1, distance);
        turn(-90);
        rightCurve(level-1, distance);
    }else{
        draw(distance);
    }
}