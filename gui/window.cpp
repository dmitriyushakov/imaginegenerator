#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QCloseEvent>

#include "window.h"
#include "storage/projectstorage.h"
#include "exportsize.h"
#include "about.h"
#include "ui_layersettings.h"

Window::Window(QWidget *parent) :
    QWidget(parent)
{
    setWindowIcon(QIcon(":/icon.png"));
    edited=false;
    canv=new Canvas(this);
    control=new LayerSettings(this);
    hlay=new QHBoxLayout();
    hlay->addWidget(canv);
    hlay->addWidget(control);
    canv->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(control,SIGNAL(renderClicked()),this,SLOT(toRender()));
    connect(control,SIGNAL(projectChanged()),this,SLOT(projectEdited()));
    setMinimumWidth(800);
    hlay->setMargin(0);
    setTitle();
    rthread=new RenderThread(this);
    connect(rthread,SIGNAL(finished()),this,SLOT(threadFinished()),Qt::QueuedConnection);
    connect(rthread,SIGNAL(rendered(QImage*)),this,SLOT(rendered(QImage*)),Qt::QueuedConnection);

    vlay=new QVBoxLayout(this);
    vlay->setMargin(0);
    vlay->setSpacing(0);

    //Menu

    mainmenu=new QMenuBar(this);
    QMenu *filemenu=mainmenu->addMenu(tr("File"));
    QAction *openAct=filemenu->addAction(tr("Open"));
    QAction *saveAct=filemenu->addAction(tr("Save"));
    QAction *saveAsAct=filemenu->addAction(tr("Save as"));
    filemenu->addSeparator();
    QAction *exportAct=filemenu->addAction(tr("Export"));
    filemenu->addSeparator();
    QAction *exitAct=filemenu->addAction(tr("Exit"));
    QMenu *help=mainmenu->addMenu(tr("Help"));
    QAction *aboutAct=help->addAction(tr("About"));

    connect(openAct,SIGNAL(triggered()),this,SLOT(open()));
    connect(saveAct,SIGNAL(triggered()),this,SLOT(save()));
    connect(saveAsAct,SIGNAL(triggered()),this,SLOT(saveAs()));
    connect(exportAct,SIGNAL(triggered()),this,SLOT(askExportSize()));
    connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(showAbout()));

    vlay->addWidget(mainmenu);
    vlay->addLayout(hlay);
}

void Window::showAbout(){
    About *about=new About();
    about->setAttribute(Qt::WA_DeleteOnClose);
    about->show();
}

void Window::askExportSize(){
    ExportSize *window=new ExportSize();
    connect(window,SIGNAL(sizeChoiced(int,int)),this,SLOT(exportImage(int,int)));
    window->show();
}

void Window::exportImage(int w, int h){
    exportSize=QSize(w,h);
    QFileDialog *saveDialog=new QFileDialog(this);
    saveDialog->setWindowTitle(tr("Save file"));
    saveDialog->setAcceptMode(QFileDialog::AcceptSave);
    QStringList nameFilters;
    nameFilters<<"Portable Network Graphics (*.png)"
               <<"Windows Bitmap (*.bmp)"
               <<"Joint Photographic Experts Group (*jpg *jpeg)";
    char* formats[]={"PNG","BMP","JPEG"};
    QStringList extensions;
    extensions<<"png"<<"bmp"<<"jpg";
    saveDialog->setNameFilters(nameFilters);
    saveDialog->exec();
    if(!saveDialog->result())return;
    int filterIndex=nameFilters.indexOf(saveDialog->selectedNameFilter());
    saveDialog->setDefaultSuffix(extensions.at(filterIndex));
    exportFile=saveDialog->selectedFiles().at(0);
    exportFormat=formats[filterIndex];

    waitDialog=new RenderWaitDialog();
    connect(rthread,SIGNAL(progress(int)),waitDialog,SLOT(progress(int)));
    connect(waitDialog,SIGNAL(stopClicked()),rthread,SLOT(stopRendering()));
    waitDialog->show();

    Layer lay=control->getProjLayout();
    rthread->startRendering(lay,exportSize.width(),exportSize.height());
}

bool Window::saveAs(){
    QString path;
    if(workFile.isEmpty()){
        path=QDir::homePath();
    }else{
        path=workFile;
    }
    QString sfname=QFileDialog::getSaveFileName(this,tr("Save file"),path,tr("Imagine Generator project (*.igp)"));
    if(sfname.isEmpty())return false;
    if(QFileInfo(sfname).suffix()=="")sfname=sfname+".igp";
    Layer lay=control->getProjLayout();
    StorageError result=ProjectStorage::saveLayout(lay,sfname);
    if(result.isError()){
        QMessageBox mb;
        mb.setIcon(QMessageBox::Critical);
        mb.setWindowTitle(tr("Save file error"));
        mb.setText(result.message());
        mb.exec();
        return false;
    }else{
        edited=false;
        workFile=sfname;
        setTitle(workFile);
        return true;
    }
}

