#ifndef Chest_H
#define Chest_H

#include <QGraphicsItem>
#include <QPainter>

struct position{
    double x;
    double y;
};

class Chest :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Chest(QGraphicsItem *parent=0);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    int getWeight();
    int randomWeight();
    void showWeight();
    void attach();
    void resetChest();
    bool checkCollision();
    bool getAttachStatus();
    bool checkCollisionWithChest();
    int chestNumber;
    qreal chestAngle;
    position defaultPos;

protected:
    int weight;
    bool isAttachable;
    bool isAttached;
public slots:
    void freeFall();
};

#endif // Chest_H
