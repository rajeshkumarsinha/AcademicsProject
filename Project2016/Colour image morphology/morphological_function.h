#include"includes.h"
#include"circle_function.h"
vpp make_structure(int s_row,int s_col,int s_x,int s_y)
{
    vpp structure(s_row,vector<pii>(s_col,mp(0,0)));
    for(int i=0;i<s_row;i++)
    {
        for(int j=0;j<s_col;j++)
        {
            structure[i][j]=mp(j-s_x,i-s_y);
            //cout<<structure[i][j].first<<","<<structure[i][j].second<<"   ";
        }
        //cout<<endl;
    }
    return structure;
}


bool in_range(int curr_x,int curr_y,int h,int w)
{
    if(curr_x>=0 && curr_x<w && curr_y>=0 && curr_y<h)
    return true;
    else return false;
}

image erosion(image &img,int s_row,int s_col,int s_x,int s_y)
{
    image e_image;
    e_image=e_image.duplicate_image(img);
    int height=img.get_height();
    int width=img.get_width();

    vpp structure = make_structure(s_row,s_col,s_x,s_y);

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            //place the origin of the structure at i,j
            vector<pixel> current;
            for(int ii=0;ii<s_row;ii++)
            {
                for(int jj=0;jj<s_col;jj++)
                {
                    int x=i+structure[ii][jj].first;
                    int y=j+structure[ii][jj].second;

                    if(in_range(x,y,height,width))
                    {
                        current.pb(img.bitmap[x][y]);
                    }
                }
            }
            e_image.bitmap[i][j]=find_min(current);
        }
    }
    return e_image;
}

image dilation(image &img,int s_row,int s_col,int s_x,int s_y)
{
    image d_image;
    d_image=d_image.duplicate_image(img);
    int height=img.get_height();
    int width=img.get_width();

    vpp structure = make_structure(s_row,s_col,s_x,s_y);

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            vector<pixel> current;
            for(int ii=0;ii<s_row;ii++)
            {
                for(int jj=0;jj<s_col;jj++)
                {
                    int x=i+structure[ii][jj].first;
                    int y=j+structure[ii][jj].second;
                    if(in_range(x,y,height,width))
                    {
                        current.pb(img.bitmap[x][y]);
                    }
                }
            }
            d_image.bitmap[i][j]=find_max(current);
        }
    }
    return d_image;
}
/*
image erosion(image &img,int s_row,int s_col,int s_x,int s_y)
{
    image e_image;
    e_image=e_image.duplicate_image(img);
    int height=img.get_height();
    int width=img.get_width();

    vpp structure = make_structure(s_row,s_col,s_x,s_y);

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            //place the origin of the structure at i,j
            vector<pixel> current;
            for(int ii=0;ii<s_row;ii++)
            {
                for(int jj=0;jj<s_col;jj++)
                {
                    int x=i+structure[ii][jj].first;
                    int y=j+structure[ii][jj].second;

                    if(in_range(x,y,height,width))
                    {
                        current.pb(img.bitmap[x][y]);
                    }
                }
            }

            pixel min_pixel=find_min(current);
            if(min_pixel<e_image.bitmap[i][j]){}
            else if(e_image.bitmap[i][j]<min_pixel)
            e_image.bitmap[i][j]=min_pixel;
            else
            {
                vector<pixel> temp;
                temp.pb(e_image.bitmap[i][j]);
                temp.pb(min_pixel);
                e_image.bitmap[i][j]=find_max(temp);
            }
        }
    }
    return e_image;
}


image dilation(image &img,int s_row,int s_col,int s_x,int s_y)
{
    image d_image;
    d_image=d_image.duplicate_image(img);
    int height=img.get_height();
    int width=img.get_width();

    vpp structure = make_structure(s_row,s_col,s_x,s_y);

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            vector<pixel> current;
            for(int ii=0;ii<s_row;ii++)
            {
                for(int jj=0;jj<s_col;jj++)
                {
                    int x=i+structure[ii][jj].first;
                    int y=j+structure[ii][jj].second;
                    if(in_range(x,y,height,width))
                    {
                        current.pb(img.bitmap[x][y]);
                    }
                }
            }
            pixel max_pixel=find_max(current);
            if(max_pixel<d_image.bitmap[i][j])
            {
                 d_image.bitmap[i][j]=max_pixel;
            }
            else if(d_image.bitmap[i][j]<max_pixel){}
            else
            {
                vector<pixel> temp;
                temp.pb(d_image.bitmap[i][j]);
                temp.pb(max_pixel);
                d_image.bitmap[i][j]=find_min(temp);
            }
        }
    }
    return d_image;
}*/

image opening(image &src,int s_row,int s_col,int s_x,int s_y)
{
    image eroded=erosion(src,s_row,s_col,s_x,s_y);
    image dilated=dilation(eroded,s_row,s_col,s_x,s_y);
    return dilated;
}

image closing (image &src,int s_row,int s_col,int s_x,int s_y)
{
    image dilated=dilation(src,s_row,s_col,s_x,s_y);
    image eroded=erosion(dilated,s_row,s_col,s_x,s_y);
    return eroded;
}

image top_hat_filter(image &src,int s_row,int s_col,int s_x,int s_y)
{
    image o_img=opening(src,s_row,s_col,s_x,s_y);
    //org-opening
    image t_image=t_image.duplicate_image(src);

    return t_image-o_img;

}

image black_top_hat_filter(image &src,int s_row,int s_col,int s_x,int s_y)
{
    image c_img=closing(src,s_row,s_col,s_x,s_y);
    //org-opening
    image t_image=t_image.duplicate_image(src);

    return c_img-t_image;
}

image outline(image &src,int s_row,int s_col,int s_x,int s_y)
{
    image dilated=dilation(src,s_row,s_col,s_x,s_y);
    image eroded=erosion(src,s_row,s_col,s_x,s_y);
    image outline;
    outline=dilated-eroded;
  return outline;
}

image black_white(image &img,int s_row,int s_col)
{
    image dup;
    dup=black_white.duplicate_image();
}


