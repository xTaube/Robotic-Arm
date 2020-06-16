#include "Robot.h"
#include "Simulation.h"
#include <QDebug>
#include <QKeyEvent>
#include <QList>
#include <QtMath>

extern Simulation *simulation;

Robot::Robot(QGraphicsItem *parent):QObject(), QGraphicsItem(parent)
{
    setFlag(ItemHasNoContents);

    remember = false;
    activeTimer = false;
    repeatModeOn = false;
    sortModeOn= false;

    robotBase = new RobotBase(this);
    robotRoot = new RobotRoot(robotBase);
    robot2Piece1 = new Robot2Piece(robotRoot);
    robot2Piece2 = new Robot2Piece(robot2Piece1);
    robotHead = new RobotHead(robot2Piece2);

    rootAngle = 0;
    secondPieceAngle = 35;
    thirdPieceAngle = 90;
    headerAngle = 0;
    robotSpeed = 75;

    robotBase->setPos(400,642);
    robotRoot->setPos(102,25);
    robot2Piece1->setPos(0,-220);
    robot2Piece2->setPos(0,-212);
    robotHead->setPos(0,-212);
    robot2Piece1->setRotation(secondPieceAngle);
    robot2Piece2->setRotation(thirdPieceAngle);

}

// robot sam w sobie nie zabiera przestrzeni, przestrzeń zabierają jego poszczególne elementy, które są tworzone w innym pliku(mimo, że funkcja nic nie zwraca jest potrzebna do poprawnego utworzenia obiektu)
QRectF Robot::boundingRect() const
{
    return QRectF();
}

