#include <QScriptContext>
#include <QScriptEngine>

#include "scriptapi.h"

#include "qmath.h"
#include "math.h"

QScriptValue ScriptAPI::funcSqrt(QScriptContext *cont, QScriptEngine *){
    if(cont->argumentCount()==0){
        cont->throwError("Have not argument.");
        return QScriptValue(0);
    }
    QScriptValue arg=cont->argument(0);
    if(!arg.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val=arg.toNumber();
    if(val<0){
        cont->throwError(QScriptContext::RangeError,"This number below zero.");
        return QScriptValue(0);
    }
    val=qSqrt(val);
    return QScriptValue(val);
}

QScriptValue ScriptAPI::funcSin(QScriptContext *cont, QScriptEngine *){
    if(cont->argumentCount()==0){
        cont->throwError("Have not argument.");
        return QScriptValue(0);
    }
    QScriptValue arg=cont->argument(0);
    if(!arg.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val=qSin(arg.toNumber());
    return QScriptValue(val);
}

QScriptValue ScriptAPI::funcCos(QScriptContext *cont, QScriptEngine *){
    if(cont->argumentCount()==0){
        cont->throwError("Have not argument.");
        return QScriptValue(0);
    }
    QScriptValue arg=cont->argument(0);
    if(!arg.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val=qCos(arg.toNumber());
    return QScriptValue(val);
}

QScriptValue ScriptAPI::funcTg(QScriptContext *cont, QScriptEngine *){
    if(cont->argumentCount()==0){
        cont->throwError("Have not argument.");
        return QScriptValue(0);
    }
    QScriptValue arg=cont->argument(0);
    if(!arg.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val=qTan(arg.toNumber());
    return QScriptValue(val);
}

QScriptValue ScriptAPI::funcCtg(QScriptContext *cont, QScriptEngine *){
    if(cont->argumentCount()==0){
        cont->throwError("Have not argument.");
        return QScriptValue(0);
    }
    QScriptValue arg=cont->argument(0);
    if(!arg.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val=1/qTan(arg.toNumber());
    return QScriptValue(val);
}

QScriptValue ScriptAPI::funcPow(QScriptContext *cont, QScriptEngine *){
    if(cont->argumentCount()<2){
        cont->throwError("Must be two arguments.");
        return QScriptValue(0);
    }

    QScriptValue arg1=cont->argument(0);
    if(!arg1.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val1=arg1.toNumber();

    QScriptValue arg2=cont->argument(1);
    if(!arg1.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val2=arg2.toNumber();

    qsreal val=qPow(val1,val2);

    return QScriptValue(val);
}

QScriptValue ScriptAPI::funcLn(QScriptContext *cont, QScriptEngine *){
    if(cont->argumentCount()==0){
        cont->throwError("Have not argument.");
        return QScriptValue(0);
    }
    QScriptValue arg=cont->argument(0);
    if(!arg.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val=arg.toNumber();
    if(val<0){
        cont->throwError(QScriptContext::RangeError,"Argument must be >=0.");
        return QScriptValue(0);
    }
    return QScriptValue(qLn(val));
}

QScriptValue ScriptAPI::funcLog(QScriptContext *cont, QScriptEngine *){
    if(cont->argumentCount()<2){
        cont->throwError("Must be two arguments.");
        return QScriptValue(0);
    }

    QScriptValue arg1=cont->argument(0);
    if(!arg1.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val1=arg1.toNumber();

    QScriptValue arg2=cont->argument(1);
    if(!arg1.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val2=arg2.toNumber();

    if(val1<=0){
        cont->throwError(QScriptContext::RangeError,"Base must be >0");
        return QScriptValue(0);
    }

    if(val2<0){
        cont->throwError(QScriptContext::RangeError,"Value must be >0");
        return QScriptValue(0);
    }

    if(val1==1){
        cont->throwError(QScriptContext::RangeError,"Base can't be =1");
        return QScriptValue(0);
    }

    qsreal val=qLn(val2)/qLn(val1);

    return QScriptValue(val);
}

QScriptValue ScriptAPI::funcExp(QScriptContext *cont, QScriptEngine *){
    if(cont->argumentCount()==0){
        cont->throwError("Have not argument.");
        return QScriptValue(0);
    }
    QScriptValue arg=cont->argument(0);
    if(!arg.isNumber()){
        cont->throwError(QScriptContext::RangeError,"Must be a number.");
        return QScriptValue(0);
    }
    qsreal val=qExp(arg.toNumber());
    return QScriptValue(val);
}

QScriptValue ScriptAPI::funcStrip(QScriptContext *cont, QScriptEngine *){
    int count=cont->argumentCount();
    if(count==0){
        cont->throwError("Have not argument.");
        return QScriptValue(0);
    }
    QList<qsreal> vals;
    for(int i=0;i<((count>3)?3:count);i++){
        QScriptValue val=cont->argument(i);
        if(!val.isNumber()){
            cont->throwError(QScriptContext::RangeError,"Must be a number.");
            return QScriptValue(0);
        }
        vals.append(val.toNumber());
    }
    qsreal arg1=vals.at(0);
    qsreal arg2=0;
    qsreal arg3=255;
    if(count>=3){
        arg2=vals.at(1);
        arg3=vals.at(2);
    }
    if(arg2==arg3){
        cont->throwError(QScriptContext::RangeError,"Second and third arguments is not different.");
        return QScriptValue(0);
    }
    qsreal val=(arg1-arg2)*255/(arg3-arg2);
    if(val<0)val=0;
    if(val>255)val=255;
    return val;
}

void ScriptAPI::installAPI(QScriptEngine &engine){
    // Functions
    engine.globalObject().setProperty("sqrt",engine.newFunction(funcSqrt));
    engine.globalObject().setProperty("sin",engine.newFunction(funcSin));
    engine.globalObject().setProperty("cos",engine.newFunction(funcCos));
    engine.globalObject().setProperty("tg",engine.newFunction(funcTg));
    engine.globalObject().setProperty("ctg",engine.newFunction(funcCtg));
    engine.globalObject().setProperty("pow",engine.newFunction(funcPow));
    engine.globalObject().setProperty("ln",engine.newFunction(funcLn));
    engine.globalObject().setProperty("log",engine.newFunction(funcLog));
    engine.globalObject().setProperty("exp",engine.newFunction(funcExp));
    engine.globalObject().setProperty("strip",engine.newFunction(funcStrip));
    // Constants
    engine.globalObject().setProperty("pi",QScriptValue(M_PI));
    engine.globalObject().setProperty("e",QScriptValue(M_E));
}
