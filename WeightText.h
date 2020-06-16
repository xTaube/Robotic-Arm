#ifndef WEIGHTTEXT_H
#define WEIGHTTEXT_H


#include <QGraphicsTextItem>
#include "Chest.h"

class WeightText: public QGraphicsTextItem{
public:
    WeightText(QGraphicsItem *parent=0);
    void checkIfCanShowWeight(Chest *ch);
};

#endif // WEIGHTTEXT_Hr
