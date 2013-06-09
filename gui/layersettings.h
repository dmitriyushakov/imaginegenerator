#ifndef LAYERSETTINGS_H
#define LAYERSETTINGS_H

#include <QWidget>
#include <QButtonGroup>

#include "model/layer.h"

namespace Ui {
class LayoutSettings;
}

class LayerSettings : public QWidget
{
    Q_OBJECT
    
public:
    explicit LayerSettings(QWidget *parent = 0);
    ~LayerSettings();
    Layer getProjLayout();
    void setProjLayout(Layer lay);
    Ui::LayoutSettings *ui;
private:
    void showSystemInfo(System &s);
    System system;
    QButtonGroup xtypegr;
    QButtonGroup ytypegr;
private slots:
    void colorTypeChanged();
    void changeSystem();
    void enableChangeSystem();
    void systemChanged(System sys);
signals:
    void projectChanged();
    void renderClicked();
};

#endif // LAYERSETTINGS_H