// robot nie ma swojego kształtu więc funkcja jest pusta (każda jego część ma nadawany kształt osobno), jednak jest potrzebna do poprawnego utworzenia obiektu
void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//funkcja zczytuje przyciski użyte przez użytkownika i wykonuje odpowiednie funkcje
void Robot::keyPressEvent(QKeyEvent *event)
{

    //jeżeli jest włączony tryb zapamiętywania przyciski użyte przez użytkownika są zapisywane w specjalnej tablicy
    if(remember){
        if(event->key()!= Qt::Key_R && event->key() != Qt::Key_T && event->key() != Qt::Key_Y && event->key() != Qt::Key_Plus && event->key() != Qt::Key_Minus){
        KeyTab.push_back(event->key());
        qDebug()<<event->key()<<",";
       }
    }

    //odpowieni przycisk powoduje ruch odpowiedniej części robota
    if(event->key() == Qt::Key_Right && !activeTimer){
       if(rootAngle<50){
            rootAngle = rootAngle + 5;
            robotRoot->setRotation(rootAngle);
       }
    }

    //odpowieni przycisk powoduje ruch odpowiedniej części robota
    else if(event->key() == Qt::Key_Left && !activeTimer){
       if(rootAngle>-50){
            rootAngle = rootAngle - 5;
            robotRoot->setRotation(rootAngle);
       }
    }

    //odpowieni przycisk powoduje ruch odpowiedniej części robota
    else if(event->key() == Qt::Key_Up && !activeTimer){
        if(secondPieceAngle>-90){
            secondPieceAngle = secondPieceAngle - 5;
            robot2Piece1->setRotation(secondPieceAngle);
        }
    }

    //odpowieni przycisk powoduje ruch odpowiedniej części robota
    else if(event->key() == Qt::Key_Down && !activeTimer){
        if(secondPieceAngle<90){
            secondPieceAngle = secondPieceAngle + 5;
            robot2Piece1->setRotation(secondPieceAngle);
        }
    }

    //odpowieni przycisk powoduje ruch odpowiedniej części robota
    else if(event->key() == Qt::Key_S && !activeTimer){
        if(thirdPieceAngle<135){
            thirdPieceAngle = thirdPieceAngle + 5;
            robot2Piece2->setRotation(thirdPieceAngle);
        }
    }

    //odpowieni przycisk powoduje ruch odpowiedniej części robota
    else if(event->key() == Qt::Key_W && !activeTimer){
        if(thirdPieceAngle>-135){
            thirdPieceAngle = thirdPieceAngle - 5;
            robot2Piece2->setRotation(thirdPieceAngle);
        }
    }

    //odpowieni przycisk powoduje ruch odpowiedniej części robota
    else if(event->key() == Qt::Key_D && !activeTimer){
        if(headerAngle>-90){
            headerAngle = headerAngle - 5;
            robotHead->setRotation(headerAngle);
        }
    }

    //odpowieni przycisk powoduje ruch odpowiedniej części robota
    else if(event->key() == Qt::Key_A && !activeTimer){
        if(headerAngle<90){
            headerAngle = headerAngle + 5;
            robotHead->setRotation(headerAngle);
        }
    }

    //czas wykonania czynności przez robota zostaje wydłużony
    else if(event->key() == Qt::Key_Plus && !activeTimer){
         robotSpeed = robotSpeed + 5;
    }

    //czas wykonania czynności przez robota zostaje skrócony
    else if(event->key() == Qt::Key_Minus && !activeTimer){
         if(robotSpeed>5) robotSpeed = robotSpeed - 5;
    }

    //ustawienie skrzynek na pozycji początkowej
    else if(event->key() == Qt::Key_P && !activeTimer){
        for(int i = 0 ; i<4 ; i++){
            if(simulation->chests[i]->getAttachStatus()){
                simulation->chests[i]->attach();
                robotHead->changeHeadStatus();
            }
            simulation->chests[i]->resetChest();
        }
    }

    //włączenie lub wyłączenie trybu remeber
    else if(event->key() == Qt::Key_R && !activeTimer){
         if(remember) {
            remember = false;
            for(int i = 0 ; i<4 ; i++){
                if(simulation->chests[i]->getAttachStatus()){
                    simulation->chests[i]->attach();
                    robotHead->changeHeadStatus();
                }
                simulation->chests[i]->setPos(simulation->chests[i]->defaultPos.x,simulation->chests[i]->defaultPos.y);
            }
          }
          else{
            remember = true;
            for(int i = 0 ; i<4 ; i++){
                if(simulation->chests[i]->getAttachStatus()){
                    simulation->chests[i]->attach();
                    robotHead->changeHeadStatus();
                }
                simulation->chests[i]->setPos(simulation->chests[i]->defaultPos.x,simulation->chests[i]->defaultPos.y);
            }
            if(!KeyTab.empty()){
               KeyTab.clear();
            }
          }
            timer = new QTimer();
            activeTimer = true;
            connect(timer,SIGNAL(timeout()),this,SLOT(defaultPos()));
            timer->start(robotSpeed);
    }

    //włączenie lub wyłączenie trybu repeatMode
    else if(event->key() == Qt::Key_T && !KeyTab.empty() && !remember && !sortModeOn){
      if(repeatModeOn){
          repeatModeOn = false;
          activeTimer = false;
          for(int i = 0 ; i<4 ; i++){
               if(simulation->chests[i]->getAttachStatus()){
                   simulation->chests[i]->attach();
                   robotHead->changeHeadStatus();
               }
              simulation->chests[i]->setPos(simulation->chests[i]->defaultPos.x,simulation->chests[i]->defaultPos.y);
          }
          delete timer;
      }
      else{
          for(int i = 0 ; i<4 ; i++){
               if(simulation->chests[i]->getAttachStatus()){
                   simulation->chests[i]->attach();
                   robotHead->changeHeadStatus();
               }
              simulation->chests[i]->setPos(simulation->chests[i]->defaultPos.x,simulation->chests[i]->defaultPos.y);
          }
          repeatModeOn = true;
          defaultPosSetted = false;
          counter = 0;
          timer = new QTimer();
          activeTimer = true;
          connect(timer,SIGNAL(timeout()),this,SLOT(repeatMode()));
          timer->start(robotSpeed);
      }
    }

    //włączenie bądź wyłączenie trybu sortingMode
    else if(event->key() == Qt::Key_Y && !remember && !repeatModeOn){
        if(sortModeOn){
            sortModeOn = false;
            activeTimer = false;
            delete timer;
        }
        else{
            simulation->sortChests();
            for(int i = 0 ; i<4 ; i++){
                 if(simulation->chests[i]->getAttachStatus()){
                     simulation->chests[i]->attach();
                     robotHead->changeHeadStatus();
                 }
                simulation->chests[i]->setPos(simulation->chests[i]->defaultPos.x,simulation->chests[i]->defaultPos.y);
            }
            sortModeOn = true;
            defaultPosSetted = false;
            counter = 0;
            sortKeyTab = makeSortKeyTab(simulation->chests);
            timer = new QTimer();
            activeTimer = true;
            connect(timer,SIGNAL(timeout()),this,SLOT(sortMode()));
            timer->start(robotSpeed);
        }
      }
    //złapanie bądź puszczenie skrzynki
    else if(event->key() == Qt::Key_Space && !activeTimer){
      for(int i = 0 ; i<4 ; i++){
          if(simulation->chests[i]->checkCollision()&&(robotHead->isSomethingOnHead() == simulation->chests[i]->getAttachStatus())){
               simulation->chests[i]->attach();
               robotHead->changeHeadStatus();
          }
      }
    }
    for(int i = 0 ; i<4 ; i++){
        if(simulation->chests[i]->getAttachStatus()){
           simulation->chests[i]->setPos(getHeaderCords().x,getHeaderCords().y);
           simulation->chests[i]->chestAngle = -(rootAngle + secondPieceAngle + thirdPieceAngle + headerAngle);
           simulation->chests[i]->setRotation(-(simulation->chests[i]->chestAngle+180));
        }
    }
}

