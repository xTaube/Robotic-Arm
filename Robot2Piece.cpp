#include "Robot2Piece.h"

Robot2Piece::Robot2Piece(QGraphicsItem *parent): QGraphicsItem(parent)
{
}

//nadanie przestrzeni dla elementu
QRectF Robot2Piece::boundingRect() const
{
    return QRectF(-20,-212,40,212);
}

//nadanie kształtu dla elementu
void Robot2Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(QPoint(-20,-212),QPixmap(":/robot/robot_2piece.png"));

}
