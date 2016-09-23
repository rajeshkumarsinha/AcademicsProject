#include<bits/stdc++.h>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#define vii vector<vector<int> >
#define vbb vector<vector<bool> >
#define pb push_back
#define mp make_pair
#define pii pair<int,int>

using namespace std;


class Image
{
    private:

    FILE* f;//opens a file in read or write mode as specified in constructor
    vii img;//actual place holder for Image file as 2D matrix
    int row,col;//store the row and col of the Image file
    string path;//store the path of Image file
    string mode;//store the mode in which file is to opened

    public:

    Image(int row,int col,string path,string mode)
    {
        this->row=row;
        this->col=col;
        this->path=path;
        this->mode=mode;
    }//constructor in case row col and path is given along with path and read mode

    Image(string path,string mode)
    {
        this->path=path;
        this->mode=mode;
    }//constructor in case only the path and mode is known row and col will be determinded automatically in this case

    Image()
    {}//does nothing only a parameterless constructor

    Image operator=()
    {

    }

    void setrow(int row){ this->row=row;}
    void setcol(int col){ this->col=col;}
    void setpath(string path){ this->path=path;}
    void setmode (string mode){ this->mode=mode;}

    int getrow(){ return this->row;}
    int getcol(){ return this->col;}
    string getpath() { return this->path;}
    string getmode() { return this->mode;}
    vii getimg() { return this->img;}

    vii imread()
    {
        f=fopen(this->path,this->mode);//open an Image in read mode using c file open function
        //to read the file we can use the fread function of c
        //till now we have only opened the Image as file the c program is unaware that it is a Image
        //now we will read the Image byte by byte in a 2D matrix using the fread function.
        img.resize(this->row,vector<int>(this->col,0));//space has been allocated to store the file we read as an matrix

        for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
        {
            int temp;
            fread(&temp,1,1,f);//read the file byte by byte to img matrix
            img[i][j]=temp;
        }
        return img;
    }//read an Image to a 2D matrix and return a double pointer of int

    void imwrite(string write_path)
    {
        FILE *f=fopen(write_path,"w");//open a file specified by path in write mode
        for(int i=0;i<row,i++)
        for(int j=0;j<col;j++)
        {
            int temp=img[i][j];
            fwrite(&temp,1,1,f);//write the value in img 2D matrix in a Image file with .jpg or .jpeg extension
        }
    }//write an Image to a file

};

vii erosion_threshold_min(int threshold,int value_threshold,Image image)
{
    //erode away the Image pixel value if it is surrounded by more than threshold number of neighbour
    //having the pixel value of less than or equal to value_threshold

    vii img_dup=image->img;//create the duplicate Image

    for(int i=1;i<image->row-1;i++)
    {
        for(int j=1;j<image->col-1;j++)
        {
            int count=0;
            int minimum=255;
            if(image->img[i][j]!=0)
            for(int a=-1;a<=1;a++)
            {
                for(int b=-1;b<=1;b++)
                {
                    if(image->img[i+a][j+b]<=value_threshold) count++;
                    minimum=min(image->img[i+a][j+b],minimum);
                }
            }
            if(count>threshold)
            img_dup[i][j]=minimum;
        }
    }
    return img_dup;
}

vii erosion_threshold_max(int threshold,int value_threshold,Image image)
{
    //erode away the Image pixel value if it is surrounded by more than threshold number of neighbour
    //having the pixel value of less than or equal to value_threshold

    vii img_dup=image->img;//create the duplicate Image

    for(int i=1;i<image->row-1;i++)
    {
        for(int j=1;j<image->col-1;j++)
        {
            int count=0;
            int maximum=0;
            if(image->img[i][j]!=0)
            for(int a=-1;a<=1;a++)
            {
                for(int b=-1;b<=1;b++)
                {
                    if(image->img[i+a][j+b]<=value_threshold) count++;
                    maximum=max(image->img[i+a][j+b],maximum);
                }
            }
            if(count>threshold)
            img_dup[i][j]=maximum;
        }
    }
    return img_dup;
}

