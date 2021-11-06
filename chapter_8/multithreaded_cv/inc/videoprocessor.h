#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>
#include <QPixmap>
#include <QDebug>
#include <QMutex>
#include <QReadWriteLock>
#include <QSemaphore>
#include <QWaitCondition>
#include "opencv2/opencv.hpp"

class VideoProcessor : public QObject
{
    Q_OBJECT
public:
    explicit VideoProcessor(QObject *t_parent = nullptr) : QObject(t_parent) {}

public slots:
    void startVideo();
    void stopVideo();

private:
    bool stopped;

signals:
    void inDisplay(QPixmap t_pixmap);
    void outDisplay(QPixmap t_pixmap);
};

#endif // VIDEOPROCESSOR_H
