#ifndef ROBOT_H
#define ROBOT_H

#include "RobotRoot.h"
#include "Robot2Piece.h"
#include "RobotBase.h"
#include "RobotHead.h"
#include "RobotMoves.h"
#include <QPainter>
#include <QTimer>

struct cords{
    qreal x;
    qreal y;
};

class Robot:public QObject, public QGraphicsItem{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem);
public:
    Robot(QGraphicsItem *parent = 0);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void keyPressEvent(QKeyEvent *event) override;
    cords getHeaderCords();
    bool getRemeberStatus();
    bool getRepeatStatus();
    bool getSortingStatus();
    RobotBase *robotBase;
    RobotRoot *robotRoot;
    Robot2Piece *robot2Piece1;
    Robot2Piece *robot2Piece2;
    RobotHead *robotHead;

private:
    QTimer *timer;
    qreal rootAngle;
    qreal secondPieceAngle;
    qreal thirdPieceAngle;
    qreal headerAngle;
    QList <unsigned long int> KeyTab;
    QList <unsigned long int> sortKeyTab;
    bool remember;
    bool activeTimer;
    bool defaultPosSetted;
    bool repeatModeOn;
    bool sortModeOn;
    int counter;
    int robotSpeed;

public slots:
    void defaultPos();
    void repeatMode();
    void sortMode();

};

#endif // ROBOT_H
