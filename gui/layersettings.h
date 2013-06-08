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
    QButtonGroup xtypegr;
    QButtonGroup ytypegr;
private slots:
    void colorTypeChanged();
signals:
    void projectChanged();
    void renderClicked();
};

#endif // LAYERSETTINGS_H