//funkcja zwraca aktualne wspórzędne "głowki robota"
cords Robot::getHeaderCords()
{
    cords c;
    c.x = qCos((rootAngle-90)*(M_PI/180))*220 + qCos((secondPieceAngle+rootAngle-90)*(M_PI/180))*212 + qCos((thirdPieceAngle+rootAngle+secondPieceAngle-90)*(M_PI/180))*212 + qCos((thirdPieceAngle+headerAngle+rootAngle+secondPieceAngle-90)*(M_PI/180))*18 + 502;
    c.y = qSin((rootAngle-90)*(M_PI/180))*220 + qSin((secondPieceAngle+rootAngle-90)*(M_PI/180))*212 + qSin((thirdPieceAngle+rootAngle+secondPieceAngle-90)*(M_PI/180))*212 + qSin((thirdPieceAngle+headerAngle+rootAngle+secondPieceAngle-90)*(M_PI/180))*18 + 667;

    return c;
}

//funkcja zwaraca informacje o tym czy aktywny jest tryb remember
bool Robot::getRemeberStatus()
{
    return  remember;
}

//funkcja zwaraca informacje o tym czy aktywny jest tryb repeatMode
bool Robot::getRepeatStatus()
{
    return repeatModeOn;
}

//funkcja zwaraca informacje o tym czy aktywny jest tryb sortingMode
bool Robot::getSortingStatus()
{
    return sortModeOn;
}

//funkcja ustawia robota do pozycji początkowej
void Robot::defaultPos()
{
    qreal change1;
    qreal change2;
    qreal change3;
    qreal change4;

    if(rootAngle < 0) change1 = 5;
    else change1 = -5;
    if(secondPieceAngle < 35) change2 = 5;
    else change2 = -5;
    if(thirdPieceAngle < 90) change3 = 5;
    else change3 = -5;
    if(headerAngle < 0) change4 = 5;
    else change4 = -5;

    if(rootAngle != 0){
        rootAngle = rootAngle + change1;
        robotRoot->setRotation(rootAngle);
    }
    if(secondPieceAngle != 35){
        secondPieceAngle = secondPieceAngle + change2;
        robot2Piece1->setRotation(secondPieceAngle);
    }
    if(thirdPieceAngle != 90){
        thirdPieceAngle = thirdPieceAngle + change3;
        robot2Piece2->setRotation(thirdPieceAngle);
    }
    if(headerAngle != 0){
        headerAngle = headerAngle + change4;
        robotHead->setRotation(headerAngle);
    }
    if(rootAngle == 0 && secondPieceAngle == 35 && thirdPieceAngle == 90 && headerAngle == 0){
        timer->stop();
        activeTimer = false;
        delete timer;
    }
}

