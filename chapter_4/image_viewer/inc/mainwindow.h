#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void dragEnterEvent(QDragEnterEvent *t_event);
    void dropEvent(QDropEvent *t_event);
    void resizeEvent(QResizeEvent *t_event);

private:
    Ui::MainWindow *ui;
    QPixmap m_pixmap;
};

#endif // MAINWINDOW_H
