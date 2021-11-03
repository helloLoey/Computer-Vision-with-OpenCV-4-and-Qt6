#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *t_parent) :
    QMainWindow(t_parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *t_event)
{
    QStringList accepted_file_types;
    accepted_file_types.append("jpg");
    accepted_file_types.append("png");
    accepted_file_types.append("bmp");
    if (t_event->mimeData()->hasUrls() && t_event->mimeData()->urls().count() == 1)
    {

        QFileInfo file(t_event->mimeData()->urls().at(0).toLocalFile());
        if(accepted_file_types.contains(file.suffix().toLower()))
            t_event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *t_event)
{
    QFileInfo file(t_event->mimeData()->urls().at(0).toLocalFile());
    if (m_pixmap.load(file.absoluteFilePath()))
        ui->label->setPixmap(m_pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    else
        QMessageBox::critical(this, tr("Error"), tr("The image file cannot be read!"));
}

void MainWindow::resizeEvent(QResizeEvent *t_event)
{
    Q_UNUSED(t_event);
    if(!m_pixmap.isNull())
        ui->label->setPixmap(m_pixmap.scaled(ui->label->width() - 5, ui->label->height() - 5, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
