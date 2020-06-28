#include "ExamMVC.h"
#include "Repository.h"
#include "Controller.h"
#include "TableModel.h"
#include <QtWidgets/QApplication>

void testAddStar()
{
    Repository r;
    TableModel* m = new TableModel{ r };
    Controller c(r, m);
    r.addStar(Star("s1", "c1", 1, 1, 1));
    assert(r.getStars().size() == 1);
    c.addStar("s2", "c2", 2, 2, 2);
    assert(r.getStars().size() == 2);
    assert(r.getStars()[1].getConstellation() == "c2");
}

int main(int argc, char *argv[])
{
    testAddStar();
    QApplication a(argc, argv);
    Repository repo("astron.txt", "stars.txt");
    TableModel* model = new TableModel{ repo };
    Controller srv(repo, model);

    vector<ExamMVC*> windows;
    for (auto astro : repo.getAstronomers())
        windows.push_back(new ExamMVC(srv, model, astro));

    for(auto w : windows)
        w->show();
    return a.exec();
}
