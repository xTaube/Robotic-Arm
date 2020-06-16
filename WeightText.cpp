#include "WeightText.h"
#include <QFont>
#include <QDebug>

WeightText::WeightText(QGraphicsItem *parent): QGraphicsTextItem(){
    Q_UNUSED(parent);

    setFont(QFont("times",16));
    setDefaultTextColor(Qt::black);
    setPos(1100,30);
}

//jeżeli robot trzyma skrzynie to zostanie wyświetlona waga w górnym prawym rogu
void WeightText::checkIfCanShowWeight(Chest *ch)
{
        if(ch->getAttachStatus()){
            setPlainText("Waga: " + QString::number(ch->getWeight()));
        }
        else{
            setPlainText("");
        }
}

