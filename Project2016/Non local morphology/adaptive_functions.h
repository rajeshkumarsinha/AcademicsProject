#define e 1.78
#define pii pair<int,int>
#define mp make_pair
#define vpp vector<vector<pii> >

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
    if(curr_x>=0 && curr_x<h && curr_y>=0 && curr_y<w)
    return true;
    else return false;
}

double calculate_w_bar(image &img,pii patch_x,pii patch_y,int patch_size,int sigma)
{
    vector<vector<int> > result(patch_size,vector<int>(patch_size,0));
    vector<vector<pii> > patch_object=make_structure(patch_size,patch_size,patch_size/2,patch_size/2);
    int h=img.get_height();
    int w=img.get_width();
    long long euclidean_sum=0;
    for(int i=0;i<patch_size;i++)
    {
        for(int j=0;j<patch_size;j++)
        {
            int px_x=patch_x.first+patch_object[i][j].first;//x coordinate of patch x
            int px_y=patch_x.second+patch_object[i][j].second;//y coordinate of patch x
            int py_x=patch_y.first+patch_object[i][j].first;
            int py_y=patch_y.second+patch_object[i][j].second;
            int val_patch_x=0,val_patch_y=0;
            //cout<<px_x<<" "<<px_y<<" "<<py_x<<" "<<py_y<<endl;
            if(in_range(px_x,px_y,h,w)) val_patch_x=img.bitmap[px_x][px_y];
            if(in_range(py_x,py_y,h,w)) val_patch_y=img.bitmap[py_x][py_y];
            result[i][j]=val_patch_x-val_patch_y;
            euclidean_sum+=result[i][j]*result[i][j];
        }
    }
    double ans=(double)euclidean_sum/(double)(sigma*sigma);
    ans=pow(e,-ans);
    return ans;
}

double calculate_denm(image &img,pii center,int patch_size,int sigma)
{
    double ans=0;
    int h=img.get_height();
    int w=img.get_width();
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            ans+=calculate_w_bar(img,center,make_pair(w,h),patch_size,sigma);
        }
    }
    return ans;

}

double calculate_w(image &img,pii patch_x,pii patch_y,int patch_size,int sigma)
{
    int height=img.get_height();
    int width=img.get_width();
    double denm=calculate_denm(img,patch_x,patch_size,sigma);
    double numr=calculate_w_bar(img,patch_x,patch_y,patch_size,sigma);
    double ans= numr/denm;
    return ans;
}

image adaptive_erosion(image &img,int s_row,int s_col,int s_x,int s_y,int patch_size,int sigma)
{
    image e_image;
    e_image=e_image.duplicate_image(img);
    int height=img.get_height();
    int width=img.get_width();
    int range=img.get_range_max();

    vpp structure = make_structure(s_row,s_col,s_x,s_y);

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            //place the origin of the structure at i,j
            double current=img.bitmap[i][j];
            for(int ii=0;ii<s_row;ii++)
            {
                for(int jj=0;jj<s_col;jj++)
                {
                    int x=i+structure[ii][jj].first;
                    int y=j+structure[ii][jj].second;

                    if(in_range(x,y,height,width))
                    {
                        double temp=calculate_w(img,make_pair(i,j),make_pair(x,y),patch_size,sigma);
                        temp=log(abs(temp));
                        current=min(current,img.bitmap[x][y]-temp);
                    }
                }
            }
            e_image.bitmap[i][j]=current;
            //if(e_image.bitmap[i][j]>range) e_image.bitmap[i][j]=range;

        }
    }
    //cout<<"sdf";
    return e_image;
}

image adaptive_dilation(image &img,int s_row,int s_col,int s_x,int s_y,int patch_size,int sigma)
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
            double current=img.bitmap[i][j];
            for(int ii=0;ii<s_row;ii++)
            {
                for(int jj=0;jj<s_col;jj++)
                {
                    int x=i+structure[ii][jj].first;
                    int y=j+structure[ii][jj].second;

                    if(in_range(x,y,height,width))
                    {
                        double temp=calculate_w(img,make_pair(i,j),make_pair(x,y),patch_size,sigma);
                        temp=log(temp);
                        current=max(current,img.bitmap[x][y]+temp);
                    }
                }
            }
            d_image.bitmap[i][j]=current;
        }
    }
    return d_image;
}

image adaptive_opening(image &src,int s_row,int s_col,int s_x,int s_y,int patch_size,int sigma)
{
    image eroded=adaptive_erosion(src,s_row,s_col,s_x,s_y,patch_size,sigma);
    image dilated=adaptive_dilation(eroded,s_row,s_col,s_x,s_y,patch_size,sigma);
    return dilated;
}

image adaptive_closing (image &src,int s_row,int s_col,int s_x,int s_y,int patch_size,int sigma)
{
    image dilated=adaptive_dilation(src,s_row,s_col,s_x,s_y,patch_size,sigma);
    image eroded=adaptive_erosion(dilated,s_row,s_col,s_x,s_y,patch_size,sigma);
    return eroded;
}

image adaptive_top_hat_filter(image &src,int s_row,int s_col,int s_x,int s_y,int patch_size,int sigma)
{
    image o_img=adaptive_opening(src,s_row,s_col,s_x,s_y,patch_size,sigma);
    //org-opening
    image t_image=t_image.duplicate_image(src);

    return t_image-o_img;

}

image adaptive_black_top_hat_filter(image &src,int s_row,int s_col,int s_x,int s_y,int patch_size,int sigma)
{
    image c_img=adaptive_closing(src,s_row,s_col,s_x,s_y,patch_size,sigma);
    //org-opening
    image t_image=t_image.duplicate_image(src);

    return c_img-t_image;
}
