#include "QT_test.h"
#include <QtWidgets/QApplication>
#include "controller.h"
#include <qmessagebox.h>
#include <cassert>

// tests for the function which searches for profiles by category or name
void testFilter()
{
    Service srv("ents2.txt"); 
    auto v = srv.filter("Heavy");
    assert(v.size() == 2);
    v = srv.filter("LMAO");
    assert(v.size() == 0);
    v = srv.filter("Simion");
    assert(v.size() == 1);
    assert(v[0] == Person("Moroc Simion"));
}


int main(int argc, char *argv[])
{
    testFilter();
    QApplication a(argc, argv);
    Service service("ents.txt");
    QT_GUI w(service);
    w.show();
    return a.exec();
}
