#ifndef ROBOTMOVES_H
#define ROBOTMOVES_H

#include <QList>
#include <Chest.h>


QList <unsigned long int> firstIsHeaviest();
QList <unsigned long int> secondIsHeaviest();
QList <unsigned long int> thirdIsHeaviest();
QList <unsigned long int> fourthIsHeaviest();
QList <unsigned long int> firstIsSecondHeaviest();
QList <unsigned long int> secondIsSecondHeaviest();
QList <unsigned long int> thirdSecondHeaviest();
QList <unsigned long int> fourthIsSecondHeaviest();
QList <unsigned long int> firstIsThirdHeaviest();
QList <unsigned long int> secondIsThirdHeaviest();
QList <unsigned long int> thirdIsThirdHeaviest();
QList <unsigned long int> fourthIsThirdHeaviest();
QList <unsigned long int> firstIsLightest();
QList <unsigned long int> secondIsLightest();
QList <unsigned long int> thirdIsLightest();
QList <unsigned long int> fourthIsLightest();
QList <unsigned long int> makeSortKeyTab(QList <Chest*> ch);

#endif // ROBOTMOVES_H
