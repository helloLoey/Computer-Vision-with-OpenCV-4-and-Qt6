#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <opencv2/opencv.hpp>

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
    void closeEvent(QCloseEvent *t_event) override;
    void changeEvent(QEvent *t_event) override;

private:
    Ui::MainWindow *ui;
    QTranslator *m_russian_translator;

    void setupUi();
    void initializationOfConnection();
    bool initializationOfTranslators();
    void loadSettings();
    void saveSettings();
    cv::Mat filterImage(const cv::Mat& t_source);

private slots:
    void pushButton_input_browse_clicked();
    void pushButton_output_browse_clicked();
    void actionRussian_triggered();
    void actionEnglish_triggered();
};

#endif // MAINWINDOW_H
