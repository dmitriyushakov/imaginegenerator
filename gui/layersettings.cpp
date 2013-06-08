#include "layersettings.h"
#include "ui_layersettings.h"

LayerSettings::LayerSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayoutSettings)
{
    ui->setupUi(this);
    connect(ui->tricolorBtn,SIGNAL(clicked()),this,SLOT(colorTypeChanged()));
    connect(ui->greyBtn,SIGNAL(clicked()),this,SLOT(colorTypeChanged()));
    connect(ui->renderBtn,SIGNAL(clicked()),this,SIGNAL(renderClicked()));
    xtypegr.addButton(ui->xabsolute);
    xtypegr.addButton(ui->xrelate);
    ytypegr.addButton(ui->yabsolute);
    ytypegr.addButton(ui->yrelate);
    setProjLayout(Layer());

    connect(ui->scriptEditor,SIGNAL(modificationChanged(bool)),this,SIGNAL(projectChanged()));
    connect(ui->redVal,SIGNAL(textEdited(QString)),this,SIGNAL(projectChanged()));
    connect(ui->greenVal,SIGNAL(textEdited(QString)),this,SIGNAL(projectChanged()));
    connect(ui->blueVal,SIGNAL(textEdited(QString)),this,SIGNAL(projectChanged()));
    connect(ui->greyVal,SIGNAL(textEdited(QString)),this,SIGNAL(projectChanged()));
    connect(ui->tricolorBtn,SIGNAL(toggled(bool)),this,SIGNAL(projectChanged()));
    connect(ui->greyBtn,SIGNAL(toggled(bool)),this,SIGNAL(projectChanged()));
    connect(ui->xabsolute,SIGNAL(toggled(bool)),this,SIGNAL(projectChanged()));
    connect(ui->xrelate,SIGNAL(toggled(bool)),this,SIGNAL(projectChanged()));
    connect(ui->yabsolute,SIGNAL(toggled(bool)),this,SIGNAL(projectChanged()));
    connect(ui->yrelate,SIGNAL(toggled(bool)),this,SIGNAL(projectChanged()));
}

Layer LayerSettings::getProjLayout(){
    Layer lay;
    lay.setScript(ui->scriptEditor->toPlainText());
    lay.setRComponent(ui->redVal->text());
    lay.setGComponent(ui->greenVal->text());
    lay.setBComponent(ui->blueVal->text());
    lay.setGreyComponent(ui->greyVal->text());
    lay.setColorType((ui->tricolorBtn->isChecked())?Tricolor:GreyColor);
    lay.setXPointType((ui->xabsolute->isChecked())?Absolute:Related);
    lay.setYPointType((ui->yabsolute->isChecked())?Absolute:Related);
    return lay;
}

void LayerSettings::setProjLayout(Layer lay){
    ui->scriptEditor->setPlainText(lay.getScript());
    ui->redVal->setText(lay.getRComponent());
    ui->greenVal->setText(lay.getGComponent());
    ui->blueVal->setText(lay.getBComponent());
    ui->greyVal->setText(lay.getGreyComponent());

    if(lay.getColorType()==Tricolor){
        ui->tricolorBtn->setChecked(true);
    }else{
        ui->greyBtn->setChecked(true);
    }

    if(lay.getXPointType()==Absolute){
        ui->xabsolute->setChecked(true);
    }else{
        ui->xrelate->setChecked(true);
    }

    if(lay.getYPointType()==Absolute){
        ui->yabsolute->setChecked(true);
    }else{
        ui->yrelate->setChecked(true);
    }

    colorTypeChanged();
}

void LayerSettings::colorTypeChanged(){
    if(ui->tricolorBtn->isChecked()){
        ui->redVal->setEnabled(true);
        ui->greenVal->setEnabled(true);
        ui->blueVal->setEnabled(true);
        ui->greyVal->setEnabled(false);
    }else{
        ui->redVal->setEnabled(false);
        ui->greenVal->setEnabled(false);
        ui->blueVal->setEnabled(false);
        ui->greyVal->setEnabled(true);
    }
}

LayerSettings::~LayerSettings()
{
    delete ui;
}
