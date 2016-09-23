#include"includes.h"
class circle
{
    public:
    float x,y,r;

    circle(float x,float y,float r)
    {
        this->x=x;
        this->y=y;
        this->r=r;
    }

    circle(){}

    float get_up(){
        return (y+r);}
    float get_down(){
        return y-r;}
    float get_right(){
        return x+r;}
    float get_left(){
        return x-r;}

};
