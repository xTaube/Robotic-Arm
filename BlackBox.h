#ifndef BLACKBOX_H
#define BLACKBOX_H

#include <QGraphicsItem>
#include <QPainter>

class BlackBox:public QGraphicsItem{
public:
    BlackBox();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // BLACKBOX_H
