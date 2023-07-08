#include "bullet.h"
#include "mainscene.h"
#include "gameobjectpool.h"
Bullet::Bullet(){
    type = BULLET;
    SP = 8;
}


Bullet::Bullet(QPoint position, QPixmap img,int speed)
{   type = BULLET;
    this->setPos(position);
    this->setPixmap(img);
    this->SP=speed;
}

void Bullet::BulletMove(QPoint direction)
{
    this->moveBy(direction.x()*SP,direction.y()*SP);

}
void Bullet::BulletMove(double x,double y)
{
    this->moveBy(x*SP,y*SP);

}



