#include "qenhancedgraphicsview.h"
#include <QWheelEvent>

void QEnhancedGraphicsView::wheelEvent(QWheelEvent *t_event)
{
    double angle_delta_y = t_event->angleDelta().y();
    double zoom_factor = qPow(1.0015, angle_delta_y);
    scale(zoom_factor, zoom_factor);
    if (angle_delta_y > 0)
    {
        this->centerOn(m_scene_mouse_position);
        m_scene_mouse_position = this->mapToScene(t_event->position().toPoint());
    }
    this->viewport()->update();
    t_event->accept();
}
