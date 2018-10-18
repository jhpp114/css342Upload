#ifndef SIERPINSKI_H
#define SIERPINSKI_H

#include <iostream>
#include "Turtle.h"
#include <math.h>

using namespace std; 
//why are you using std in header file and cpp file that is not your main?
//I personally don;t get it.

class Sierpinski: Turtle{
    public:
    Sierpinski(float initX = 0.0, float initY = 0.0, float initAngle = 0.0);
    void leftCurve(int l, float d); //draw a level-l left curve with dist d
    void rightCurve(int l, float d); //draw a level-l right curve with dist d
};

#endif //SIERPINSKI_H