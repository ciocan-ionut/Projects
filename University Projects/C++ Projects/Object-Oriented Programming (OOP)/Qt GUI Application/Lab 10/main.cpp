#include <QtWidgets/QApplication>
#include "Teste.h"
#include "GUI.h"
#include "Service.h"
#include "CosActivitati.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Teste::runTests();
    Repository repo;
	CosActivitati cos;
    Service service{ repo, cos };

    GUI gui{ service };
    gui.show();

    return a.exec();
}
