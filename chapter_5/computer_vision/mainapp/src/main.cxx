#include <QApplication>
#include <memory>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");
    std::unique_ptr<MainWindow> mainwindow(new MainWindow);
    mainwindow.get()->showMaximized();
    return app.exec();
}
