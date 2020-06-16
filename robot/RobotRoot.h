#ifndef ROBOTROOT_H
#define ROBOTROOT_H

#include <QGraphicsItem>
#include <QPainter>

class RobotRoot : public QGraphicsItem {
public:
    RobotRoot(QGraphicsItem *parent = 0);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
#endif // ROBOTROOT_H
