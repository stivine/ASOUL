#ifndef ACAO_FOLLOW_H
#define ACAO_FOLLOW_H

#include "acao.h"
#include "bullet.h"
#include "gameobjectpool.h"

class Acao_follow:public Acao
{
public:
    explicit Acao_follow(Gameobject *parent = nullptr);
    Acao_follow(QPoint position, QPixmap img, int speed);
    int islongrange;
    QTimer* Acao_longrangeshoottimer;
};

#endif // ACAO_FOLLOW_H
