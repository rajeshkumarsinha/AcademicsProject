#include"includes.h"
#include"circle.h"
pixel find_max(vector<pixel> cand)
{
    int n=cand.size();
    vector<circle> circles(n);
    for(int i=0;i<n;i++)
    {
        float alpha=cand[i].red;
        float beta=cand[i].green;
        float gamma=cand[i].blue;
        circle new_circle(1.414*beta,(gamma-alpha)/1.414,(alpha+gamma)/1.414);
        circles[i]=new_circle;
    }

    float up_max=circles[0].get_up();
    float down_max=circles[0].get_down();
    float left_max=circles[0].get_left();
    float right_max=circles[0].get_right();

    for(int i=1;i<n;i++)
    {
        up_max=max(up_max,circles[i].get_up());
        down_max=max(down_max,circles[i].get_down());
        left_max=max(left_max,circles[i].get_left());
        right_max=max(right_max,circles[i].get_right());
    }

    float x_new=(right_max-left_max)/2.0;
    float y_new=(up_max-down_max)/2.0;
    float r_new= sqrt( pow((right_max-left_max),2)+pow((up_max-down_max),2) );

    float red_new=(r_new-y_new)/1.414;
    float green_new=x_new/1.414;
    float blue_new=(r_new+y_new)/1.414;

    pixel p(ceil(red_new),ceil(green_new),ceil(blue_new));
    return p;
}


pixel find_min(vector<pixel> cand)
{
    int n=cand.size();
    vector<circle> circles(n);
    for(int i=0;i<n;i++)
    {
        float alpha=(cand[i].red+cand[i].blue)/2.0;
        float beta=cand[i].green;
        float gamma=(cand[i].blue-cand[i].red)/2.0;
        circle new_circle(1.414*beta,(gamma-alpha)/1.414,(alpha+gamma)/1.414);
        circles[i]=new_circle;
    }

    float up_max=circles[0].get_up();
    float down_max=circles[0].get_down();
    float left_max=circles[0].get_left();
    float right_max=circles[0].get_right();

    for(int i=1;i<n;i++)
    {
        up_max=max(up_max,circles[i].get_up());
        down_max=max(down_max,circles[i].get_down());
        left_max=max(left_max,circles[i].get_left());
        right_max=max(right_max,circles[i].get_right());
    }

    float x_new=(right_max-left_max)/2.0;
    float y_new=(up_max-down_max)/2.0;
    float r_new= sqrt( pow((right_max-left_max),2)+pow((up_max-down_max),2) );

    float red_new=(r_new-y_new)*1.414;
    float green_new=x_new*1.414;
    float blue_new=(r_new+y_new)*1.414;

    pixel p(floor(red_new),floor(green_new),floor(blue_new));
    return p;
}
