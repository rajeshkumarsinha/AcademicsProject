#include "imageIO.h"

int main()
{
    int row=10;
    int col=10;
    vii img(row,vector<int> (col,0));
    int count=100;
    for(int i=0;i<row;i++)
    for(int j=0;j<col;j++)
    img[i][j]=count++;

    Image image;
    image.setrow(row);
    image.setcol(col);
    image.setimg(img);
    image.setmode("w");
    image.imwrite("test.ppm");
}