//funkcja powtarza zapamiętane ruchy użytkownika
void Robot::repeatMode()
{
    if(!defaultPosSetted){
        qreal change1;
        qreal change2;
        qreal change3;
        qreal change4;

        if(rootAngle < 0) change1 = 5;
        else change1 = -5;
        if(secondPieceAngle < 35) change2 = 5;
        else change2 = -5;
        if(thirdPieceAngle < 90) change3 = 5;
        else change3 = -5;
        if(headerAngle < 0) change4 = 5;
        else change4 = -5;

        if(rootAngle != 0){
            rootAngle = rootAngle + change1;
            robotRoot->setRotation(rootAngle);
        }
        if(secondPieceAngle != 35){
            secondPieceAngle = secondPieceAngle + change2;
            robot2Piece1->setRotation(secondPieceAngle);
        }
        if(thirdPieceAngle != 90){
            thirdPieceAngle = thirdPieceAngle + change3;
            robot2Piece2->setRotation(thirdPieceAngle);
        }
        if(headerAngle != 0){
            headerAngle = headerAngle + change4;
            robotHead->setRotation(headerAngle);
        }
        if(rootAngle == 0 && secondPieceAngle == 35 && thirdPieceAngle == 90 && headerAngle == 0){
            defaultPosSetted = true;
        }
    }
    else{
        if(KeyTab[counter] == Qt::Key_Right){
            if(rootAngle<50){
                 rootAngle = rootAngle + 5;
                 robotRoot->setRotation(rootAngle);
             }
        }
        else if(KeyTab[counter] == Qt::Key_Left){
           if(rootAngle>-50){
                rootAngle = rootAngle - 5;
                robotRoot->setRotation(rootAngle);
           }
        }
        if(KeyTab[counter] == Qt::Key_Up){
            if(secondPieceAngle>-90){
                secondPieceAngle = secondPieceAngle - 5;
                robot2Piece1->setRotation(secondPieceAngle);
            }
        }
        else if(KeyTab[counter] == Qt::Key_Down){
            if(secondPieceAngle<90){
                secondPieceAngle = secondPieceAngle + 5;
                robot2Piece1->setRotation(secondPieceAngle);
            }
        }
        else if(KeyTab[counter] == Qt::Key_S){
            if(thirdPieceAngle<135){
                thirdPieceAngle = thirdPieceAngle + 5;
                robot2Piece2->setRotation(thirdPieceAngle);
            }
        }
        else if(KeyTab[counter] == Qt::Key_W){
            if(thirdPieceAngle>-135){
                thirdPieceAngle = thirdPieceAngle - 5;
                robot2Piece2->setRotation(thirdPieceAngle);
            }
        }
        else if(KeyTab[counter] == Qt::Key_D){
            if(headerAngle>-90){
                headerAngle = headerAngle - 5;
                robotHead->setRotation(headerAngle);
            }
        }
        else if(KeyTab[counter] == Qt::Key_A){
            if(headerAngle<90){
                headerAngle = headerAngle + 5;
                robotHead->setRotation(headerAngle);
            }
        }
        else if(KeyTab[counter] == Qt::Key_Space){
          for(int i = 0 ; i<4 ; i++){
              if(simulation->chests[i]->checkCollision()&&(robotHead->isSomethingOnHead() == simulation->chests[i]->getAttachStatus())){
                   simulation->chests[i]->attach();
                   robotHead->changeHeadStatus();
              }
          }
        }
        for(int i = 0 ; i<4 ; i++){
            if(simulation->chests[i]->getAttachStatus()){
               simulation->chests[i]->setPos(getHeaderCords().x,getHeaderCords().y);
               simulation->chests[i]->chestAngle = -(rootAngle + secondPieceAngle + thirdPieceAngle + headerAngle);
               simulation->chests[i]->setRotation(-(simulation->chests[i]->chestAngle+180));
            }
        }
        counter++;
        if(counter == KeyTab.size()){
            counter = 0;
            defaultPosSetted = false;
            for(int i = 0 ; i<4 ; i++){
                simulation->chests[i]->setPos(simulation->chests[i]->defaultPos.x,simulation->chests[i]->defaultPos.y);
            }
        }
    }
}

