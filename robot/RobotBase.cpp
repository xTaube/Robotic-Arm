#include "RobotBase.h"
#include "Simulation.h"

extern Simulation *simulation;


RobotBase::RobotBase(QGraphicsItem *parent): QGraphicsItem(parent)
{
}

//nadanie przestrzeni dla elementu
QRectF RobotBase::boundingRect() const
{
     return QRectF(0,0,203,80);
}

//nadanie kształtu dla elementu
void RobotBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(simulation->robot->getRemeberStatus()){
         painter->drawPixmap(QPoint(0,0),QPixmap(":/robot/robot_base_green.png"));
    }
    else if(simulation->robot->getRepeatStatus()){
         painter->drawPixmap(QPoint(0,0),QPixmap(":/robot/robot_base_red.png"));
    }
    else if(simulation->robot->getSortingStatus()){
         painter->drawPixmap(QPoint(0,0),QPixmap(":/robot/robot_base_blue.png"));
    }
    else painter->drawPixmap(QPoint(0,0),QPixmap(":/robot/robot_base.png"));
}
