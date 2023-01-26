#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>

class Joystick : public QWidget
{
    Q_OBJECT

    QPoint point;

public:

    enum Direction
    {
        FORWARD=0,
        BACKWARD=1
    };

    explicit Joystick(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* e) override;

    void mouseMoveEvent(QMouseEvent *e) override;

    int heightForWidth( int w ) { return w; }

    uint16_t Angel() const;

    uint16_t Speed() const;

    Direction GetDirection() const;

    bool event(QEvent* event);


signals:

void updated();

};

#endif // JOYSTICK_H
