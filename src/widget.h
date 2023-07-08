#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QToolButton>
#include <QPixmap>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QSound>
enum Roletype{
    DIANA=1,
    AVA,
    EILEEN,
    BELLA
};
#define WINDOWSW 1900
#define WINDOWSH 1180
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QGraphicsView Gameview;
    QGraphicsScene Startscene;
    QGraphicsPixmapItem Startbackground;

    QGraphicsScene Rolechoosescene;
    QGraphicsPixmapItem Rolechoosebackground;


    QMediaPlayer* bgm;
    QMediaPlaylist *bgm_list;
};

#endif // WIDGET_H
