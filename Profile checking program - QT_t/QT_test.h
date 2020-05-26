#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QT_test.h"
#include "controller.h"

class QT_GUI : public QMainWindow
{
    Q_OBJECT

public:
    QT_GUI(Service& s, QWidget *parent = Q_NULLPTR);

private:
    Service& srv;
    Ui::QT_testClass ui;

    void connectSignalsAndSlots();
    void populateList();
    void populateTraitsList();
    int getSelectedIndex() const;
    void filterEnts();
};
