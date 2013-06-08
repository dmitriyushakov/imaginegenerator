#include<QImage>

#include "imaginerender.h"

ImagineRender::ImagineRender(){}

ImagineRender::ImagineRender(Layer &lay):QObject(){
    color=new ColorCalculator(lay);
    _stop=false;
}

ImagineRender::~ImagineRender(){
    delete color;
}

QImage* ImagineRender::render(int width, int height){
    QImage *img=new QImage(width,height,QImage::Format_RGB32);
    lprogr=0;
    color->setSize(width,height);
    for(int y=0;y<height;y++){
        double ry=double(y)/height;
        for(int x=0;x<width;x++){
            double rx=double(x)/width;
            img->setPixel(x,y,color->getPixel(x,y,rx,ry));
            if(color->hasError()||toStop()){
                delete img;
                return 0;
            }
        }
        int progr=ry*100;
        if(progr!=lprogr){
            lprogr=progr;
            emit progress(progr);
        }
    }
    return img;
}

bool ImagineRender::hasError(){
    return color->hasError();
}

QString ImagineRender::errorMessage(){
    return color->errorMessage();
}

bool ImagineRender::toStop(){
    if(_stop){
        _stop=false;
        return true;
    }else return false;
}

void ImagineRender::stop(){
    _stop=true;
    color->getEngine()->abortEvaluation();
}
