#ifndef ACAO_H
#define ACAO_H
#include "gameobject.h"
#include<QGraphicsPixmapItem>
#include<QtMath>
#include<QDebug>
#include<QRandomGenerator>
#include<QTimer>
#include<QObject>
#include<QGraphicsColorizeEffect>
class Acao : public Gameobject
{
public:
    explicit Acao(Gameobject *parent = nullptr);
    Acao(QPoint position, QPixmap img, int speed);
    void AcaoMove(QPointF direction=QPointF(1,1));
    float SP=1;
    float HP=20;
    float AT=1;
    double direction_x=1,direction_y=1;
    int isfrozen=0;
    void froze();
    QTimer* frozetimer;
    QTimer* effecttimer;
    QGraphicsColorizeEffect *acaoeffect;
signals:

public slots:
};

#endif // ACAO_H
