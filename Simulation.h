#ifndef SIMULATION_H
#define SIMULATION_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include "Chest.h"
#include "WeightText.h"
#include "Robot.h"
#include "BlackBox.h"

class Simulation : public QGraphicsView
{
public:
    Simulation(QWidget *parent = 0);
    QGraphicsScene *scene;
    Chest *chest;
    QList <Chest*> chests;
    BlackBox *blackBox;
    WeightText *weightText;
    Robot *robot;
    void sortChests();

};

#endif // SIMULATION_H
