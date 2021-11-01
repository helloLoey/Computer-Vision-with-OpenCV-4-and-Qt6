#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *t_parent) :
    QMainWindow(t_parent),
    ui(new Ui::MainWindow)
{
    setupUi();
    initializationOfConnection();
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *t_event)
{
    int result = QMessageBox::warning(this, tr("Exit"), tr("Are you sure you want to close this program?"), QMessageBox::Yes, QMessageBox::No);
        if (result == QMessageBox::Yes)
        {
            saveSettings();
            t_event->accept();
        }
        else
            t_event->ignore();
}

void MainWindow::setupUi()
{
    ui->setupUi(this);
    ui->radioButton_type_median->setChecked(true);
}

void MainWindow::initializationOfConnection()
{
    connect(ui->pushButton_input_browse, &QPushButton::clicked, this, &MainWindow::pushButton_input_browse_clicked);
    connect(ui->pushButton_output_browse, &QPushButton::clicked, this, &MainWindow::pushButton_output_browse_clicked);
}

void MainWindow::loadSettings()
{
    QSettings settings("packt", "hello_qt_opencv", this);
    ui->lineEdit_input->setText(settings.value("lineEdit_input", "").toString());
    ui->lineEdit_output->setText(settings.value("lineEdit_output", "").toString());
    ui->radioButton_type_median->setChecked(settings.value("radioButton_type_median", true).toBool());
    ui->radioButton_type_gaussian->setChecked(settings.value("radioButton_type_gaussian", false).toBool());
    ui->checkBox_display_image->setChecked(settings.value("checkBox_display_image", false).toBool());
}

void MainWindow::saveSettings()
{
    QSettings settings("packt", "hello_qt_opencv", this);
    settings.setValue("lineEdit_input", ui->lineEdit_input->text());
    settings.setValue("lineEdit_output", ui->lineEdit_output->text());
    settings.setValue("radioButton_type_median", ui->radioButton_type_median->isChecked());
    settings.setValue("radioButton_type_gaussian", ui->radioButton_type_gaussian->isChecked());
    settings.setValue("checkBox_display_image", ui->checkBox_display_image->isChecked());
}

cv::Mat MainWindow::filterImage(const cv::Mat &t_source)
{
    cv::Mat filtered;
    if (ui->radioButton_type_median->isChecked())
        cv::medianBlur(t_source, filtered, 7);
    else if (ui->radioButton_type_gaussian->isChecked())
        cv::GaussianBlur(t_source, filtered, cv::Size(5, 5), 3, 3);
    return filtered;
}

void MainWindow::pushButton_input_browse_clicked()
{
    const QString caption = tr("Open Input Image");
    const QString filter = tr("Images (*.jpg *.png *.bmp)");
    QString filename = QFileDialog::getOpenFileName(this, caption, QDir::homePath(), filter);
    if (QFile::exists(filename))
        ui->lineEdit_input->setText(filename);
}

void MainWindow::pushButton_output_browse_clicked()
{
    const QString caption = tr("Select Output Image");
    const QString filter = tr("*.jpg;;*.png;;*.bmp");
    QString filename = QFileDialog::getSaveFileName(this, caption, QDir::currentPath(), filter);
    if(!filename.isEmpty())
    {
        ui->lineEdit_output->setText(filename);
        cv::Mat input_image = cv::imread(ui->lineEdit_input->text().toStdString());
        cv::Mat output_image = filterImage(input_image);
        cv::imwrite(filename.toStdString(), output_image);
        if(ui->checkBox_display_image->isChecked())
            cv::imshow("Output Image", output_image);
    }
}