vii dilation_threshold_min(int threshold,int value_threshold,Image image)
{
    //dilate the Image based on the the pixel value having value more than the given threshold value
    //and the number of such neighbour is more than the threshold

    vii img_dup=image->img;//create the duplicate Image

    for(int i=1;i<image->row-1;i++)
    {
        for(int j=1;j<image->col-1;j++)
        {
            int count=0;
            int minimum=255;
            if(image->img[i][j]==0)
            for(int a=-1;a<=1;a++)
            {
                for(int b=-1;b<=1;b++)
                {
                    if(image->img[i+a][j+b]<=value_threshold) count++;
                    minimum=min(image->img[i+a][j+b],minimum);
                }
            }
            if(count>threshold)
            img_dup[i][j]=minimum;
        }
    }
    return img_dup;
}


vii dilation_threshold_max(int threshold,int value_threshold,Image image)
{
    //dilate the Image based on the the pixel value having value more than the given threshold value
    //and the number of such neighbour is more than the threshold

    vii img_dup=image->img;//create the duplicate Image

    for(int i=1;i<image->row-1;i++)
    {
        for(int j=1;j<image->col-1;j++)
        {
            int count=0;
            int maximum=0;
            if(image->img[i][j]==0)
            for(int a=-1;a<=1;a++)
            {
                for(int b=-1;b<=1;b++)
                {
                    if(image->img[i+a][j+b]<=value_threshold) count++;
                    maximum=min(image->img[i+a][j+b],maximum);
                }
            }
            if(count>threshold)
            img_dup[i][j]=maximum;
        }
    }
    return img_dup;
}

vii erosion_mask_min(vii mask,Image image)
{
    //this erode the value of the pixel based on the mask. the center of the mask is placed on the
    //pixel to be eroded then the image is
    vii img_dup=image->img;

    for(int i=1;i<image->row;i++)
    {
        for(int j=1;j<image->col;j++)
        {
            int minimum=image->img[i][j];
            for(int a=-1;a<=1;a++)
            {
                for(int b=-1;b<=1;b++)
                {
                    if(mask[a+1][b+1]==1)
                    {
                        minimum=min(minimum,this->img[i+a][j+b]);
                    }
                }
            }
            img_dup[i][j]=minimum;
        }
    }
    return img_dup;
}


vii erosion_mask_max(vii mask,Image image)
{
    //this erode the value of the pixel based on the mask. the center of the mask is placed on the
    //pixel to be eroded then the image is
    vii img_dup=image->img;

    for(int i=1;i<image->row;i++)
    {
        for(int j=1;j<image->col;j++)
        {
            int maximum=image->img[i][j];
            for(int a=-1;a<=1;a++)
            {
                for(int b=-1;b<=1;b++)
                {
                    if(mask[a+1][b+1]==1)
                    {
                        maximum=max(maximum,this->img[i+a][j+b]);
                    }
                }
            }
            img_dup[i][j]=maximum;
        }
    }
    return img_dup;
}

vii dilation_mask_min(vii mask,Image image)
{
    vii img_dup=image->img;

    for(int i=1;i<image->row;i++)
    {
        for(int j=1;j<image->col;j++)
        {
            int minimum=image->img[i][j];
            for(int a=-1;a<=1;a++)
            {
                for(int b=-1;b<=1;b++)
                {
                    if(mask[a+1][b+1]==1)
                    {
                        minimum=min(minimum,image->img[i+a][j+b]);
                    }
                }
            }
            img_dup[i][j]=minimum;
        }
    }
    return img_dup;
}

vii dilation_mask_max(vii mask,Image image)
{
    vii img_dup=image->img;

    for(int i=1;i<image->row;i++)
    {
        for(int j=1;j<image->col;j++)
        {
            int maximum=image->img[i][j];
            for(int a=-1;a<=1;a++)
            {
                for(int b=-1;b<=1;b++)
                {
                    if(mask[a+1][b+1]==1)
                    {
                        maximum=max(maximum,image->img[i+a][j+b]);
                    }
                }
            }
            img_dup[i][j]=maximum;
        }
    }
    return img_dup;
}

vii outeroutline(vii eroded,Image image)
{
    int row=image.getrow();
    int col=image.getcol();

    for(int i=0;i<row;i++)
    {
       for(int j=0;j<col;j++)
       {
            eroded[i][j]=image->img[i][j]-eroded[i][j];
       }
    }
    return eroded;
}

vii inneroutline(vii dilated,Image image)
{
    int row=image.getrow();
    int col=image.getcol();

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            dilated[i][j]-=image->img[i][j];
        }
    }
    return dilated;
}

