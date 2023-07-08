#ifndef MYROLE_H
#define MYROLE_H

#include "gameobject.h"
#include <QGraphicsPixmapItem>
#include <QString>
#include <QPixmap>

class Myrole : public Gameobject
{

public:
    float HP=10;
    float HP_max=10;
    float AT=5;
    float SP=5;
    float ATSP=3000;
    Myrole(QString name);
signals:

public slots:

};

#endif // MYROLE_H
