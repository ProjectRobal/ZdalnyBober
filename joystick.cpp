#include "joystick.h"
#include <QDebug>

Joystick::Joystick(QWidget *parent)
    : QWidget{parent}
{
    point.setX(0);
    point.setY(0);
}

void Joystick::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);

    QPainter paint(this);

    QPen pen;

    pen.setColor(QColor(128,128,128));

    pen.setWidth(5);

    paint.setBrush(QColor(224,213,213));

    paint.setPen(pen);

    paint.drawEllipse(0,0,this->width(),this->height());

    double angel=atan2(static_cast<double>(this->point.x()-this->width()/2),static_cast<double>(this->point.y()-this->height()/2));

    uint32_t radius=sqrt(pow(this->point.x()-this->width()/2,2)+pow(this->point.y()-this->height()/2,2));

    paint.drawLine(this->width()/2,this->height()/2,this->point.x(),this->point.y());

    if(radius>=this->width()/2)
    {
        radius=this->width()/2;
    }

    point.setX(sin(angel)*radius +this->width()/2);
    point.setY(cos(angel)*radius +this->height()/2);

    paint.setBrush(QColor(0,0,0));
    pen.setColor(QColor(255,255,255));
    paint.setPen(pen);

    paint.drawEllipse(point.x()-50,point.y()-50,100,100);

}

void Joystick::mouseMoveEvent(QMouseEvent *e)
{
    point=e->pos();

    update();

    emit updated();
}

uint16_t Joystick::Angel() const
{
    uint16_t angel=270+atan2(static_cast<double>(-point.x()+(this->width()/2)),static_cast<double>(-point.y()+(this->height()/2)))*(180.f/M_PI);

    return angel%360;
}

uint16_t Joystick::Speed() const
{
    uint32_t max_radius=sqrt(pow(this->width(),2)+pow(this->height(),2));

    uint32_t radius=sqrt(pow(this->point.x()-this->width()/2,2)+pow(this->point.y()-this->height()/2,2));

    double precent=static_cast<double>(radius)/static_cast<double>(max_radius);

    return precent*65535;
}

Joystick::Direction Joystick::GetDirection() const
{
    uint32_t angel=this->Angel();

    if((angel<=360)&&(angel>=180))
    {
        return Joystick::Direction::FORWARD;
    }

    return Joystick::Direction::BACKWARD;
}

bool Joystick::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
        qDebug() << "touch!";
        return true;
    default:
        // call base implementation
        return QWidget::event(event);
    }
}

