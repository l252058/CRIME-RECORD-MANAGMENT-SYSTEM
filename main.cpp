#include <QApplication>
#include "Interface1.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LandingPage window;
    window.showMaximized();

    return app.exec();
}