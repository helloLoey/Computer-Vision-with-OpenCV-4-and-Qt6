#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "qcustomgraphicseffect.h"

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

protected:
    void dragEnterEvent(QDragEnterEvent *t_event) override;
    void dropEvent(QDropEvent *t_event) override;

private:
    Ui::MainWindow *ui;
    QGraphicsScene m_scene;
};

#endif // MAINWINDOW_H
