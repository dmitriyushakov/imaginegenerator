#ifndef SCRIPTABLECALCULATOR_H
#define SCRIPTABLECALCULATOR_H

#include <QtScript/QScriptProgram>
#include <QtScript/QScriptEngine>

#include "model/layer.h"

class ScriptableCalculator
{
    bool isRunnable;
    QScriptProgram componentProg;
    QScriptEngine *engine;
public:
    ScriptableCalculator();
    ScriptableCalculator(Layer &lay,ComponentType component,QScriptEngine *engine);
    bool hasError();
    QString errorMessage();
    void setSize(int width,int height);
    int math();
};

#endif // SCRIPTABLECALCULATOR_H
