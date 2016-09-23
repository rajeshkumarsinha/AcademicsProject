#include"includes.h"
#include"pixel.h"


class image
{
private:
    int width,height,range_max;

public:
    vpipi bitmap;
    void set_width(int width)
    {
        this->width=width;
    }
    void set_height(int height)
    {
        this->height=height;
    }
    void set_range_max(int range_max)
    {
        this->range_max=range_max;
    }
    void set_bitmap(vpipi bitmap)
    {
        this->bitmap=bitmap;
    }
    int get_width()
    {
        return this->width;
    }
    int get_height()
    {
        return this->height;
    }
    int get_range_max()
    {
        return this->range_max;
    }
    vpipi get_bitmap()
    {
        return this->bitmap;
    }

    image()
    {
    }

    image(int width,int height,int range_max)
    {
        this->width=width;
        this->height=height;
        this->range_max=range_max;
        bitmap.resize(height,vector<pixel>(width));
    }

    void print_image()
    {
        cout<<width<<" "<<height<<" "<<range_max<<endl;
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                cout<<bitmap[i][j].red<<" "<<bitmap[i][j].green<<" "<<bitmap[i][j].blue<<endl;
            }
        }
    }

    void print_image(int param)
    {
         cout<<width<<" "<<height<<" "<<range_max<<endl;
    }

    void write_image(string src_file_name)
    {
        int dimx, dimy, range;
        dimx=this->width;
        dimy=this->height;
        range=this->range_max;
        int i, j;
        FILE *fp = fopen(src_file_name.c_str(), "wb"); /* b - binary mode */
        (void) fprintf(fp, "P6\n%d %d\n%d\n", dimx, dimy,range);
        for (j = 0; j < dimy; ++j)
        {
            for (i = 0; i < dimx; ++i)
            {
                static unsigned char color[3];
                color[0] = this->bitmap[j][i].red %( range+1);  /* red */
                color[1] = this->bitmap[j][i].green % (range+1);  /* green */
                color[2] = this->bitmap[j][i].blue % (range+1);  /* blue */
                (void) fwrite(color, 1, 3, fp);
            }
        }
        (void) fclose(fp);

    }

    image duplicate_image(image img)
    {
        image dup_image;
        dup_image.set_width(img.get_width());
        dup_image.set_height(img.get_height());
        dup_image.set_range_max(img.get_range_max());
        dup_image.set_bitmap(img.get_bitmap());
        return dup_image;
    }

    image operator-(image& img)
    {
        image sub_img;
        sub_img=sub_img.duplicate_image(img);
        int height=img.get_height();
        int width=img.get_width();
        //cout<<height<<" "<<width<<endl;
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                sub_img.bitmap[i][j]=this->bitmap[i][j]-img.bitmap[i][j];
            }
        }
        return sub_img;
    }

    image operator+(image& img)
    {
        image add_img;
        add_img=add_img.duplicate_image(img);
        int height=img.get_height();
        int width=img.get_width();
        //cout<<height<<" "<<width<<endl;
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                add_img.bitmap[i][j]=this->bitmap[i][j]+img.bitmap[i][j];
            }
        }
        return add_img;
    }

};


image read_image(string src_file_name)
{
    int buff_len=256;

    FILE *pf=fopen(src_file_name.c_str(), "rb");
    char buf[buff_len], *t;
    unsigned int w, h, d;
    int r;

    t = fgets(buf, buff_len, pf);
    do
    {
        t = fgets(buf, buff_len, pf);
    }
    while ( strncmp(buf, "#", 1) == 0 );
    r = sscanf(buf, "%u %u", &w, &h);

    r = fscanf(pf, "%u", &d);
    fseek(pf, 1, SEEK_CUR);

    image img(w,h,d);

    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            unsigned char arr[3];
            fread(arr, sizeof(unsigned char), 3, pf);
            pixel px((unsigned int)arr[0],(unsigned int)arr[1],(unsigned int)arr[2]);
            img.bitmap[i][j]=px;
        }
    }
    return img;
}