vii combine(vii eroded, vii dilated)
{
    int row=eroded.size();
    int col=eroded[0].size();
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            eroded[i][j]+=dilated[i][j];
        }
    }
    return eroded;
}


vii create_mask(int sel)//create a specific mask based on the request of the user in sel variable
{
    int mask_size=3;
    vii mask(mask_size,vector<int>(mask_size,0));

    switch(sel)
    {
        case 1://only the horizontal row is 1 middle one
        for(int i=0;i<3;i++) mask[1][i]=1;
        break;
        case 2://only the vertical column is 1 middle one
        for(int i=0;i<3;i++) mask[i][1]=1;
        break;
        case 3://the vertical and horizontal both are 1 in middle
        for(int i=0;i<3;i++) mask[1][i]=1;
        for(int i=0;i<3;i++) mask[i][1]=1;
        break;
        case 4://all 1
        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        mask[i][j]=1;
        break;
        default://no mask in default case the image remain unchanged
        break;
    }
    return mask;
}

vii outlining_mask_min(Image image,int sel)
{
    vii mask=create_mask(sel);
    vii eroded=erosion_mask_min(mask,image);
    vii dilation=dilation_mask_min(mask,image);
    vii combined=combine(eroded,dilation);
    return combined;
}

vii outlining_mask_max(Image image,int sel)
{
    vii mask=create_mask(sel);
    vii eroded=erosion_mask_max(mask,image);
    vii dilation=dilation_mask_max(mask,image);
    vii combined=combine(eroded,dilation);
    return combined;
}

vii opening_mask_min(Image image,int sel,int num)
{
    //sel is to select a mask of specific type
    //num is the number of erosion to do before doing an dilation
    vii mask=create_mask(sel);
    vii prev=image->img;
    int row=image.getrow();
    int col=image.getcol();

    while(num>0)
    {
        Image temp;
        temp.setcol(col);
        temp.setrow(row);
        temp.setimg(prev);
        vii eroded=erosion_mask_max(mask,temp);
        prev=eroded;
    }

    Image temp;
    temp.setcol(col);
    temp.setrow(row);
    temp.setimg(prev);
    vii dilated=dilation_mask_max(mask,temp);
    return dilated;

}

vii opening_mask_min(Image image,int sel,int num)
{
    //sel is to select a mask of specific type
    //num is the number of erosion to do before doing an dilation
    vii mask=create_mask(sel);
    vii prev=image->img;
    int row=image.getrow();
    int col=image.getcol();

    while(num>0)
    {
        Image temp;
        temp.setcol(col);
        temp.setrow(row);
        temp.setimg(prev);
        vii eroded=erosion_mask_min(mask,temp);
        prev=eroded;
    }

    Image temp;
    temp.setcol(col);
    temp.setrow(row);
    temp.setimg(prev);
    vii dilated=dilation_mask_min(mask,temp);
    return dilated;

}

vii closing_mask_max(Image image,int sel,int num)
{
    //sel is to select a mask of specific type
    //num is the number of erosion to do before doing an dilation
    vii mask=create_mask(sel);
    vii prev=image->img;
    int row=image.getrow();
    int col=image.getcol();

    while(num>0)
    {
        Image temp;
        temp.setcol(col);
        temp.setrow(row);
        temp.setimg(prev);
        vii dilated=dilation_mask_max(mask,temp);
        prev=dilated;
    }

    Image temp;
    temp.setcol(col);
    temp.setrow(row);
    temp.setimg(prev);
    vii eroded=erosion_mask_max(mask,temp);
    return eroded;

}

vii closing_mask_min(Image image,int sel,int num)
{
    //sel is to select a mask of specific type
    //num is the number of erosion to do before doing an dilation
    vii mask=create_mask(sel);
    vii prev=image->img;
    int row=image.getrow();
    int col=image.getcol();

    while(num>0)
    {
        Image temp;
        temp.setcol(col);
        temp.setrow(row);
        temp.setimg(prev);
        vii dilated=dilation_mask_min(mask,temp);
        prev=dilated;
    }

    Image temp;
    temp.setcol(col);
    temp.setrow(row);
    temp.setimg(prev);
    vii eroded=erosion_mask_min(mask,temp);
    return eroded;

}

void
