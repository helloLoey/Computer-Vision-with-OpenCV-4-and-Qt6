#ifndef QBLINKINGWIDGET_H
#define QBLINKINGWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

class QBlinkingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QBlinkingWidget(QWidget *t_parent = nullptr);

protected:
    void paintEvent(QPaintEvent *t_event);

private:
    QTimer m_blink_timer;
    bool m_is_blink;

private slots:
    void onBlink();
};

#endif // QBLINKINGWIDGET_H
