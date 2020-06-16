#ifndef ROBOTBASE_H
#define ROBOTBASE_H

#include <QGraphicsItem>
#include <QPainter>

class RobotBase: public QGraphicsItem{
public:
    RobotBase(QGraphicsItem *parent=0);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};


#endif // ROBOTBASE_H
