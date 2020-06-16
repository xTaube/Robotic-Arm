#ifndef ROBOTHEAD_H
#define ROBOTHEAD_H

#include <QGraphicsItem>
#include <QPainter>

class RobotHead: public QGraphicsItem{
public:
    RobotHead(QGraphicsItem *parent = NULL);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    bool isSomethingOnHead();
    void changeHeadStatus();
private:
    bool somethingOnHead;
};

#endif // ROBOTHEAD_H
