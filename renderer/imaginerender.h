#ifndef IMAGINERENDER_H
#define IMAGINERENDER_H

#include "model/layer.h"
#include "colorcalculator.h"

class ImagineRender:public QObject
{
    Q_OBJECT
private:
    ColorCalculator *color;
    ImagineRender();
    int lprogr;
    bool _stop;
    bool toStop();
    bool hasAlpha;
    System coordSys;
public:
    void stop();
    bool hasError();
    QString errorMessage();
    ImagineRender(Layer &lay);
    ~ImagineRender();
    QImage *render(int width,int height);
signals:
    void progress(int percents);
};

#endif // IMAGINERENDER_H
