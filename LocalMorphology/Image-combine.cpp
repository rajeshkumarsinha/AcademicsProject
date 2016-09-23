#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;
int i,j;

void stretch_image_linear(int row,int col,int imgmin,int imgmax,int **imgin1)
{
    int dp[255];
    float mark;

    mark = 255.0/(float)(imgmax-imgmin);
    for(i=imgmin; i<=imgmax; i++) dp[i] = mark * ( i - imgmin) + 0.5;

    for(i=0; i<row; i++)
    for(j=0; j<col; j++)
    {
        int temp = imgin1[i][j];
        imgin1[i][j] = dp[temp];
    }
}

void max_min_image(int row,int col,int **imgin1)
{
    int imgmax = -1;
    int imgmin = 255;
    for(i=0; i<row; i++)
    for(j=0; j<col; j++)
    {
        if(imgmax < imgin1[i][j]) imgmax = imgin1[i][j];
        if(imgmin > imgin1[i][j]) imgmin = imgin1[i][j];
    }
    cout<<"maximum val= "<<imgmax<<"  minimum val= "<<imgmin<<endl;
    stretch_image_linear(row,col,imgmin,imgmax,imgin1);
}

void combine_image(int sel,int row,int col,int **imgin1,int **imgin2)
{
   switch(sel)
   {

   case 1:
   for(i=0;i<row;i++)
   for(j=0;j<col;j++)
   {
        imgin1[i][j] +=imgin2[i][j];
		if (imgin1[i][j] > 255) imgin1[i][j] = 255;
   }
    break;

   case 2:
   for(i=0;i<row;i++)
   for(j=0;j<col;j++)
   {
        imgin1[i][j] -=imgin2[i][j];
		if (imgin1[i][j] < 0) imgin1[i][j] = 0;
   }
    break;

    case 3:
   for(i=0;i<row;i++)
   for(j=0;j<col;j++)
   {
        imgin1[i][j] *=imgin2[i][j];
		if (imgin1[i][j] > 255) imgin1[i][j] = 255;
   }
    break;

   case 4:
   for(i=0;i<row;i++)
   for(j=0;j<col;j++)
   {
         imgin1[i][j] = ( (float)(imgin1[i][j]+1)/(float)(imgin2[i][j]+1) )* 255.0 + 0.5;
         if (imgin1[i][j] > 255) imgin1[i][j] = 255;
   }
    break;

   case 5:
   for(i=0;i<row;i++)
   for(j=0;j<col;j++)
   {
        imgin1[i][j] -=imgin2[i][j];
		if (imgin1[i][j] < 0) imgin1[i][j] *=-1;
   }
    break;

   case 6:
   for(i=0;i<row;i++)
   for(j=0;j<col;j++)
   {
        if(imgin1[i][j] != 255)
		{
            if (imgin1[i][j] == imgin2[i][j]) imgin1[i][j] = 0;
            else imgin1[i][j] = 240;
        }
   }
   break;

   case 7:
   for(i=0;i<row;i++)
   for(j=0;j<col;j++)
   {
       if (imgin1[i][j] != imgin2[i][j]) imgin1[i][j] = 0;
                else imgin1[i][j] = 255;
   }
   break;

   case 8:
   for(i=0;i<row;i++)
   for(j=0;j<col;j++)
         imgin1[i][j] =max(imgin1[i][j], imgin2[i][j]);
   break;

   case 9:
   for(i=0;i<row;i++)
   for(j=0;j<col;j++)
       imgin1[i][j] =min(imgin1[i][j], imgin2[i][j]);
   break;


   case 10:
   for(i=0;i<row;i++)
   for(j=0;j<col;j++)
      imgin1[i][j] =(int)((imgin1[i][j]+ imgin2[i][j])/2.0);
   break;

   }

}

int main()
{
    cout<<"Addition    = 1. \n";
    cout<<"Substraction = 2. \n";
    cout<<"Multiplication= 3. \n";
    cout<<"Division = 4.\n";
    cout<<"Differnce = 5.\n";
    cout<<"Detect the change = 6.\n";
    cout<<"Unchange the Detect = 7.\n";
    cout<<"Maximum = 8.\n";
    cout<<"Minimum = 9.\n";
    cout<<"Averages = 10.\n";
    cout<<"Enter your choice:";
    int sel;cin>>sel;

    FILE *img1,*img2,*img3;
    int row = ;
    int col = ;

    int **imgin1=(int **)malloc(row*sizeof(int *));
    for(i=0;i<row;i++) imgin1[i]=(int *)malloc(col*sizeof(int));

    int **imgin2=(int **)malloc(row*sizeof(int *));
    for(i=0;i<row;i++) imgin2[i]=(int *)malloc(col*sizeof(int));

    img1 = fopen (, "r");
    img2 = fopen (, "r");
    img3 = fopen (, "w");

    int temp1,temp2;
    for(i=0;i<row;i++)
    for(j=0;j<col;j++)
    {
        fread(&temp1,1,1,img1);
        fread(&temp2,1,1,img2);
        imgin1[i][j] = temp1;
        imgin2[i][j] = temp2;
    }

    combine_image(sel,row,col,imgin1,imgin2);
    max_min_image();

    for(i=0; i<row; i++)
    for(j=0; j<col; j++)
    {
        temp1 = imgin1[i][j];
        fwrite(&temp1,1,1,img3);
    }
}
