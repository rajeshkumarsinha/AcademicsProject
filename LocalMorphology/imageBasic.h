void maxmin(Image image, int& imin,int &imax,int &highpow)
{
    vii img=image.getimg();
    imax = img[0][0];
    imin = img[0][0];

    for(int i=0; i<image.getrow(); i++)
    {
        for(int j=0; j<image.getcol(); j++)
        {
            if(imax < img[i][j]) imax = img[i][j];
            if(imin > img[i][j]) imin = img[i][j];
        }
    }

    highpow = 1;
    int temp = imax-1;
    do{
            temp = temp/2;
            highpow = highpow*2;
    }while(temp > 0);
}

int min_structure(vii structure)
{
    int temp=INT_MAX;
    int srow=structure.size();
    int scol=structure[0].size();
    for(int i=0;i<srow;i++)
    for(int j=0;j<scol;j++)
    temp=min(temp,structure[i][j]);
    return temp;
}

int max_structure(vii structure)
{
    int temp=INT_MIN;
    int srow=structure.size();
    int scol=structure[0].size();
    for(int i=0;i<srow;i++)
    for(int j=0;j<scol;j++)
    temp=max(temp,structure[i][j]);
    return temp;
}

void upper_limit(Image &test,Image &tester)
{
    //change the value at each point of test image either greater than or equal to the tester value
    vii Test=test.getimg();
    vii Tester=tester.getimg();
    int row=test.getrow();
    int col=test.getcol();
    for(int i=0;i<row;i++)
    for(int j=0;j<col;j++)
    if(Tester[i][j]<Test[i][j]) Test[i][j]=Tester[i][j];

    test.setimg(Test);
    tester.setimg(Tester);
}

void lower_limit(Image &test,Image &tester)
{
    //change the value at each point of test image either greater than or equal to the tester value
    vii Test=test.getimg();
    vii Tester=tester.getimg();
    int row=test.getrow();
    int col=test.getcol();
    for(int i=0;i<row;i++)
    for(int j=0;j<col;j++)
    if(Tester[i][j]>Test[i][j]) Test[i][j]=Tester[i][j];

    test.setimg(Test);
    tester.setimg(Tester);
}

void swapper(Image &test,Image &tester,int &count)
{
    vii Test=test.getimg();
    vii Tester=tester.getimg();
    count=0;
    int row=test.getrow();
    int col=test.getcol();
    for(int i=0;i<row;i++)
    for(int j=0;j<col;j++)
    if(Test[i][j]!=Tester[i][j])
    {
       swap(Test[i][j],Tester[i][j]);
       count++;
    }
    test.setimg(Test);
    tester.setimg(Tester);
}

Image shift(Image image,vii structure)
{
    int row=image.getrow()-structure.size();
    int col=image.getcol()-structure[0].size();
    int srow=structure.size();
    int scol=structure[0].size();
    int row_org=srow/2;
    int col_org=scol/2;

    Image dup_img;
    dup_img.setrow(row);
    dup_img.setcol(col);

    vii temp(row,vector<int>(col,0));
    vii img=image.getimg();

    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            temp[i][j] = img[i+row_org][j+col_org];

    dup_img.setimg(temp);
    return dup_img;
}

