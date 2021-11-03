#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *t_parent) :
    QMainWindow(t_parent),
    ui(new Ui::MainWindow)
{
    setupUi();
    getPluginsList();
    initializationOfConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getPluginsList()
{
    QDir filters_dir(qApp->applicationDirPath() + FILTERS_SUBFOLDER);
    QFileInfoList filters = filters_dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    foreach(QFileInfo filter, filters)
    {
        if(QLibrary::isLibrary(filter.absoluteFilePath()))
        {
            QPluginLoader plugin_loader(filter.absoluteFilePath(), this);
            if(dynamic_cast<CvPluginInterface*>(plugin_loader.instance()))
            {
                ui->listWidget_filters->addItem(filter.fileName());
                plugin_loader.unload(); // we can unload for now
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"),
                                     QString(tr("Make sure %1 is a correct plugin for this application<br>"
                                                "and it's not in use by some other application!")).arg(filter.fileName()));
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Warning"),
                                 QString(tr("Make sure only plugins exist in plugins folder.<br>"
                                            "%1 is not a plugin.")).arg(filter.fileName()));
        }
    }

    if(ui->listWidget_filters->count() <= 0)
    {
        QMessageBox::critical(this, tr("No Plugins"), tr("This application cannot work without plugins!"
                                                         "<br>Make sure that filter_plugins folder exists "
                                                         "in the same folder as the application<br>and that "
                                                         "there are some filter plugins inside it"));
        this->setEnabled(false);
    }
}

void MainWindow::setupUi()
{
    ui->setupUi(this);
}

void MainWindow::initializationOfConnection()
{
    connect(ui->pushButton_input, &QPushButton::clicked, this, &MainWindow::pushButton_input_clicked);
    connect(ui->pushButton_help, &QPushButton::clicked, this, &MainWindow::pushButton_help_clicked);
    connect(ui->pushButton_filter, &QPushButton::clicked, this, &MainWindow::pushButton_filter_clicked);
}

void MainWindow::pushButton_input_clicked()
{
    const QString caption = tr("Open Input Image");
    QString filename = QFileDialog::getOpenFileName(this, caption, QDir::currentPath(), tr("Images") + " (*.jpg *.png *.bmp)");
    if(QFile::exists(filename))
        ui->lineEdit_input->setText(filename);
}

void MainWindow::pushButton_help_clicked()
{
    if(ui->listWidget_filters->currentRow() >= 0)
    {
        QPluginLoader plugin_loader(qApp->applicationDirPath() + FILTERS_SUBFOLDER + ui->listWidget_filters->currentItem()->text());
        CvPluginInterface *plugin = dynamic_cast<CvPluginInterface*>(plugin_loader.instance());
        if (plugin)
            QMessageBox::information(this, tr("Plugin Description"), plugin->description());
        else
            QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure plugin %1 exists and is usable.")).arg(ui->listWidget_filters->currentItem()->text()));
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"), QString(tr("First select a filter plugin from the list.")));
    }
}

void MainWindow::pushButton_filter_clicked()
{
    if (ui->listWidget_filters->currentRow() >= 0 && !ui->lineEdit_input->text().isEmpty())
    {
        QPluginLoader plugin_loader(qApp->applicationDirPath() + FILTERS_SUBFOLDER + ui->listWidget_filters->currentItem()->text());
        CvPluginInterface *plugin = dynamic_cast<CvPluginInterface*>(plugin_loader.instance());
        if (plugin)
        {
            if (QFile::exists(ui->lineEdit_input->text()))
            {
                cv::Mat source = cv::imread(ui->lineEdit_input->text().toStdString());
                cv::Mat result;
                plugin->processImage(source, result);
                cv::imshow(tr("Filtered Image").toStdString(), result);
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure %1 exists.")).arg(ui->lineEdit_input->text()));
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure plugin %1 exists and is usable.")).arg(ui->listWidget_filters->currentItem()->text()));
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"), QString(tr("First select a filter plugin from the list.")));
    }
}
