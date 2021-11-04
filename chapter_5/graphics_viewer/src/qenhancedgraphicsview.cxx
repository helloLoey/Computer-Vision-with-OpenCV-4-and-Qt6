#include "qenhancedgraphicsview.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QGraphicsItem>

void QEnhancedGraphicsView::wheelEvent(QWheelEvent *t_event)
{
    double angleDeltaY = t_event->angleDelta().y();
    double zoomFactor = qPow(1.0015, angleDeltaY);
    scale(zoomFactor, zoomFactor);
    if(angleDeltaY > 0)
    {
        this->centerOn(sceneMousePos);
        sceneMousePos = this->mapToScene(t_event->position().toPoint());
    }
    this->viewport()->update();
    t_event->accept();
}

void QEnhancedGraphicsView::mousePressEvent(QMouseEvent *t_event)
{
    if(t_event->button() == Qt::RightButton)
    {
        QMenu menu;
        QAction *clear_all_action = menu.addAction("Clear All");
        connect(clear_all_action, SIGNAL(triggered(bool)), this, SLOT(clearAll(bool)));
        QAction *clear_selected_action = menu.addAction("Clear Selected");
        connect(clear_selected_action, SIGNAL(triggered(bool)), this, SLOT(clearSelected(bool)));
        QAction *no_effect_action = menu.addAction("No Effect");
        connect(no_effect_action, SIGNAL(triggered(bool)), this, SLOT(noEffect(bool)));
        QAction *blurEffectAction = menu.addAction("Blur Effect");
        connect(blurEffectAction, SIGNAL(triggered(bool)), this, SLOT(blurEffect(bool)));
        QAction *dropShadEffectAction = menu.addAction("Drop Shadow Effect");
        connect(dropShadEffectAction, SIGNAL(triggered(bool)), this, SLOT(dropShadowEffect(bool)));
        QAction *colorizeEffectAction = menu.addAction("Colorize Effect");
        connect(colorizeEffectAction, SIGNAL(triggered(bool)), this, SLOT(colorizeEffect(bool)));
        QAction *customEffectAction = menu.addAction("Custom Effect");
        connect(customEffectAction, SIGNAL(triggered(bool)), this, SLOT(customEffect(bool)));
        menu.exec(t_event->globalPosition().toPoint());
        t_event->accept();
    }
    else
    {
        QGraphicsView::mousePressEvent(t_event);
    }
}

void QEnhancedGraphicsView::clearAll(bool)
{
    scene()->clear();
}

void QEnhancedGraphicsView::clearSelected(bool)
{
    while(scene()->selectedItems().count() > 0)
    {
        delete scene()->selectedItems().at(0);
        scene()->selectedItems().removeAt(0);
    }
}

void QEnhancedGraphicsView::noEffect(bool)
{
    foreach(QGraphicsItem *item, scene()->selectedItems())
        item->setGraphicsEffect(Q_NULLPTR);
}

void QEnhancedGraphicsView::blurEffect(bool)
{
    foreach(QGraphicsItem *item, scene()->selectedItems())
        item->setGraphicsEffect(new QGraphicsBlurEffect(this));
}

void QEnhancedGraphicsView::dropShadowEffect(bool)
{
    foreach(QGraphicsItem *item, scene()->selectedItems())
        item->setGraphicsEffect(new QGraphicsDropShadowEffect(this));
}

void QEnhancedGraphicsView::colorizeEffect(bool)
{
    foreach(QGraphicsItem *item, scene()->selectedItems())
        item->setGraphicsEffect(new QGraphicsColorizeEffect(this));
}

void QEnhancedGraphicsView::customEffect(bool)
{
    foreach(QGraphicsItem *item, scene()->selectedItems())
        item->setGraphicsEffect(new QCustomGraphicsEffect(this));
}
