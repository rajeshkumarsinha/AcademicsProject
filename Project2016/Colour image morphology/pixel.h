const int bandwidth =255;
class pixel
{
public:
    int red,green,blue;
    pixel(int red,int green,int blue)
    {
        this->red=red;
        this->green=green;
        this->blue=blue;
    }
    pixel()
    {
    }
    int get_red()
    {
        return this->red;
    }
    int get_green()
    {
        return this->green;
    }
    int get_blue()
    {
        return this->blue;
    }
    void set_red(int red)
    {
        this->red=red;
    }
    void set_green(int green)
    {
        this->green=green;
    }
    void set_blue(int blue)
    {
        this->blue=blue;
    }

    pixel operator-(pixel& px)
    {
        pixel ans_px(this->red-px.red,this->green-px.green,this->blue-px.blue);
        if(ans_px.red<0) ans_px.red=0;
        if(ans_px.green<0) ans_px.green=0;
        if(ans_px.blue<0) ans_px.green=0;

       // if(ans_px.red<0) ans_px.red+=bandwidth;
       // if(ans_px.green<0) ans_px.green+=bandwidth;
       // if(ans_px.blue<0) ans_px.green+=bandwidth;
        return ans_px;
    }

    pixel operator+(pixel& px)
    {
        pixel ans_px(this->red-px.red,this->green-px.green,this->blue-px.blue);
        if(ans_px.red>bandwidth) ans_px.red=bandwidth;
        if(ans_px.green>bandwidth) ans_px.green=bandwidth;
        if(ans_px.blue>bandwidth) ans_px.green=bandwidth;

       // if(ans_px.red>bandwidth) ans_px.red-=bandwidth;
       // if(ans_px.green>bandwidth) ans_px.green-=bandwidth;
       // if(ans_px.blue>bandwidth) ans_px.green-=bandwidth;
        return ans_px;
    }

    bool operator<(pixel &px)
    {
        //return true if px greater than this else false
        if(px.red>this->red && px.green>this->green && px.blue>this->blue) return true;
        else return false;
    }
};
