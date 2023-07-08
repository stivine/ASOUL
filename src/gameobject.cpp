#include "gameobject.h"
#include "gameobjectpool.h"
Gameobject::Gameobject(QGraphicsPixmapItem *parent) :QGraphicsPixmapItem(parent)
{

}

void Gameobject::Gameobjectdelete(QGraphicsScene* scene)
{
    if(isItemInScene(scene,this))scene->removeItem(this);
    Gameobjectpool::Instance()->Recovery(this);
}

