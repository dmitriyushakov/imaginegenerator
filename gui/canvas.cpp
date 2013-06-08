#include <QPainter>

#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent)
{
    img=0;
}

void Canvas::setImage(QImage *image){
    delete img;
    img=image;
    update();
}

void Canvas::paintEvent(QPaintEvent *){
    QPainter p(this);

    p.fillRect(0,0,width(),height(),QColor(255,255,255));

    if(img)p.drawImage(0,0,*img);
}
