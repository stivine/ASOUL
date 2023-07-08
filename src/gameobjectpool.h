#ifndef GAMEOBJECTPOOL_H
#define GAMEOBJECTPOOL_H

#include <QObject>
#include "bullet.h"
#include "acao.h"
#include "gameobject.h"
#include "obstacle.h"
class Acao_follow;
class Drops;
class Gameobjectpool : public QObject
{
public:
    explicit Gameobjectpool(QObject *parent = nullptr);
    static Gameobjectpool* instance;
    static Gameobjectpool* Instance(){
        if(instance==nullptr){
            return instance=new Gameobjectpool;
        }
        return instance;
    }
    void Init();
    Gameobject* GetgameObject(int type);

    QList<Bullet*> BulletPool;
    QList<Acao*> AcaoPool;
    QList<Acao_follow*>Acao_followpool;
    QList<Drops*>Dropspool;
    //对象回收
    void Recovery(Gameobject* obj);
    void Clear();
    ~Gameobjectpool();

    void Acao_longrangebulletshoot();
};

#endif // GAMEOBJECTPOOL_H
