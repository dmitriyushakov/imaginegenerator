#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT
private:
    QImage *img;
public:
    void setImage(QImage *image);
    explicit Canvas(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CANVAS_H
