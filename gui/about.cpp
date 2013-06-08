#include <QPainter>
#include <QImage>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>

#include "about.h"
#include "ui_about.h"
#include "version.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    img=new QImage(":/logo.png");
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint);
    connect(ui->closeBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->aboutQtBtn,SIGNAL(clicked()),this,SLOT(aboutQt()));
    ui->versionLbl->setText(ui->versionLbl->text().append(VERSION));
    ui->licenseLbl->setText(ui->licenseLbl->text().append("GPLv2"));
}

void About::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawImage(0,0,*img);
}

void About::aboutQt(){
    QMessageBox::aboutQt(this,tr("About Qt"));
}

About::~About()
{
    delete img;
    delete ui;
}
