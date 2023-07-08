#ifndef DROPS_H
#define DROPS_H
#include"gameobject.h"
#include<QRandomGenerator>
enum Dropstype{
    COIN,
    HEART,
};
class Drops:public Gameobject
{
public:
    Drops();
    int Dropstype;
};

#endif // DROPS_H
