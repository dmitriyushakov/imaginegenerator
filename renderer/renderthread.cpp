#include "renderthread.h"

RenderThread::RenderThread(){}

RenderThread::RenderThread(QObject *parent) :
    QThread(parent)
{
    renderer=0;
    _haserror=false;
}

RenderThread::~RenderThread(){
    delete renderer;
}

void RenderThread::startRendering(Layer &lay, int width, int height){
    if(isRunning())return;
    _haserror=false;
    _errormsg=QString();
    layout=lay;
    w=width;
    h=height;
    start();
}

void RenderThread::run(){
    renderer=new ImagineRender(layout);
    connect(renderer,SIGNAL(progress(int)),this,SIGNAL(progress(int)));
    QImage *img=renderer->render(w,h);
    if(renderer->hasError()){
        _haserror=true;
        _errormsg=renderer->errorMessage();
    }
    if(img)emit rendered(img);
    delete renderer;
    renderer=0;
}

void RenderThread::stopRendering(){
    if(renderer)renderer->stop();
}

bool RenderThread::hasError(){
    return _haserror;
}

QString RenderThread::errorMessage(){
    return _errormsg;
}
