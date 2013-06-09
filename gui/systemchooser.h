#ifndef SYSTEMCHOOSER_H
#define SYSTEMCHOOSER_H

#include "model/system.h"

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class SystemChooser;
}

class SystemChooser : public QWidget
{
    Q_OBJECT
    
public:
    void init(System system);
    explicit SystemChooser(QWidget *parent = 0);
    ~SystemChooser();
signals:
    void systemSelected(System system);
private slots:
    void okClicked();
    void onChangeType();
private:
    QButtonGroup typeGroup;
    Ui::SystemChooser *ui;
};

#endif // SYSTEMCHOOSER_H
