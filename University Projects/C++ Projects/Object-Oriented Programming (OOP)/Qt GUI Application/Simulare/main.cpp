#include "GUI.h"
#include "Teste.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Teste::runFilterBrandTest();

    GUI w;
    w.show();
    return a.exec();
}
