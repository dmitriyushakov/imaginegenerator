#include "colorcalculator.h"
#include "scriptapi.h"
#include "qmath.h"
#include "math.h"

ColorCalculator::ColorCalculator()
{
    _isnull=true;
    _hasError=false;
}

ColorCalculator::ColorCalculator(Layer &lay){
    _isnull=false;
    _hasError=false;

    ScriptAPI::installAPI(engine);

    engine.evaluate(lay.getScript());

    absolutex=(lay.getXPointType()==Absolute);
    absolutey=(lay.getYPointType()==Absolute);

    if(lay.getColorType()==Tricolor){
        red=new ScriptableCalculator(lay,RedColor,&engine);
        green=new ScriptableCalculator(lay,GreenColor,&engine);
        blue=new ScriptableCalculator(lay,BlueColor,&engine);
        grey=0;
        isColor=true;
    }else{
        red=0;
        green=0;
        blue=0;
        grey=new ScriptableCalculator(lay,Grey,&engine);
        isColor=false;
    }
}

ColorCalculator::~ColorCalculator(){
    delete red;
    delete green;
    delete blue;
    delete grey;
}

bool ColorCalculator::isNull(){
    return _isnull;
}

uint ColorCalculator::getPixel(int x,int y,double rx,double ry){
    if(_isnull)return 0;

    if(absolutex)engine.globalObject().setProperty("x",x);
    else engine.globalObject().setProperty("x",rx);

    if(absolutey)engine.globalObject().setProperty("y",y);
    else engine.globalObject().setProperty("y",ry);

    QScriptValue absoluteVal=engine.newObject();
    absoluteVal.setProperty("x",x);
    absoluteVal.setProperty("y",y);
    engine.globalObject().setProperty("absolute",absoluteVal);

    QScriptValue relativeVal=engine.newObject();
    relativeVal.setProperty("x",rx);
    relativeVal.setProperty("y",ry);
    engine.globalObject().setProperty("relative",relativeVal);

    return getPixel();
}

uint ColorCalculator::getPixel(){
    uint value=0;
    if(isColor){
        value=(red->math()<<16)|(green->math()<<8)|blue->math();
        if(red->hasError()){
            _hasError=true;
            _isnull=true;
            _errorMessage=red->errorMessage();
            return 0;
        }
        if(green->hasError()){
            _hasError=true;
            _isnull=true;
            _errorMessage=green->errorMessage();
            return 0;
        }
        if(blue->hasError()){
            _hasError=true;
            _isnull=true;
            _errorMessage=blue->errorMessage();
            return 0;
        }
    }else{
        value=grey->math()*0x010101;
        if(grey->hasError()){
            _hasError=true;
            _isnull=true;
            _errorMessage=grey->errorMessage();
        }
    }
    return value;
}

uint ColorCalculator::getRadialPixel(int x, int y, int cx, int cy){
    int dx=x-cx;
    int dy=y-cy;

    qreal radius=qSqrt(dx*dx+dy*dy);
    qreal sinus=0;
    if(radius>0)sinus=qreal(dy)/radius;
    qreal angle=qAsin(sinus);

    if(dx<0)angle=M_PI-angle;
    if(angle<0)angle+=M_PI*2;

    engine.globalObject().setProperty("r",radius);
    engine.globalObject().setProperty("a",angle);

    return getPixel();
}

bool ColorCalculator::hasError(){
    return _hasError;
}

QString ColorCalculator::errorMessage(){
    return _errorMessage;
}

void ColorCalculator::setSize(int width, int height){
    engine.globalObject().setProperty("width",QScriptValue(width));
    engine.globalObject().setProperty("height",QScriptValue(height));
}

QScriptEngine *ColorCalculator::getEngine(){
    return &engine;
}
