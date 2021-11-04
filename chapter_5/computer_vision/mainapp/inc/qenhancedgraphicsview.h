#ifndef QENHANCEDGRAPHICSVIEW_H
#define QENHANCEDGRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>

class QEnhancedGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QEnhancedGraphicsView(QWidget *t_parent = nullptr) : QGraphicsView(t_parent) {}

protected:
    void wheelEvent(QWheelEvent *t_event);

private:
    QPointF m_scene_mouse_position;
};

#endif // QENHANCEDGRAPHICSVIEW_H
