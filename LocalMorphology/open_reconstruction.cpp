#include "imageIO.h"
#include "imageBasic.h"

Image erosion(Image image,vii structure,int highpow)
{
    int row=image.getrow();
    int col=image.getcol();

    Image dup_img;
    dup_img.setrow(row);
    dup_img.setcol(col);
    vii temp(row,vector<int>(col,0));
    vii img=image.getimg();


    int srow=structure.size();
    int scol=structure[0].size();

    int row_org=srow/2;
    int col_org=scol/2;

    int new_row=row-srow+row_org;
    int new_col=col-scol+col_org;

    vii structure_dup(srow,vector<int>(scol,0));

    for(int i=row_org;i<new_row;i++)
    {
        for(int j=col_org;j<new_col;j++)
        {
            for(int a=0;a<srow;a++)
            {
                for(int b=0;b<scol;b++)
                {
                     int temp1 = a - row_org;
                     int temp2 = b - col_org;
                     structure_dup[a][b] = img[i+temp1][j+temp2] - structure[a][b];
                }
            }
            temp[i][j]=min_structure(structure_dup);
            if(temp[i][j]<0) temp[i][j]=0;
            else if(temp[i][j]>highpow-1) temp[i][j]=highpow-1;
        }
    }
    dup_img.setimg(temp);//duplicate image have been created with 0 value and will be filled now
    return dup_img;
}//returns an eroded image based on the neighours element and size of structureing element

Image dilation(Image image,vii structure,int highpow)
{
    int row=image.getrow();
    int col=image.getcol();
    int srow=structure.size();
    int scol=structure[0].size();
    int row_org=srow/2;
    int col_org=scol/2;
    int new_row=row+srow-row_org;
    int new_col=col+scol-col_org;

    Image dup_img;
    dup_img.setrow(row+srow);
    dup_img.setcol(col+scol);

    vii temp(row+srow,vector<int>(col+scol));
    vii img=image.getimg();

    vii dup_structure(srow,vector<int> (scol,0));

    for(int i= -row_org; i<new_row; i++)
    {
        for(int j= -col_org; j<new_col; j++)
        {
            for(int a=0; a<srow; a++)
            {
                for(int b=0; b<scol; b++)
                {
                    int temp1=a-row_org;
                    int temp2=b-col_org;
                    if( (i-temp1)>=0 && (j-temp2)>=0 && (i-temp1)<row && (j-temp2)<col)
                        dup_structure[a][b] = img[i-temp1][j-temp2] + structure[a][b];
                    else dup_structure[a][b]=-999;
                }
                temp[i+row_org][j+col_org]=max_structure(dup_structure);
                if(temp[i+row_org][j+col_org]<0) temp[i+row_org][j+col_org]=0;
                else if(temp[i+row_org][j+col_org]>highpow-1) temp[i+row_org][j+col_org]=highpow-1;
            }
        }
    }

    dup_img.setimg(temp);
    return dup_img;

}//takes in the eroded image and dilate it

Image dilation_mask_max(Image image,int highpow)
{
    int row=image.getrow();
    int col=image.getcol();
    vii img=image.getimg();
    vii temp=img;

    Image dup_image;
    dup_image.setrow(row);
    dup_image.setcol(col);

    vii mask(3,vector<int>(3,0));

    for(int i=1;i<row-1;i++)
    {
        for(int j=1;j<col-1;j++)
        {
            for(int a=-1;a<=1;a++)
            {
                for(int b=-1;b<=1;b++)
                {
                    mask[a+1][b+1]=img[i+a][j+b];
                }
            }
            int tmp=max_structure(mask);
            if(tmp<0) tmp=0;
            else if(tmp>highpow-1) tmp=highpow-1;
            temp[i][j]=tmp;
        }
    }

    dup_image.setimg(temp);
    return dup_image;
}


Image gl_open(Image image,vii structure,int highpow)
{
    Image eroded=erosion(image,structure,highpow);
    Image dilated=dilation(eroded,structure,highpow);
    Image opened=shift(dilated,structure);
    return opened;
}


int main()
{
    Image image;
    image.setpath("test.ppm");
    image.setmode("r");
    image.imread();//image has been read now

   /* vii img=image.getimg();
    for(int i=0;i<image.getrow();i++)
    for(int j=0;j<image.getcol();j++)
    cout<<img[i][j]<<" ";*/

    int imin,imax,highpow;
    maxmin(image,imin,imax,highpow);

    int scol,srow;
    cout<<"Enter the number of rows in structuring element:";
    cin>>srow;
    cout<<"Enter the number of columns in structuring element:";
    cin>>scol;

    vii structure(srow,vector<int> (scol,0));

    Image opened=gl_open(image,structure,highpow);
    Image copy_img=opened;

    int count=0;
    do
    {

        opened=dilation_mask_max(opened,highpow);
        upper_limit(opened,image);
        swapper(copy_img,opened,count);
    }while(count != 0);

    copy_img.imwrite("open_recons.ppm");
}

