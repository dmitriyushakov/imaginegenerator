#ifndef LAYER_H
#define LAYER_H

#include <QString>

#include "pointtype.h"
#include "componenttype.h"
#include "system.h"

enum ColorType{
    Tricolor,
    GreyColor
};

class Layer
{
    QString script;
    QString rcomponent;
    QString gcomponent;
    QString bcomponent;
    QString acomponent;
    QString greycomponent;
    PointType xtype;
    PointType ytype;
    ColorType colortype;
    System system;
public:
    Layer();
    QString getScript();
    QString getRComponent();
    QString getGComponent();
    QString getBComponent();
    QString getAComponent();
    QString getGreyComponent();
    QString getComponent(ComponentType component);
    PointType getXPointType();
    PointType getYPointType();
    ColorType getColorType();
    bool alphaIsSet();
    System getSystem();
    void setScript(QString script);
    void setRComponent(QString expr);
    void setGComponent(QString expr);
    void setBComponent(QString expr);
    void setAComponent(QString expr);
    void setGreyComponent(QString expr);
    void setComponent(ComponentType component,QString exp);
    void setXPointType(PointType type);
    void setYPointType(PointType type);
    void setColorType(ColorType type);
    void setSystem(System s);
};

#endif // LAYER_H
