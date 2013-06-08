#ifndef EXPORTSIZE_H
#define EXPORTSIZE_H

#include <QDialog>

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
signals:
    void sizeChoiced(int w,int h);
private:
    Ui::ExportSize *ui;
};

#endif // EXPORTSIZE_H
