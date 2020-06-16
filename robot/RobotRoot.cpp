#include "RobotRoot.h"

RobotRoot::RobotRoot(QGraphicsItem *parent): QGraphicsItem(parent)
{
}

//nadanie przestrzeni elementu
QRectF RobotRoot::boundingRect() const
{
    return QRectF(-20,-220,40,220);
}

//nadanie kształtu elementu
void RobotRoot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

      painter->drawPixmap(QPoint(-20,-220),QPixmap(":/robot/Robot_root.png"));
}

