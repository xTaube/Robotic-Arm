#include "Simulation.h"
#include <QGraphicsRectItem>
#include <QTimer>
#include <QDebug>




Simulation::Simulation(QWidget *parent){
    Q_UNUSED(parent);

    //Tworzenie 'sceny"
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1280,720);
    setScene(scene);

    //wyłączenie suwaków
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1280,720);

    //stworzenie i dodanie robota do sceny
    robot = new Robot;
    scene->addItem(robot);
    robot->setFlag(QGraphicsItem::ItemIsFocusable);
    robot->setFocus();

    //stworzenie 4 skrzynek z losową wagą
    for(int i = 0 ; i<4 ; i++){
        chest = new Chest();
        chest->setPos(800 + 70*i, 669);
        chest->defaultPos.x = 800 +70*i;
        chest->defaultPos.y =669;
        chest->chestNumber = i+1;
        chests.push_back(chest);
        scene->addItem(chest);
    }


    //w prawym górnym rogu będzie się pojawiać informacja o wadze skrzyni jeżeli zostanie podniesiona przez ramię
    weightText = new WeightText();
    scene->addItem(weightText);


    show();

}

//funkcja sortuje skrzynki według wagi

void Simulation::sortChests()
{
    Chest *pom = new Chest();
    for(int i = 0; i<4 ; i++){
        for(int j = 0 ; j<3-i ; j++){
            if(chests[j]->getWeight()<chests[j+1]->getWeight()){
                pom = chests[j];
                chests[j] = chests[j+1];
                chests[j+1] = pom;
            }
        }
    }
}