//funkcja służąca do sortowania skrzynek po wadze
void Robot::sortMode()
{
    if(!defaultPosSetted){
        qreal change1;
        qreal change2;
        qreal change3;
        qreal change4;

        if(rootAngle < 0) change1 = 5;
        else change1 = -5;
        if(secondPieceAngle < 35) change2 = 5;
        else change2 = -5;
        if(thirdPieceAngle < 90) change3 = 5;
        else change3 = -5;
        if(headerAngle < 0) change4 = 5;
        else change4 = -5;

        if(rootAngle != 0){
            rootAngle = rootAngle + change1;
            robotRoot->setRotation(rootAngle);
        }
        if(secondPieceAngle != 35){
            secondPieceAngle = secondPieceAngle + change2;
            robot2Piece1->setRotation(secondPieceAngle);
        }
        if(thirdPieceAngle != 90){
            thirdPieceAngle = thirdPieceAngle + change3;
            robot2Piece2->setRotation(thirdPieceAngle);
        }
        if(headerAngle != 0){
            headerAngle = headerAngle + change4;
            robotHead->setRotation(headerAngle);
        }
        if(rootAngle == 0 && secondPieceAngle == 35 && thirdPieceAngle == 90 && headerAngle == 0){
            defaultPosSetted = true;
        }
    }
    else{
        if(sortKeyTab[counter] == Qt::Key_Right){
            if(rootAngle<50){
                 rootAngle = rootAngle + 5;
                 robotRoot->setRotation(rootAngle);
             }
        }
        else if(sortKeyTab[counter] == Qt::Key_Left){
           if(rootAngle>-50){
                rootAngle = rootAngle - 5;
                robotRoot->setRotation(rootAngle);
           }
        }
        if(sortKeyTab[counter] == Qt::Key_Up){
            if(secondPieceAngle>-90){
                secondPieceAngle = secondPieceAngle - 5;
                robot2Piece1->setRotation(secondPieceAngle);
            }
        }
        else if(sortKeyTab[counter] == Qt::Key_Down){
            if(secondPieceAngle<90){
                secondPieceAngle = secondPieceAngle + 5;
                robot2Piece1->setRotation(secondPieceAngle);
            }
        }
        else if(sortKeyTab[counter] == Qt::Key_S){
            if(thirdPieceAngle<135){
                thirdPieceAngle = thirdPieceAngle + 5;
                robot2Piece2->setRotation(thirdPieceAngle);
            }
        }
        else if(sortKeyTab[counter] == Qt::Key_W){
            if(thirdPieceAngle>-135){
                thirdPieceAngle = thirdPieceAngle - 5;
                robot2Piece2->setRotation(thirdPieceAngle);
            }
        }
        else if(sortKeyTab[counter] == Qt::Key_D){
            if(headerAngle>-90){
                headerAngle = headerAngle - 5;
                robotHead->setRotation(headerAngle);
            }
        }
        else if(sortKeyTab[counter] == Qt::Key_A){
            if(headerAngle<90){
                headerAngle = headerAngle + 5;
                robotHead->setRotation(headerAngle);
            }
        }
        else if(sortKeyTab[counter] == Qt::Key_Space){
          for(int i = 0 ; i<4 ; i++){
              if(simulation->chests[i]->checkCollision()&&(robotHead->isSomethingOnHead() == simulation->chests[i]->getAttachStatus())){
                   simulation->chests[i]->attach();
                   robotHead->changeHeadStatus();
              }
          }
        }
        for(int i = 0 ; i<4 ; i++){
            if(simulation->chests[i]->getAttachStatus()){
               simulation->chests[i]->setPos(getHeaderCords().x,getHeaderCords().y);
               simulation->chests[i]->chestAngle = -(rootAngle + secondPieceAngle + thirdPieceAngle + headerAngle);
               simulation->chests[i]->setRotation(-(simulation->chests[i]->chestAngle+180));
            }
        }
        counter++;
        if(counter == sortKeyTab.size()){
            counter = 0;
            sortKeyTab.clear();
            defaultPosSetted = false;
            sortModeOn = false;
            activeTimer = false;
            delete timer;
        }
    }
}





