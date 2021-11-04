#ifndef QCUSTOMGRAPHICSEFFECT_H
#define QCUSTOMGRAPHICSEFFECT_H

#include <QGraphicsEffect>
#include <QPainter>

class QCustomGraphicsEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    explicit QCustomGraphicsEffect(QObject *parent = nullptr) : QGraphicsEffect(parent) {}

protected:
    void draw(QPainter *t_painter) override;
};

#endif // QCUSTOMGRAPHICSEFFECT_H
