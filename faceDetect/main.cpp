#include "opencv/cv.hpp"
#include "opencv/highgui.h"
#include <iostream>
#include "funcao.h"

using namespace std;
using namespace cv;

int main()
{

    Mat img, imgH, imgV, imgHB, imgVB;
    img = imread("imagens\\luiz.jpg",0);
    imshow("imgOriginal",img);

    //imagem matriz Vertical
    imgV = sobelV(img);
    imshow("imgProcessadaH",imgV);

    //imagem matriz Horizontal
    imgH = sobelH(img);
    imshow("imgProcessadaV",imgH);

    //Binariza
    threshold(imgH, imgHB, 0, 255, THRESH_OTSU);
    threshold(imgV, imgVB, 0, 255, THRESH_OTSU);

    imshow("imgProcessadaVB",imgVB);
    imshow("imgProcessadaHB",imgHB);

    //Abertura
    //elemento estruturante
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3,3),Point(2,2));
    imgHB = abertura(imgHB, element);
    imgVB = abertura(imgVB, element);
    imshow("aberturaHB", imgHB);
    imshow("aberturaVB", imgVB);




    waitKey(0);
    destroyAllWindows();

    return 0;
}
