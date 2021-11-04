#ifndef QENHANCEDGRAPHICSVIEW_H
#define QENHANCEDGRAPHICSVIEW_H

#include <QGraphicsView>
#include "qcustomgraphicseffect.h"

class QEnhancedGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QEnhancedGraphicsView(QWidget *t_parent = nullptr): QGraphicsView(t_parent) {}

protected:
    void wheelEvent(QWheelEvent *t_event) override;
    void mousePressEvent(QMouseEvent *t_event) override;

private slots:
    void clearAll(bool);
    void clearSelected(bool);
    void noEffect(bool);
    void blurEffect(bool);
    void dropShadowEffect(bool);
    void colorizeEffect(bool);
    void customEffect(bool);

private:
    QPointF sceneMousePos;

};

#endif // QENHANCEDGRAPHICSVIEW_H
