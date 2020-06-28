#include "ExamMVC.h"
#include <qmessagebox.h>
#include <fstream>
#include <qdebug.h>

ExamMVC::ExamMVC(Controller& c, TableModel* m, Astronomer& w,QWidget *parent): QMainWindow(parent), srv(c), model(m), astro(w)
{
    ui.setupUi(this);
    this->ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui.tableView->setModel(model);
    this->ui.tableView->verticalHeader()->hide();
    this->ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->w = new ViewWindow{};
    this->setWindowTitle(QString::fromStdString(astro.getName()));
    this->connectSignalsAndSlots();
}

void ExamMVC::connectSignalsAndSlots()
{
    QObject::connect(this->ui.tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0)
            return;
        //string creator = this->ui.tableView->model()->index(selectedIndex, 2).data().toString().toStdString();
        });
    QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &ExamMVC::addStar);
    QObject::connect(this->ui.checkBox, &QCheckBox::stateChanged, this, &ExamMVC::showMyStars);
    QObject::connect(this->ui.searchLineEdit, &QLineEdit::textChanged, this, &ExamMVC::showResults);
    QObject::connect(this->ui.viewButton, &QPushButton::clicked, this, &ExamMVC::showViewWindow);
}

int ExamMVC::getSelectedIndex() const
{
    QModelIndexList selectedIndexes = this->ui.tableView->selectionModel()->selectedIndexes();
    if (!selectedIndexes.size())   // in case there is something that is not selected
        return -1;
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void ExamMVC::showMyStars()
{
    if (!this->ui.checkBox->isChecked())
    {
        for (int i = 0; i < ui.tableView->model()->rowCount(); i++)
            this->ui.tableView->showRow(i);
        return;
    }
    for (int i = 0; i < ui.tableView->model()->rowCount(); i++)
    {
        if(this->ui.tableView->model()->index(i, 1).data().toString().toStdString() != astro.getConstellation())
            this->ui.tableView->hideRow(i);
    }
}

void ExamMVC::addStar()
{
    string name = this->ui.nameLineEdit->text().toStdString();
    int ra = this->ui.RAlineEdit->text().toInt();
    int Dec = this->ui.decLineEdit->text().toInt();
    int diam = this->ui.diamLineEdit->text().toInt();
    try {
        this->srv.addStar(name,astro.getConstellation(),ra,Dec,diam);
    }
    catch (exception& e)
    {
        QMessageBox::information(this, "Operation failed", e.what());
        return;
    }
}

void ExamMVC::showResults()
{
    string str = this->ui.searchLineEdit->text().toStdString();
    vector<Star> selected = this->srv.filterStars(str);
    this->ui.listWidget->clear();
    for (const Star& e : selected)
        this->ui.listWidget->addItem(QString::fromStdString(e.getName()));
}

void ExamMVC::showViewWindow()
{
    int selectedIndex = this->getSelectedIndex();
    if (selectedIndex < 0)
    {
        QMessageBox::information(this, "Operation failed", "No star selected!");
        return;
    }
    string selectedStar = this->ui.tableView->model()->index(selectedIndex, 0).data().toString().toStdString();
    string currentConstellation = this->ui.tableView->model()->index(selectedIndex, 1).data().toString().toStdString();
    vector<Star> constellationStars = this->srv.getConstellationsStars(currentConstellation);

    this->w->setStars(constellationStars, selectedStar);
    this->w->show();
}
