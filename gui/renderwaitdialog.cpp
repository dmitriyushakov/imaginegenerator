#include <QProgressBar>
#include <QPushButton>

#include "renderwaitdialog.h"
#include "ui_renderwaitdialog.h"

#include <QDebug>

RenderWaitDialog::RenderWaitDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderWaitDialog)
{
    ui->setupUi(this);
    connect(ui->stopBtn,SIGNAL(clicked()),this,SLOT(close()));
    setWindowFlags(Qt::Dialog);
}

RenderWaitDialog::~RenderWaitDialog()
{
    delete ui;
}

void RenderWaitDialog::progress(int percents){
    if(percents>100)percents=100;
    if(percents<0)percents=0;
    ui->progressBar->setValue(percents);
}

void RenderWaitDialog::closeEvent(QCloseEvent *){
    emit stopClicked();
}
