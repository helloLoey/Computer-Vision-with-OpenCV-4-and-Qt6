#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *t_parent) :
    QMainWindow(t_parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_video_processor = new VideoProcessor();
    m_video_processor->moveToThread(new QThread(this));
    connect(m_video_processor->thread(), &QThread::started, m_video_processor, &VideoProcessor::startVideo);
    connect(m_video_processor->thread(), &QThread::finished, m_video_processor, &VideoProcessor::deleteLater);
    connect(m_video_processor, &VideoProcessor::inDisplay, ui->inVideo, &QLabel::setPixmap);
    connect(m_video_processor, &VideoProcessor::outDisplay, ui->outVideo, &QLabel::setPixmap);
    m_video_processor->thread()->start();
}

MainWindow::~MainWindow()
{
    m_video_processor->stopVideo();
    m_video_processor->thread()->quit();
    m_video_processor->thread()->wait();
    delete ui;
}
