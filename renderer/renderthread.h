#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QThread>

#include "imaginerender.h"

class RenderThread : public QThread
{
    Q_OBJECT
private:
    ImagineRender *renderer;
    Layer layout;
    int w;
    int h;
    RenderThread();
    bool _haserror;
    QString _errormsg;
public:
    explicit RenderThread(QObject *parent = 0);
    void startRendering(Layer &lay,int width,int height);
    bool hasError();
    QString errorMessage();
    ~RenderThread();
protected:
    void run();
signals:
    void progress(int percents);
    void rendered(QImage* img);
public slots:
    void stopRendering();
};

#endif // RENDERTHREAD_H
