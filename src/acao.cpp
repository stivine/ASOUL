#include "acao.h"

Acao::Acao(Gameobject *parent) : Gameobject(parent)
{
    type=ACAO;
}
Acao::Acao(QPoint position, QPixmap img,int speed)
{
    type=ACAO;
    this->setPos(position);
    this->setPixmap(img);
    this->SP=speed;


}
void Acao::AcaoMove(QPointF direction){
    if(!isfrozen){
    this->moveBy(direction.x(),direction.y());}
}

void Acao::froze()
{
    this->isfrozen=1;
    frozetimer=new QTimer();
    frozetimer->start(500);
    connect(frozetimer,&QTimer::timeout,[=](){
        isfrozen=0;
        frozetimer->stop();
    });
}
