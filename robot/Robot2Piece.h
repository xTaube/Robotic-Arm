#ifndef ROBOT2PIECE_H
#define ROBOT2PIECE_H

#include <QGraphicsItem>
#include <QPainter>

class Robot2Piece: public QGraphicsItem{
public:
    Robot2Piece(QGraphicsItem *parent = 0);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};


#endif // ROBOT2PIECE_H
