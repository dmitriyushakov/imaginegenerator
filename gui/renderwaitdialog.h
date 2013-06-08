#ifndef RENDERWAITDIALOG_H
#define RENDERWAITDIALOG_H

#include <QWidget>

namespace Ui {
class RenderWaitDialog;
}

class RenderWaitDialog : public QWidget
{
    Q_OBJECT
public:
    explicit RenderWaitDialog(QWidget *parent = 0);
    ~RenderWaitDialog();
public slots:
    void progress(int percents);
protected:
    void closeEvent(QCloseEvent *);
signals:
    void stopClicked();
private:
    Ui::RenderWaitDialog *ui;
};

#endif // RENDERWAITDIALOG_H
