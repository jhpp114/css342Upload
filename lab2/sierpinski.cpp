#include "sierpinski.h"

//--------------Sierpinski Arrowhead---------
Sierpinski::Sierpinski(float initX, float initY, float initAngle)
:Turtle(initX, initY, initAngle)
{

}//end of construtor

//-------------Left Curve----------------
void Sierpinski::leftCurve(int level, float d){
    if(level > 0){
        rightCurve(level-1,d);
        turn(60);
        leftCurve(level-1, d);
        turn(60);
        rightCurve(level-1, d);
    }
    else{
        draw(d);
    }
}
//----------Right Curve----------------
void Sierpinski::rightCurve(int level, float d){
    if(level > 0){
       leftCurve(level-1,d);
       turn(-60);
       rightCurve(level-1,d);
       turn(-60);
       leftCurve(level-1,d);
    }
    else{
        draw(d);
    }
}