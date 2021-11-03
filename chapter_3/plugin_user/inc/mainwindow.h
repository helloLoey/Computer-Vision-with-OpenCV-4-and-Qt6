#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QPluginLoader>
#include <QFileInfoList>
#include <opencv2/opencv.hpp>
#include "cvplugininterface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *t_parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    const QString FILTERS_SUBFOLDER = "/filter_plugins/";

    void getPluginsList();
    void setupUi();
    void initializationOfConnection();

private slots:
    void pushButton_input_clicked();
    void pushButton_help_clicked();
    void pushButton_filter_clicked();
};

#endif // MAINWINDOW_H
