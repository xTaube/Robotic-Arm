#include "BlackBox.h"

BlackBox::BlackBox(): QGraphicsItem()
{

}

QRectF BlackBox::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void BlackBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    painter->drawRect(rec);
    painter->fillRect(rec,(Qt::black));
}

