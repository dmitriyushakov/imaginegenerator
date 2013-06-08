#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT
private:
    QImage *img;
public:
    explicit About(QWidget *parent = 0);
    ~About();
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void aboutQt();
private:
    Ui::About *ui;
};

#endif // ABOUT_H
