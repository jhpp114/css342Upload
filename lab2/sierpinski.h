#ifndef SIERPINSKI_H
#define SIERPINSKI_H

#include <iostream>
#include "Turtle.h"
#include <math.h>

using namespace std; 

//sierpinski class inherits Turtle class that is pre-made by professor
//public is defaulted so it is ok to right :Turtle instead of public Turtle
class Sierpinski: Turtle{
    public:
    Sierpinski(float initX = 0.0, float initY = 0.0, float initAngle = 0.0); //default constructor 
    void leftCurve(int l, float d); //draw a level-l left curve with dist d
    void rightCurve(int l, float d); //draw a level-l right curve with dist d
};

#endif //SIERPINSKI_H