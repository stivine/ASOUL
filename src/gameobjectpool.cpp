#include "gameobjectpool.h"
#include <QDebug>
#include "acao_follow.h"
#include "drops.h"
Gameobjectpool* Gameobjectpool:: instance = nullptr;
Gameobjectpool::Gameobjectpool(QObject *parent) : QObject(parent)
{

}

void Gameobjectpool::Init()
{
    for(int i=0;i<80;i++){
        Bullet* bullet=new Bullet();
        BulletPool.append(bullet);
    }
    for(int i=0;i<500;i++){
        Acao* acao=new Acao();
        AcaoPool.append(acao);
    }
    for(int i=0;i<500;i++){
        Acao_follow* acao_follow=new Acao_follow();
        Acao_followpool.append(acao_follow);
    }
    for(int i=0;i<50;i++){
        Drops* drop=new Drops();
        Dropspool.append(drop);
    }
}

Gameobject *Gameobjectpool::GetgameObject(int type)
{
    switch (type) {
        case Gameobject::BULLET:{
            Bullet* bullet = BulletPool.first();
            BulletPool.pop_front();
            return bullet;}
    case Gameobject::ACAO:{
        Acao* acao=AcaoPool.first();
        AcaoPool.pop_front();
        return acao;
    }
    case Gameobject::ACAO_FOLLOW:{
        Acao_follow* acao_follow=Acao_followpool.first();
        Acao_followpool.pop_front();
        return acao_follow;
    }
    case Gameobject::DROPS:{
        Drops* drop=Dropspool.first();
        Dropspool.pop_front();
        return drop;
    }
    }


}

void Gameobjectpool::Recovery(Gameobject *obj)
{
    switch (obj->type) {
    case Gameobject::BULLET:{
        BulletPool.append((Bullet*)obj);
        break;
    }
    case Gameobject::ACAO:{
        qDebug()<<"回收阿草";
        AcaoPool.append((Acao*)obj);
        break;
    }
    case Gameobject::ACAO_FOLLOW:{
        qDebug()<<"回收跟随版阿草";
        Acao_followpool.append((Acao_follow*)obj);
        break;
    }
    case Gameobject::DROPS:{
        qDebug()<<"回收掉落物";
        Dropspool.append((Drops*)obj);
        break;
    }
    }
}

void Gameobjectpool::Clear()
{
    for(auto pBullet:BulletPool){
        delete pBullet;
    }
    for(auto pAcao:AcaoPool){
        delete pAcao;
    }
    for(auto pAcao_follow:Acao_followpool){
        delete pAcao_follow;
    }
    for(auto pDrops:Dropspool){
        delete pDrops;
    }
}

Gameobjectpool::~Gameobjectpool()
{
    Clear();
}
