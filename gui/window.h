#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QMenuBar>

#include "layersettings.h"
#include "canvas.h"
#include "renderer/imaginerender.h"
#include "renderer/renderthread.h"
#include "renderwaitdialog.h"

class Window : public QWidget
{
    Q_OBJECT
private:
    Canvas *canv;
    LayerSettings *control;
    QHBoxLayout *hlay;
    QVBoxLayout *vlay;
    QMenuBar *mainmenu;
    RenderThread *rthread;
    RenderWaitDialog *waitDialog;
    void setTitle(QString filename=QString(),bool isEdited=false);
    QString workFile;
    bool edited;
    QString exportFile;
    char *exportFormat;
    QSize exportSize;
private slots:
    void showAbout();
    void askExportSize();
    void exportImage(int w,int h);
    bool saveAs();
    void open();
    bool save();
    void rendered(QImage *img);
    void threadFinished();
    void projectEdited();
    void toRender();
protected:
    void closeEvent(QCloseEvent *ev);
public:
    bool saveEdited();
    void open(QString filename);
    explicit Window(QWidget *parent = 0);
};

#endif // WINDOW_H
