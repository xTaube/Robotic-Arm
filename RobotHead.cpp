#include "RobotHead.h"

RobotHead::RobotHead(QGraphicsItem *parent): QGraphicsItem(parent)
{
    somethingOnHead = false;
}

//nadanie przestrzeni dla elementu
QRectF RobotHead::boundingRect() const
{
    return QRectF(-25,-20,50,20);
}

//nadanie kształtu dla elementu
void RobotHead::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(QPoint(-25,-20),QPixmap(":/robot/robot_header"));
}

//funkcja zwraca informacje o tym czy aktualnie robot coś trzyma
bool RobotHead::isSomethingOnHead()
{
    return somethingOnHead;
}

//jeżeli skrzynia zostanie złapana bądź puszczona robot zmienia status tego czy coś trzyma czy nie
void RobotHead::changeHeadStatus()
{
    if(somethingOnHead) somethingOnHead = false;
    else somethingOnHead = true;
}
