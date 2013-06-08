#include <QSpinBox>
#include <QDialogButtonBox>

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
}

ExportSize::~ExportSize()
{
    delete ui;
}

void ExportSize::okClicked(){
    emit sizeChoiced(ui->widthSpin->value(),ui->heightSpin->value());
    close();
}
