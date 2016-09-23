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
    int color_depth;//the color depth of the image
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

    void setrow(int row){ this->row=row;}
    void setcol(int col){ this->col=col;}
    void setpath(string path){ this->path=path;}
    void setmode (string mode){ this->mode=mode;}
    void setimg(vii img){ this->img=img;}
    void setcolor_depth(int color_depth) { this->color_depth=color_depth;}

    int getrow(){ return this->row;}
    int getcol(){ return this->col;}
    string getpath() { return this->path;}
    string getmode() { return this->mode;}
    vii getimg() { return this->img;}
    int getcolor_depth() { return this->color_depth;}

    void imread()
    {
        f=fopen(this->path.c_str(),this->mode.c_str());//open an Image in read mode using c file open function
        //to read the file we can use the fread function of c
        //till now we have only opened the Image as file the c program is unaware that it is a Image
        //now we will read the Image byte by byte in a 2D matrix using the fread function.

        char header[10];
        fscanf(f,"%s",header);
       // fgets(header, 500, f);//reads 100 chracter or a line whichever is shorter since the header only
        //consists of P6 %i %i 255 character we are good to go

        fscanf(f,"%d %d %d",&this->col,&this->row,&this->color_depth);
       // cout<<col<<" "<<row<<" "<<color_depth<<endl;

        img.resize(this->row,vector<int>(this->col,0));//space has been allocated to store the file we read as an matrix

        for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
        {
            unsigned char temp;
            fread(&temp,1,1,f);//read the file byte by byte to img matrix
            fread(&temp,1,1,f);
            fread(&temp,1,1,f);
            img[i][j]=(unsigned int)temp;
        }
    }//read an Image to a 2D matrix and return a double pointer of int

   void imwrite(string write_path)
    {
        FILE *f=fopen(write_path.c_str(),"w");//open a file specified by path in write mode
        fprintf(f, "P6 %d %d 255\n", this->col, this->row);//format necessary for representing a file in ppm format
        //cout<<this->row<<" "<<this->col<<endl;
        for(int i=0;i<this->row;i++)
        for(int j=0;j<this->col;j++)
        {
            int temp=img[i][j];
            //fwrite(&temp,1,1,f);//write the value in img 2D matrix in a Image file with .jpg or .jpeg extension
            fputc(temp, f);   // 0 .. 255 of red
            fputc(temp, f); // 0 .. 255 of green
            fputc(temp, f);  // 0 .. 255 blue
        }
        //write a file in ppm format the most basic file format used to represent
        // a file in binary format the 0 pixels are represented as 0 red 0 green and 0 blue
        //the white pixels are represented as 255 red 255 green 255 blue
    }//write an Image to a file
   // fclose(f);

};
