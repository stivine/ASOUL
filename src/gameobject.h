#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Gameobject : public QGraphicsPixmapItem,public QObject
{
public:
    enum Objecttype{
        MYROLE,
        ACAO,
        BULLET,
        ACAO_FOLLOW,
        OBSTACLE,
        DROPS
    };
    explicit Gameobject(QGraphicsPixmapItem *parent = nullptr);
    int type;
    void Gameobjectdelete(QGraphicsScene *scene);
    bool isItemInScene(QGraphicsScene *scene, QGraphicsItem *item)
    {
        QRectF sceneRect = scene->itemsBoundingRect();
        return sceneRect.contains(item->boundingRect().translated(item->pos()));
    }
};

#endif // GAMEOBJECT_H
