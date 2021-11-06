#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoprocessor.h"

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
    VideoProcessor *m_video_processor;
};

#endif // MAINWINDOW_H
