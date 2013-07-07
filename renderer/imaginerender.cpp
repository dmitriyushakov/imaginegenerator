#include<QImage>

#include "imaginerender.h"

ImagineRender::ImagineRender(){}

ImagineRender::ImagineRender(Layer &lay):QObject(){
    color=new ColorCalculator(lay);
    _stop=false;
    hasAlpha=lay.alphaIsSet();
    coordSys=lay.getSystem();
}

ImagineRender::~ImagineRender(){
    delete color;
}

QImage* ImagineRender::render(int width, int height){
    QImage *img=new QImage(width,height,hasAlpha?QImage::Format_ARGB32:QImage::Format_RGB32);
    lprogr=0;

    int dx=0;
    int dy=0;
    double drx=0;
    double dry=0;

    if(coordSys.xPos()==System::XMiddle){
        dx=width/2;
    }else if(coordSys.xPos()==System::Right){
        dx=width;
    }else{
        dx=0;
    }
    dx+=coordSys.getShiftX();
    drx=double(dx)/width;

    if(coordSys.yPos()==System::YMiddle){
        dy=height/2;
    }else if(coordSys.yPos()==System::Down){
        dy=height;
    }else{
        dy=0;
    }
    dy+=(coordSys.yOrientation()==System::ToDown)?coordSys.getShiftY():-coordSys.getShiftY();
    dry=double(dy)/height;

    color->setSize(width,height);

    if(coordSys.type()==System::Rectangle){
        for(int y=0;y<height;y++){
            double ry=double(y)/height;
            for(int x=0;x<width;x++){
                double rx=double(x)/width;

                if(coordSys.yOrientation()==System::ToDown){
                    img->setPixel(x,y,color->getPixel(x-dx,y-dy,rx-drx,ry-dry));
                }else{
                    img->setPixel(x,y,color->getPixel(x-dx,-y+dy,rx-drx,-ry+dry));
                }

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
    }else{
        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++){

                if(coordSys.yOrientation()==System::ToDown){
                    img->setPixel(x,y,color->getRadialPixel(x,y,dx,dy));
                }else{
                    img->setPixel(x,y,color->getRadialPixel(x,-y,dx,-dy));
                }

                if(color->hasError()||toStop()){
                    delete img;
                    return 0;
                }
            }
            int progr=y*100/height;
            if(progr!=lprogr){
                lprogr=progr;
                emit progress(progr);
            }
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
