#include"includes.h"
#include"image.h"
#include"morphological_function.h"
int main()
{
    string file_src="lenna.ppm";
    image img=read_image(file_src);
    int s_row,s_col,s_x,s_y;
    cout<<"Enter the number of row in the structuring element: ";
    cin>>s_row;
    cout<<"Enter the number of column in the structuring element: ";
    cin>>s_col;
    cout<<"Enter the x coordinate of origin: ";
    cin>>s_x;
    cout<<"Enter the y coordinate of origin: ";
    cin>>s_y;

    image e_img=erosion(img,s_row,s_col,s_x,s_y);
    image d_img=dilation(img,s_row,s_col,s_x,s_y);

    e_img.write_image("eroded_lenna.ppm");
    d_img.write_image("dilated_lenna.ppm");

    image o_img=opening(img,s_row,s_col,s_x,s_y);
    image c_img=closing(img,s_row,s_col,s_x,s_y);

    o_img.write_image("opening_lenna.ppm");
    c_img.write_image("closing_lenna.ppm");

    image top_hat_filter_image=top_hat_filter(img,s_row,s_col,s_x,s_y);
    top_hat_filter_image.write_image("top_hat_filter_lenna.ppm");

    image s_image=img-top_hat_filter_image;
    s_image.write_image("s_image.ppm");

     image black_top_hat_filter_image=black_top_hat_filter(img,s_row,s_col,s_x,s_y);
    black_top_hat_filter_image.write_image("black_top_hat_filter_lenna.ppm");

    image outline_image=outline(img,s_row,s_col,s_x,s_y);
    outline_image.write_image("outline_lenna.ppm");

    image black_white=black_whilte(img,s_row,s_col);
    black_white.write_image("black_white.ppm");
}
