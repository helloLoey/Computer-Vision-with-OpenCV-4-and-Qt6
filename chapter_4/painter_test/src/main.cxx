#include <QApplication>
#include <memory>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::unique_ptr<MainWindow> mainwindow(new MainWindow);
    mainwindow.get()->show();
    return a.exec();
}
