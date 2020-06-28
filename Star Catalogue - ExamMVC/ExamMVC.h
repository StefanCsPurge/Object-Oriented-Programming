#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ExamMVC.h"
#include "TableModel.h"
#include "Controller.h"
#include "ViewWindow.h"

class ExamMVC : public QMainWindow
{
    Q_OBJECT

public:
    ExamMVC(Controller& c, TableModel* m, Astronomer& w, QWidget *parent = Q_NULLPTR);

private:
    Ui::ExamMVCClass ui;
    TableModel* model;
    Controller& srv;
    Astronomer astro;
    ViewWindow* w;

    void connectSignalsAndSlots();
    int getSelectedIndex() const;

    void showMyStars();
    void addStar();
    void showResults();
    void showViewWindow();

};
