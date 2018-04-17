#include <iostream>
#include "opencv/cv.hpp"
#include "opencv/highgui.h"
#include <iostream>
#include <math.h>
#include "funcao.h"

using namespace std;
using namespace cv;

//função de truncamento
int trunca(float v){

    int valor = 0;
    valor = (int)v;

    if(v>255)
    {
        valor=255;
    }if(v<0)
    {
        valor=0;
    }

    return valor;
}


//-----------------------------------------------------------PASSA ALTA----------------------------------------------------------------------
//Mascara de Roberts na Horizontal e Vertical
//horizontal
Mat robertsH(Mat img){
    float Gx;
    Mat img2 = img.clone();

    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            Gx = img.at<uchar>(i,j)-img.at<uchar>(i+1,j+1);
            img2.at<uchar>(i,j)=trunca(sqrt(Gx*Gx));
        }
    }
    return img2;
}

//vertical
Mat robertsV(Mat img){
    float Gy;
    Mat img2 = img.clone();

    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            Gy = img.at<uchar>(i,j+1)-img.at<uchar>(i+1,j);
            img2.at<uchar>(i,j)=trunca(sqrt(Gy*Gy));
        }
    }
    return img2;
}


//---------------------------------------------------------LIMIARIZAÇÃO-----------------------------------------------------------------------
//Aplica o limiar
Mat limiar(Mat img, int T){
    int pixel;
    Mat img2 = img.clone();

    for(int i=0;i<img.rows; i++){
        for(int j=0;j<img.cols; j++){
            pixel = img.at<uchar>(i,j);
            if(pixel<=T){
                pixel=0;
            }else{
                pixel=255;
            }
            img2.at<uchar>(i,j)=pixel;
        }
    }

    return img2;

}

//Encontrar o limiar
//LIMIAR POR DOIS PICOS
int doisPicos(Mat img){
    int pico1=0, pico2=0, aux=-1, media=0;
    uchar *hist;

    hist = histograma(img);

    for(int i=0; i<256; i++){
        if(hist[i]>aux){
            aux=hist[i];
            pico1=i;
        }
    }

    for(int k=0; k<256; k++){
        if((pow(k-(pico1),2)*hist[k])>aux){
            aux=pow((k-pico1),2)*hist[k];
            pico2=k;
        }
    }

    media = abs((pico1+pico2)/2);

    return media;

}

//Função histograma
uchar *histograma(Mat img){
    uchar hist[256];

    for(int i=0; i<256; i++){
        hist[i]=0;
    }
    for(int i=0;i<img.rows; i++){
        for(int j=0;j<img.cols; j++){
            hist[img.at<uchar>(i,j)++];
        }
    }

    return hist;
}

//---------------------------------------------------------MORFOLOGIA----------------------------------------------------------------------
//ABERTURA
Mat abertura(Mat img, Mat element){
    erode(img, img, element);
    dilate(img, img, element);

    return img;
}



//------------------------------------------------------------SOBEL-------------------------------------------------------------------------
Mat sobelV(Mat img){
    Mat img2;
    int mascX[3][3]={-1, 0, 1,
                 -2, 0, 2,
                 -1, 0, 1};
    img2 = img.clone();
    int convX;
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            convX=0;
            for(int x=-1;x<=1;x++){
                for(int y=-1;y<=1;y++){
                    convX = convX + mascX[y+1][x+1]*img.at<uchar>(i-y,j-x);
                }
            }
            img2.at<uchar>(i,j)=trunca(convX);
        }
    }

    return img2;
}

Mat sobelH(Mat img){
    Mat img2;
    int mascY[3][3]={-1, -2, -1,
                      0,  0,  0,
                      1,  2,  1};
    img2 = img.clone();
    int convY;
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            convY=0;
            for(int x=-1;x<=1;x++){
                for(int y=-1;y<=1;y++){
                    convY = convY + mascY[y+1][x+1]*img.at<uchar>(i-y,j-x);
                }
            }
            img2.at<uchar>(i,j)=trunca(convY);

        }
    }

    return img2;
}



