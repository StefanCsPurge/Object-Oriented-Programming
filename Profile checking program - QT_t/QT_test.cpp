#include "QT_test.h"
#include <QMessageBox.h>
using namespace std;

QT_GUI::QT_GUI(Service& s, QWidget *parent)
    : QMainWindow(parent), srv(s)
{
    ui.setupUi(this);

    this->populateList();
    this->connectSignalsAndSlots();
}

void QT_GUI::connectSignalsAndSlots()
{
    QObject::connect(this->ui.entListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0)
            return;
        });
    QObject::connect(this->ui.showButton, &QPushButton::clicked, this, &QT_GUI::populateTraitsList);
    //QObject::connect(this->ui.searchButton, &QPushButton::clicked, this, &QT_GUI::filterEnts);
    QObject::connect(this->ui.lineEdit1, &QLineEdit::textChanged, this, &QT_GUI::filterEnts);
}

void QT_GUI::populateList()
{
    this->ui.entListWidget->clear();
    vector<Person> allEnts = this->srv.getAll();
    for (const Person& e : allEnts)
        this->ui.entListWidget->addItem(QString::fromStdString(e.getBody() + " - " + e.getName()));
}

void QT_GUI::populateTraitsList()
{
    string name = this->ui.lineEdit2->text().toStdString();
    vector<string> traits = this->srv.getEnt(name).getTraits();
    this->ui.traitsListWidget->clear();
    for (auto e : traits)
        this->ui.traitsListWidget->addItem(QString::fromStdString(e));
}

int QT_GUI::getSelectedIndex() const
{
    QModelIndexList selectedIndexes = this->ui.entListWidget->selectionModel()->selectedIndexes();
    if (!selectedIndexes.size())   // in case there is something that is not selected
    {
        //this->ui.lineEdit1->clear();
        //this->ui.lineEdit2->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void QT_GUI::filterEnts()
{
    string catname = this->ui.lineEdit1->text().toStdString();
    vector<Person> selectedEnts = this->srv.filter(catname);
    this->ui.entListWidget->clear();
    for (const Person& e : selectedEnts)
        this->ui.entListWidget->addItem(QString::fromStdString(e.getBody() + " - " + e.getName()));
}