void Window::open(){
    if(!saveEdited())return;
    QString path;
    if(workFile.isEmpty()){
        path=QDir::homePath();
    }else{
        path=workFile;
    }
    QString ofname=QFileDialog::getOpenFileName(this,tr("Open file"),path,tr("Imagine Generator project (*.igp)"));
    if(ofname.isEmpty())return;
    Layer lay;
    StorageError result=ProjectStorage::resoreLayout(lay,ofname);
    if(result.isError()){
        QMessageBox mb;
        if(result.state()==StorageError::Warning){
            mb.setIcon(QMessageBox::Warning);
            mb.setWindowTitle(tr("Warning"));
        }else{
            mb.setIcon(QMessageBox::Critical);
            mb.setWindowTitle(tr("Open file error"));
        }
        mb.setText(result.message());
        mb.exec();
    }else{
        workFile=ofname;
        control->setProjLayout(lay);
        edited=false;
        setTitle(ofname);
    }
}

void Window::open(QString filename){
    if(filename.isEmpty())return;
    Layer lay;
    StorageError result=ProjectStorage::resoreLayout(lay,filename);
    if(result.isError()){
        QMessageBox mb;
        if(result.state()==StorageError::Warning){
            mb.setIcon(QMessageBox::Warning);
            mb.setWindowTitle(tr("Warning"));
        }else{
            mb.setIcon(QMessageBox::Critical);
            mb.setWindowTitle(tr("Open file error"));
        }
        mb.setText(result.message());
        mb.exec();
    }else{
        workFile=filename;
        control->setProjLayout(lay);
        edited=false;
        setTitle(filename);
    }
}

bool Window::save(){
    if(workFile.isEmpty()){
        return saveAs();
    }else{
        Layer lay=control->getProjLayout();
        StorageError result=ProjectStorage::saveLayout(lay,workFile);
        if(result.isError()){
            QMessageBox mb;
            mb.setIcon(QMessageBox::Critical);
            mb.setWindowTitle(tr("Save file error"));
            mb.setText(result.message());
            mb.exec();
            return false;
        }else{
            edited=false;
            setTitle(workFile,false);
            return true;
        }
    }
}

void Window::toRender(){
    waitDialog=new RenderWaitDialog();
    connect(rthread,SIGNAL(progress(int)),waitDialog,SLOT(progress(int)));
    connect(waitDialog,SIGNAL(stopClicked()),rthread,SLOT(stopRendering()));
    waitDialog->show();
    control->ui->renderBtn->setEnabled(false);

    Layer lay=control->getProjLayout();
    rthread->startRendering(lay,canv->width(),canv->height());
}

void Window::rendered(QImage *img){
    if(img){
        if(exportFile.isEmpty()){
            canv->setImage(img);
        }else{
            img->save(exportFile,exportFormat,100);
            exportFile.clear();
        }
    }
}

void Window::threadFinished(){
    control->ui->renderBtn->setEnabled(true);
    if(rthread->hasError()){
        QMessageBox mb;
        mb.setIcon(QMessageBox::Warning);
        mb.setText(rthread->errorMessage());
        mb.setWindowTitle(tr("Script exception"));
        mb.exec();
    }
    if(waitDialog){
        waitDialog->close();
        delete waitDialog;
        waitDialog=0;
    }
}

void Window::setTitle(QString filename, bool isEdited){
    QString result;
    if(filename.isEmpty()){
        result="Imagine Generator";
    }else{
        result=filename.append(" - Imagine Generator");
    }
    if(isEdited)result=result.prepend("*");
    setWindowTitle(result);
}

void Window::projectEdited(){
    if(!edited){
        setTitle(workFile,true);
    }
    edited=true;
}

bool Window::saveEdited(){
    if(!edited)return true;
    QMessageBox mb;
    mb.setWindowTitle(tr("Save file"));
    mb.setText(tr("You want to save file?"));
    mb.setIcon(QMessageBox::Question);
    mb.setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    int clicked=mb.exec();
    if(clicked==QMessageBox::Yes){
        return save();
    };
    return clicked!=QMessageBox::Cancel;
}

void Window::closeEvent(QCloseEvent *ev){
    if(saveEdited()){
        ev->accept();
    }else{
        ev->ignore();
    }
}
