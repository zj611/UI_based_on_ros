#include <QtGui>
#include <QApplication>
#include "../include/msg/main_window.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    msg::MainWindow w(argc,argv);
    w.show();
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    return app.exec();
}
