#ifndef COLORCALCULATOR_H
#define COLORCALCULATOR_H

#include <QtScript/QScriptEngine>

#include "model/layer.h"
#include "scriptablecalculator.h"

class ColorCalculator
{
    bool isColor;
    bool _isnull;
    bool _hasError;
    QString _errorMessage;
    ScriptableCalculator *grey;
    ScriptableCalculator *red;
    ScriptableCalculator *green;
    ScriptableCalculator *blue;
    QScriptEngine engine;
    bool absolutex;
    bool absolutey;
public:
    QScriptEngine *getEngine();
    ColorCalculator();
    ColorCalculator(Layer &lay);
    ~ColorCalculator();
    bool isNull();
    uint getPixel(int x,int y,double rx,double ry);
    void setSize(int width,int height);
    bool hasError();
    QString errorMessage();
};

#endif // COLORCALCULATOR_H
