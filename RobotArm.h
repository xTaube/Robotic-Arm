#ifndef ROBOTARM_H
#define ROBOTARM_H

#include <QGraphicsItem>


class Robot : public QGraphicsItem{
public:
    Robot(QGraphicsItem *parent = 0);
    QRectF boundingRect();
};

#endif // ROBOTARM_H
