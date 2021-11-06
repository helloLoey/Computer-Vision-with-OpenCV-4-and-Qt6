#ifndef VIDEOPROCESSORTHREAD_H
#define VIDEOPROCESSORTHREAD_H

#include <QObject>
#include <QThread>
#include <QPixmap>
#include "opencv2/opencv.hpp"

class VideoProcessorThread : public QThread
{
    Q_OBJECT
public:
    explicit VideoProcessorThread(QObject *t_parent = nullptr) : QThread(t_parent) {}

private:
    void run() override;

signals:
    void inDisplay(QPixmap t_pixmap);
    void outDisplay(QPixmap t_pixmap);
};

#endif // VIDEOPROCESSORTHREAD_H
