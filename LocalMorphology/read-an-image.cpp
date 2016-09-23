#include "imageIO.h"
int main()
{
    int row=10;
    int col=10;
    vii img(row,vector<int> (col,0));

    Image image;
    image.setrow(row);
    image.setcol(col);
    image.setpath("test.ppm");
    image.setmode("rb");
    img=image.imread();

    for(int i=0;i<row;i++)
    for(int j=0;j<col;j++)
    cout<<img[i][j]<<" ";
}

