#include <QSpinBox>
#include <QDialogButtonBox>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "exportsize.h"
#include "ui_exportsize.h"

ExportSize::ExportSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportSize)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(okClicked()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(close()));
    setWindowFlags(Qt::WindowCloseButtonHint|Qt::Dialog);
    setAttribute(Qt::WA_DeleteOnClose);
    setMaximumSize(size());
    setMinimumSize(size());

    int cwidth=ui->widthSpin->value();
    int cheight=ui->heightSpin->value();
    QComboBox *rbox=ui->resolutionsBox;
    rbox->addItem(tr("Other"));

    QFile resolFile(":/resolutions");
    if(resolFile.open(QIODevice::ReadOnly)){
        QTextStream stream(&resolFile);
        QString line;
        while(!(line=stream.readLine()).isNull()){
            QStringList vals=line.split("x");
            int width=vals.at(0).toInt();
            int height=vals.at(1).toInt();
            QSize size(width,height);
            sizes.append(size);
            rbox->addItem(line);

            if(width==cwidth&&height==cheight){
                int pos=rbox->count()-1;
                rbox->setCurrentIndex(pos);
            }
        }
        resolFile.close();
    }else{
        QMessageBox *mb=new QMessageBox();
        mb->setWindowTitle("Imagine Generator");
        mb->setText("Can't read resolutions resource.");
        mb->setIcon(QMessageBox::Critical);
        mb->exec();
        delete mb;
    }

    connect(rbox,SIGNAL(currentIndexChanged(int)),this,SLOT(onSelectResol()));
    connect(ui->widthSpin,SIGNAL(valueChanged(int)),this,SLOT(onOtherSize()));
    connect(ui->heightSpin,SIGNAL(valueChanged(int)),this,SLOT(onOtherSize()));
    lockOtherSize=false;
}

ExportSize::~ExportSize()
{
    delete ui;
}

void ExportSize::okClicked(){
    emit sizeChoiced(ui->widthSpin->value(),ui->heightSpin->value());
    close();
}

void ExportSize::onSelectResol(){
    int index=ui->resolutionsBox->currentIndex();
    if(index!=0){
        QSize size=sizes.at(index-1);
        lockOtherSize=true;
        ui->widthSpin->setValue(size.width());
        ui->heightSpin->setValue(size.height());
        lockOtherSize=false;
    }
}

void ExportSize::onOtherSize(){
    if(!lockOtherSize){
        bool find=false;
        int width=ui->widthSpin->value();
        int height=ui->heightSpin->value();

        int count=sizes.count();
        int i;
        for(i=0;i<count;i++){
            QSize size=sizes.at(i);
            if(size.width()==width&&size.height()==height){
                find=true;
                break;
            }
        }
        if(find){
            ui->resolutionsBox->setCurrentIndex(i+1);
        }else
            ui->resolutionsBox->setCurrentIndex(0);
    }
}
