#include<bits/stdc++.h>
using namespace std;
#include "image_io.h"
int main()
{

    image img;
    img.set_height(30);
    img.set_width(30);
    img.set_range_max(255);
    vector<vector<int> > bitmap(30,vector<int> (30,0));
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<30;j++)
        {
            bitmap[i][j]=i*j;
            bitmap[i][j]%=255;
        }
    }
    img.set_bitmap(bitmap);
    img.write_image("test.pgm");
}
