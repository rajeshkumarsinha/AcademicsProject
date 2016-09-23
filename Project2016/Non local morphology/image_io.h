#define vvi vector<vector<int> >
#define vi vector<int>
class image
{
private:
    int width,height,range_max;
    //height is the number of rows
    //width is the number of cols


public:
    vvi bitmap;
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
    void set_bitmap(vvi bitmap)
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
    vvi get_bitmap()
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
        bitmap.resize(height,vector<int>(width));
    }

    void print_image()
    {
        cout<<width<<" "<<height<<" "<<range_max<<endl;
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                cout<<bitmap[i][j]<<endl;
            }
        }
    }

    void print_image(int param)
    {
         cout<<"width="<<width<<" height="<<height<<" range="<<range_max<<endl;
       //  cout<<bitmap.size()<<endl;
       //  cout<<bitmap[0].size();
    }

    void write_image(string src_file_name)
    {
        int dimx, dimy, range;
        dimx=this->width;
        dimy=this->height;
        range=this->range_max;
        int i, j;
        FILE *fp = fopen(src_file_name.c_str(), "wb"); /* b - binary mode */
        (void) fprintf(fp, "P5\n%d %d\n%d\n", dimx, dimy,range);
        for (j = 0; j < dimy; ++j)
        {
            for (i = 0; i < dimx; ++i)
            {
                int temp=this->bitmap[j][i];
                temp+=(range+1);
                static unsigned char color[1];
             //   color[0]+=(range+1);
                color[0] = temp%(range+1);
                (void) fwrite(color, 1, 1, fp);
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
            unsigned char arr[1];
            fread(arr, sizeof(unsigned char), 1, pf);
            img.bitmap[i][j]=(unsigned int)arr[0];
        }
    }
    return img;
}

