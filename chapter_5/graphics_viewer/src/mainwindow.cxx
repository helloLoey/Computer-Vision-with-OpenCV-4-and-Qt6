#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>
#include <QPixmap>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *t_parent) :
    QMainWindow(t_parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    ui->graphicsView->setAcceptDrops(false);
    ui->graphicsView->setScene(&m_scene);
    ui->graphicsView->setInteractive(true);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setRubberBandSelectionMode(Qt::ContainsItemShape);
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
    QPoint view_position = ui->graphicsView->mapFromParent(t_event->position().toPoint());
    QPointF scene_drop_position = ui->graphicsView->mapToScene(view_position);
    QFileInfo file(t_event->mimeData()->urls().at(0).toLocalFile());
    QPixmap pixmap;
    if(pixmap.load(file.absoluteFilePath()))
    {
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
        item->setPos(scene_drop_position);
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        item->setAcceptedMouseButtons(Qt::LeftButton);
        m_scene.addItem(item);
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("The image file cannot be read!"));
    }
}
