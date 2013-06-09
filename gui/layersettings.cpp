#include "layersettings.h"
#include "ui_layersettings.h"
#include "systemchooser.h"

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
    connect(ui->systemBtn,SIGNAL(clicked()),this,SLOT(changeSystem()));
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
    lay.setSystem(system);
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

    system=lay.getSystem();
    showSystemInfo(system);

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

void LayerSettings::showSystemInfo(System &s){
    QString str;
    str+=(s.type()==System::Rectangle)?tr("Rectangle"):tr("Radial");
    str+="; ";

    QStringList yPosStrs;
    yPosStrs.append(tr("Up"));
    yPosStrs.append(tr("Middle"));
    yPosStrs.append(tr("Down"));

    QStringList xPosStrs;
    xPosStrs.append(tr("Left"));
    xPosStrs.append(tr("Middle"));
    xPosStrs.append(tr("Right"));

    QString str1=xPosStrs.at(s.xPos());
    QString str2=yPosStrs.at(s.yPos());

    if(str1==str2){
        str+=str1;
    }else{
        str+=str2+"-"+str1;
    }

    str+="; ";

    str+=(s.yOrientation()==System::ToDown)?tr("To down"):tr("To up");
    ui->pointerGroup->setEnabled(system.type()==System::Rectangle);
    ui->systemLbl->setText(str);
}

void LayerSettings::changeSystem(){
    ui->systemBtn->setEnabled(false);

    SystemChooser *chooser=new SystemChooser();
    chooser->setAttribute(Qt::WA_DeleteOnClose,true);
    chooser->init(system);
    connect(chooser,SIGNAL(destroyed()),this,SLOT(enableChangeSystem()));
    connect(chooser,SIGNAL(systemSelected(System)),this,SLOT(systemChanged(System)));
    chooser->show();
}

void LayerSettings::enableChangeSystem(){
    ui->systemBtn->setEnabled(true);
}

void LayerSettings::systemChanged(System sys){
    system=sys;
    emit projectChanged();
    showSystemInfo(system);
}
