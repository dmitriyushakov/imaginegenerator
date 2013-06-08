#ifndef SCRIPTAPI_H
#define SCRIPTAPI_H

#include <QScriptValue>

class QScriptContext;

class ScriptAPI
{
private:
    static QScriptValue funcSqrt(QScriptContext *cont,QScriptEngine *);
    static QScriptValue funcSin(QScriptContext *cont, QScriptEngine *);
    static QScriptValue funcCos(QScriptContext *cont,QScriptEngine *);
    static QScriptValue funcTg(QScriptContext *cont, QScriptEngine *);
    static QScriptValue funcCtg(QScriptContext *cont,QScriptEngine *);
    static QScriptValue funcPow(QScriptContext *cont,QScriptEngine *);
    static QScriptValue funcLn(QScriptContext *cont,QScriptEngine *);
    static QScriptValue funcLog(QScriptContext *cont,QScriptEngine *);
    static QScriptValue funcExp(QScriptContext *cont,QScriptEngine *);
    static QScriptValue funcStrip(QScriptContext *cons,QScriptEngine *);
public:
    static void installAPI(QScriptEngine &engine);
};

#endif // SCRIPTAPI_H
