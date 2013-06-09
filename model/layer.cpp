#include "layer.h"

Layer::Layer()
{
    xtype=Absolute;
    ytype=Absolute;
    colortype=Tricolor;
}

QString Layer::getScript(){
    return script;
}

QString Layer::getRComponent(){
    return rcomponent;
}

QString Layer::getGComponent(){
    return gcomponent;
}

QString Layer::getBComponent(){
    return bcomponent;
}

QString Layer::getGreyComponent(){
    return greycomponent;
}

QString Layer::getComponent(ComponentType component){
    switch(component){
        case RedColor:return rcomponent;break;
        case GreenColor:return gcomponent;break;
        case BlueColor:return bcomponent;break;
        case Grey:return greycomponent;break;
        default:return QString();break;
    }
}

PointType Layer::getXPointType(){
    return xtype;
}

PointType Layer::getYPointType(){
    return ytype;
}

ColorType Layer::getColorType(){
    return colortype;
}

void Layer::setScript(QString script){
    this->script=script;
}

void Layer::setRComponent(QString expr){
    rcomponent=expr;
}

void Layer::setGComponent(QString expr){
    gcomponent=expr;
}

void Layer::setBComponent(QString expr){
    bcomponent=expr;
}

void Layer::setGreyComponent(QString expr){
    greycomponent=expr;
}

void Layer::setComponent(ComponentType type,QString exp){
    switch(type){
        case RedColor:rcomponent=exp;break;
        case GreenColor:gcomponent=exp;break;
        case BlueColor:bcomponent=exp;break;
        case Grey:greycomponent=exp;break;
    }
}

void Layer::setXPointType(PointType type){
    xtype=type;
}

void Layer::setYPointType(PointType type){
    ytype=type;
}

void Layer::setColorType(ColorType type){
    colortype=type;
}

System Layer::getSystem(){
    return system;
}

void Layer::setSystem(System s){
    system=s;
}
