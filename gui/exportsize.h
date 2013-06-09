#ifndef EXPORTSIZE_H
#define EXPORTSIZE_H

#include <QDialog>
#include <QList>
#include <QSize>

namespace Ui {
class ExportSize;
}

class ExportSize : public QDialog
{
    Q_OBJECT
    
public:
    explicit ExportSize(QWidget *parent = 0);
    ~ExportSize();
private slots:
    void okClicked();
    void onSelectResol();
    void onOtherSize();
    void onReverseClick();
signals:
    void sizeChoiced(int w,int h);
private:
    QList<QSize> sizes;
    bool lockOtherSize;
    Ui::ExportSize *ui;
};

#endif // EXPORTSIZE_H
