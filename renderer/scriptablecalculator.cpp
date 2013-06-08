#include "scriptablecalculator.h"

ScriptableCalculator::ScriptableCalculator(){
    isRunnable=false;
}

ScriptableCalculator::ScriptableCalculator(Layer &lay, ComponentType component,QScriptEngine *e){
    QString prog=lay.getComponent(component);
    if(prog.isEmpty()){
        isRunnable=false;
        engine=0;
    }else{
        engine=e;

        componentProg=QScriptProgram(prog);
        isRunnable=!engine->hasUncaughtException();
    }
}

bool ScriptableCalculator::hasError(){
    if(engine)return engine->hasUncaughtException();
    else return false;
}

QString ScriptableCalculator::errorMessage(){
    if(engine)return engine->uncaughtException().toString()
            .append("\n").append(QObject::tr("Line:"))
            .append(QString::number(engine->uncaughtExceptionLineNumber()));
    else return QString();
}

int ScriptableCalculator::math(){
    if(!isRunnable)return 0;

    QScriptValue value=engine->evaluate(componentProg);
    if(engine->hasUncaughtException()){
        isRunnable=false;
        return 0;
    }else{
        if(!value.isNumber())return 0;
        int ivalue=value.toInt32();
        if(ivalue>255)ivalue=255;
        if(ivalue<0)ivalue=0;
        return ivalue;
    }
}
