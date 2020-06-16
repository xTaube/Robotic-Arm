#include "Chest.h"
#include "Simulation.h"
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

extern Simulation *simulation;

Chest::Chest(QGraphicsItem *parent): QObject() , QGraphicsItem(parent)
{
    Q_UNUSED(parent);
    weight = randomWeight();
    isAttached = false;
    isAttachable = false;
    chestAngle = 0;

    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(freeFall()));                      //funkcja freeFall() będzie się odtwarzała co 5ms
    timer->start(5);
}

//stworzenie przestrzeni dla obiektu
QRectF Chest::boundingRect() const
{
    return QRectF(-25,0,50,50);
}

//nadanie kształtu dla obiektu
void Chest::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(QPoint(-25,0),QPixmap(":/robot/chest.png"));
}

//zwraca wage skrzyni
int Chest::getWeight()
{
    return weight;
}

//losuje wage dla skrzyni
int Chest::randomWeight()
{
    int random = QRandomGenerator::global()->bounded(200) + 30;
    return random;
}

//funkca która przyczepią bądź odczepia skrzynię od robota
void Chest::attach()
{
    if(isAttached) isAttached = false;
    else isAttached = true;
    simulation->weightText->checkIfCanShowWeight(this);
    update();
}

//funkcja resetuje pozycje skrzyki oraz nadaje jej nową wagę
void Chest::resetChest()
{
    weight = randomWeight();
    setPos(defaultPos.x,defaultPos.y);
}

//funkcja sprawdza czy skrzynia koliduje z "głową robota"
bool Chest::checkCollision()
{
    QList <QGraphicsItem*> colliding_items = collidingItems();
    if(colliding_items.size() == 0) isAttachable = false;
    for(int i = 0, n = colliding_items.size() ; i<n ; i++){
        if(typeid (*(colliding_items[i])) == typeid(RobotHead)){
            isAttachable = true;
            return isAttachable;
        }
        else isAttachable = false;
    }
    return isAttachable;
}

//funkcja zwarca wartość boolowską w zależności od tego czy skrzynka jest przyczepiona do robota czy nie
bool Chest::getAttachStatus()
{
    return isAttached;
}

//funkcja sprawdza czy skrzynia koliduje z inną skrzynią
bool Chest::checkCollisionWithChest()
{
    QList <QGraphicsItem*> colliding_items = collidingItems();
    if(colliding_items.size() == 0) return false;
    for(int i = 0, n = colliding_items.size() ; i<n ; i++){
        if(typeid (*(colliding_items[i])) == typeid(Chest)){
            if(colliding_items[i]->pos().y() > pos().y()) return true;
        }
    }
    return false;
}

//funkcja nakłada na skrzynię efekt grawitacji
void Chest::freeFall()
{
   if(pos().y()<669 && !isAttached && !checkCollisionWithChest()) setPos(pos().x(),pos().y()+5);
   if((checkCollisionWithChest()||pos().y() >= 669) && !isAttached){
       if(pos().y()>=669) setRotation(chestAngle);
       chestAngle = 0;
   }
}








