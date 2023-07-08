#include "acao_follow.h"


Acao_follow::Acao_follow(Gameobject *parent)
{
        type=ACAO;
        //决定自己是否有远程攻击能力
        islongrange=QRandomGenerator::global()->bounded(0,2);
//        if(islongrange){
//            Acao_longrangeshoottimer= new QTimer(this);
//            Acao_longrangeshoottimer->start(2000);            qDebug()<<"HERE";
//            connect(Acao_longrangeshoottimer,&QTimer::timeout,[=](){
//                qDebug()<<"敌方的子弹";
//                Gameobject*obj = Gameobjectpool::Instance()->GetgameObject(Gameobject::BULLET);
//                Bullet* bullet=(Bullet*)obj;
//                bullet->bullettype=ACAO_LONGRANGE_BULLET;
//                bullet->setPixmap(QPixmap(":/img/bullet.jpg"));
//                bullet->setScale(0.02);
//                bullet->setPos(this->x(),this->y());

//            });
//        }

}

Acao_follow::Acao_follow(QPoint position, QPixmap img, int speed)
{
//    type=ACAO;
//    this->setPos(position);
//    this->setPixmap(img);
//    this->SP=speed;
}

