#include<bits/stdc++.h>
using namespace std;
#include "image_io.h"
#include "adaptive_functions.h"

int main()
{
    string file_src="test.pgm";
    image img=read_image(file_src);
    int s_row,s_col,s_x,s_y;
    int patch_size,sigma;
    cout<<"Enter the number of row in the structuring element: ";
    cin>>s_row;
    cout<<"Enter the number of column in the structuring element: ";
    cin>>s_col;
    cout<<"Enter the x coordinate of origin: ";
    cin>>s_x;
    cout<<"Enter the y coordinate of origin: ";
    cin>>s_y;
    cout<<"Enter the size of patch(patch will always be square so enter the dimesion of one side): ";
    cin>>patch_size;
    cout<<"Enter the value of smoothing factor: ";
    cin>>sigma;

    //img.print_image();
    image e_img1=adaptive_erosion(img,s_row,s_col,s_x,s_y,patch_size,sigma);
    image d_img1=adaptive_dilation(img,s_row,s_col,s_x,s_y,patch_size,sigma);

    e_img1.write_image("eroded_lenna1.pgm");
    d_img1.write_image("dilated_lenna1.pgm");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
   /* image e_img2=adaptive_erosion(e_img1,s_row,s_col,s_x,s_y,patch_size,sigma);
    image d_img2=adaptive_dilation(d_img1,s_row,s_col,s_x,s_y,patch_size,sigma);

    e_img2.write_image("eroded_lenna2.pgm");
    d_img2.write_image("dilated_lenna2.pgm");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    image e_img3=adaptive_erosion(e_img2,s_row,s_col,s_x,s_y,patch_size,sigma);
    image d_img3=adaptive_dilation(d_img2,s_row,s_col,s_x,s_y,patch_size,sigma);

    e_img3.write_image("eroded_lenna3.pgm");
    d_img3.write_image("dilated_lenna3.pgm");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    image e_img4=adaptive_erosion(e_img3,s_row,s_col,s_x,s_y,patch_size,sigma);
    image d_img4=adaptive_dilation(d_img3,s_row,s_col,s_x,s_y,patch_size,sigma);

    e_img4.write_image("eroded_lenna4.pgm");
    d_img4.write_image("dilated_lenna4.pgm");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    image e_img5=adaptive_erosion(e_img4,s_row,s_col,s_x,s_y,patch_size,sigma);
    image d_img5=adaptive_dilation(d_img4,s_row,s_col,s_x,s_y,patch_size,sigma);

    e_img5.write_image("eroded_lenna5.pgm");
    d_img5.write_image("dilated_lenna5.pgm");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    image e_img6=adaptive_erosion(e_img5,s_row,s_col,s_x,s_y,patch_size,sigma);
    image d_img6=adaptive_dilation(d_img5,s_row,s_col,s_x,s_y,patch_size,sigma);

    e_img6.write_image("eroded_lenna6.pgm");
    d_img6.write_image("dilated_lenna6.pgm");*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    image o_img1=adaptive_opening(img,s_row,s_col,s_x,s_y,patch_size,sigma);
    image c_img1=adaptive_closing(img,s_row,s_col,s_x,s_y,patch_size,sigma);

    o_img1.write_image("opening_lenna1.pgm");
    c_img1.write_image("closing_lenna1.pgm");

    c_img1=d_img1-e_img1;
    c_img1.write_image("outline.pgm");

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /* image o_img2=adaptive_opening(o_img1,s_row,s_col,s_x,s_y,patch_size,sigma);
    image c_img2=adaptive_closing(c_img1,s_row,s_col,s_x,s_y,patch_size,sigma);

    o_img2.write_image("opening_lenna2.pgm");
    c_img2.write_image("closing_lenna2.pgm");

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     image o_img3=adaptive_opening(o_img2,s_row,s_col,s_x,s_y,patch_size,sigma);
    image c_img3=adaptive_closing(c_img2,s_row,s_col,s_x,s_y,patch_size,sigma);

    o_img3.write_image("opening_lenna3.pgm");
    c_img3.write_image("closing_lenna3.pgm");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     image o_img4=adaptive_opening(o_img3,s_row,s_col,s_x,s_y,patch_size,sigma);
    image c_img4=adaptive_closing(c_img3,s_row,s_col,s_x,s_y,patch_size,sigma);

    o_img4.write_image("opening_lenna4.pgm");
    c_img4.write_image("closing_lenna4.pgm");

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     image o_img5=adaptive_opening(o_img4,s_row,s_col,s_x,s_y,patch_size,sigma);
    image c_img5=adaptive_closing(c_img4,s_row,s_col,s_x,s_y,patch_size,sigma);

    o_img5.write_image("opening_lenna5.pgm");
    c_img5.write_image("closing_lenna5.pgm");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*image top_hat_filter_image=top_hat_filter(img,s_row,s_col,s_x,s_y);
    top_hat_filter_image.write_image("top_hat_filter_lenna.ppm");

    image s_image=img-top_hat_filter_image;
    s_image.write_image("s_image.ppm");

    image black_top_hat_filter_image=black_top_hat_filter(img,s_row,s_col,s_x,s_y);
    black_top_hat_filter_image.write_image("black_top_hat_filter_lenna.ppm");

    image outline_image=outline(img,s_row,s_col,s_x,s_y);
    outline_image.write_image("outline_lenna.ppm");*/

}
