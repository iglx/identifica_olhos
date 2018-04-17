#ifndef FUNCAO
#define FUNCAO
#include <iostream>
#include "opencv/cv.hpp"
#include "opencv/highgui.h"
#include <iostream>

using namespace cv;


//função de truncamento
int trunca(float v);

//Mascara de Roberts
Mat robertsH(Mat img);
Mat robertsV(Mat img);

//Limiar
Mat limiar(Mat img, int T);
int doisPicos(Mat img);
uchar *histograma(Mat img);

//Mofologia
Mat abertura(Mat img, Mat element);


//SOBEL
Mat sobelH(Mat img);
Mat sobelV(Mat img);

#endif // FUNCAO

