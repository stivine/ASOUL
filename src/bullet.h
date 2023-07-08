#ifndef BULLET_H
#define BULLET_H
#include "gameobject.h"
enum bullettype{
    ACAO_LONGRANGE_BULLET,
    ROLE_BULLET
};
class Bullet: public Gameobject
{
public:
    Bullet();

    Bullet(QPoint position, QPixmap img, int speed=8);
    void BulletMove(QPoint direction=QPoint(0,-1));
    void BulletMove(double x,double y);
    double SP;
    double AT_LONGRANGE=1;
    int direction;//0为向右，2为向左，3为向下，4为向上,5为任意方向（敌方单位射的）
    int initial_x;
    int initial_y;

    int bullettype;
    double acao_longrangedirection_x;
    double acao_longrangedirection_y;
};

#endif // BULLET_H
