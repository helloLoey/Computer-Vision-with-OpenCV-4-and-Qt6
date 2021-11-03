#include "qblinkingwidget.h"

QBlinkingWidget::QBlinkingWidget(QWidget *t_parent) :
    QWidget(t_parent),
    m_is_blink(false)
{
    connect(&m_blink_timer, &QTimer::timeout, this, &QBlinkingWidget::onBlink);
    m_blink_timer.start(500);
}

void QBlinkingWidget::paintEvent(QPaintEvent *t_event)
{
    Q_UNUSED(t_event);
    QPainter painter(this);
    if(m_is_blink)
        painter.fillRect(this->rect(), QBrush(Qt::red));
    else
        painter.fillRect(this->rect(), QBrush(Qt::white));
}

void QBlinkingWidget::onBlink()
{
    m_is_blink = !m_is_blink;
    this->update();
}
