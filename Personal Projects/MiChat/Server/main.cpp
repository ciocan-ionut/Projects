#include <QtCore/QCoreApplication>

#include "MiServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    MiServer server;

    return app.exec();
}
