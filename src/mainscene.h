#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "myrole.h"
#include "bullet.h"
#include "acao.h"
#include "info.h"
#include "widget.h"
#include "gameobject.h"
#include "gameobjectpool.h"
#include "drops.h"
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QPixmap>
#include <QKeyEvent>
#include <QList>
#include <QTimer>
#include <QDialog>
#include <QRandomGenerator>
#include <QStackedWidget>
#include <QMediaPlayer>
#include <QSound>
#include <QtMath>
#include <QRadioButton>
#include <QButtonGroup>
#include <QBoxLayout>
#include <QFile>
#include <QListWidget>
#include <QFileDialog>
#include <QDateTime>
#include <QGraphicsItemAnimation>
#include <QGraphicsColorizeEffect>

#define WINDOWSW 1900
#define WINDOWSH 1180
#define ACAOHP 2
static int face=0;//随时记录主角的朝向
static int ispause=0;
static int scene=0;//随时记录用户位置
static int issuicide=0;
enum locate{
    ingame=0,
    inglobal=1,
    inshop,
    ingameover
};

namespace Ui {
class Info;
}


class Mainscene : public QWidget
{
    Q_OBJECT
private:
    QPixmap pix_diana,pix2_diana,pix3_diana,pix4_diana,pix_ava,pix2_ava,pix3_ava,pix4_ava;
    //人物、武器种类
    int Roletype;
    int MainRoletype;
    int Weapontype;
    int Ava_attack_sp=3000;
    //局内强化等级
    int AT_level=1;
    int SP_level=1;
    int HP_level=1;
    int ATSP_level=1;
    //经验值
    int Exp=0;
    int Maxexp=2;
    int Level=1;
    //局内怪物数量
    int acaonumber;
    int acao_follownumber;
    //游戏时长（秒为单位）
    QTimer* Gametimer;
    int gametime=0;
    //信息更新
    QTimer* infoupdatetimer;
public:
    explicit Mainscene(QWidget *parent = nullptr,int x=DIANA);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void Rolemove();
    void mainInit();
    void timerInit();
    Ui::Info *ui_info;
    QGraphicsView Mainview;
    QGraphicsScene* Gamescene;
    QGraphicsPixmapItem Mainbackground;
    Obstacle obstacle[2];
    Myrole Role;
    QList<int> keylist;
    QTimer* Rolemovetimer;
    QTimer* Bulletshoottimer=nullptr;
    void Bulletshoot();
    QList<Bullet*> bulletlist;
    QTimer* Bulletmovetimer;
    QTimer* Acaoshoottimer;
    QTimer* Acaomovetimer;
    void Acaoshoot();
    QList<Acao*> acaolist;
    //碰撞相关
    QTimer* Collisiontimer;
    void Collision();
    //敌方单位相关
    QTimer* Acaoattacktimer;
    QList<Acao_follow*> acao_followlist;
    QTimer* Acao_followshoottimer;
    void Acao_followshoot();
    void gameover();
    QGraphicsScene Gameoverscene;
    QGraphicsPixmapItem Gameoverbackground;

    //向晚攻击
    QTimer* Avaattacktimer;

    //暂停与恢复
    void pause();
    void restart();

    //掉落物
    void generate_drop(qreal x,qreal y);
    QList<Drops*> dropslist;

    //全局属性
    int global_coin_number=10000;
    int global_AT_level=1;
    int global_SP_level=1;
    int global_HP_level=1;
    int global_Ava_level=1;
    int global_Diana_level=1;
    int global_Bella_level=1;
    int global_Eileen_level=1;
    int global_GC_level=1;
    //全局设置相关界面
    void global_ui_init();
    void newgame();
    QGraphicsScene Globalscene;
    QGraphicsPixmapItem Globalbackground;
    QGraphicsPixmapItem Shopbackground;
    QPushButton* continue_button=nullptr;
    QPushButton* shop_button=nullptr;
    QPushButton* newgame_button=nullptr;

    //商店界面
    QGraphicsPixmapItem* ava_pro=nullptr;
    QGraphicsPixmapItem* diana_pro=nullptr;
    QGraphicsPixmapItem* bella_pro=nullptr;
    QGraphicsPixmapItem* eileen_pro=nullptr;
    void shop();
    QGraphicsScene Shopscene;
    void shophide();
    QPushButton* button_diana_buy=nullptr;
    QPushButton* button_ava_buy=nullptr;
    QPushButton* button_bella_buy=nullptr;
    QPushButton* button_eileen_buy=nullptr;

    //武器全局

    QPushButton* button_diana_uprade=nullptr;
    QPushButton* button_ava_uprade=nullptr;
    QPushButton* button_bella_uprade=nullptr;
    QPushButton* button_eileen_uprade=nullptr;
    void global_diana_control();
    void global_ava_control();
    void global_bella_control();
    void global_eileen_control();

    int have_ava=0;
    int have_diana=0;
    int have_bella=0;
    int have_eileen=0;
    double calcDistance(double x1, double y1, double x2, double y2)
    {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }
    void global_label_AT_control();
    void global_label_SP_control();
    void global_label_HP_control();
    void global_label_GC_control();

    void revive_ava();
    void revive_diana();
    void revive_eileen();
    void revive_bella();
    void Weapon_Ava_Init();

    void save();
    void load();
    void suicide();
    void loadGenerateAcao();
    QGraphicsPixmapItem* pause_item;
    QPushButton* suicide_button;
    QPushButton* save_button;
    void globalLoad();
    QPushButton* load_button=nullptr;

    //音效
    QMediaPlayer* ava_attack_sound=nullptr;
    QMediaPlayer* ava_pain_sound=nullptr;
    QMediaPlayer* ava_buy_sound=nullptr;
    QMediaPlayer* diana_attack_sound=nullptr;
    QMediaPlayer* diana_pain_sound=nullptr;
    QMediaPlayer* diana_buy_sound=nullptr;
    QMediaPlayer* bella_attack_sound=nullptr;
    QMediaPlayer* bella_pain_sound=nullptr;
    QMediaPlayer* bella_buy_sound=nullptr;
    QMediaPlayer* eileen_attack_sound=nullptr;
    QMediaPlayer* eileen_pain_sound=nullptr;
    QMediaPlayer* eileen_buy_sound=nullptr;
    QMediaPlaylist *sound_list_ava_attack;
    QMediaPlaylist *sound_list_ava_pain;
    QMediaPlaylist *sound_list_diana_attack;
    QMediaPlaylist *sound_list_diana_pain;

    //攻击受伤效果
    QGraphicsColorizeEffect *myeffect;
    void roleEffect();
    void acaoEffect(Acao* acao);
    QTimer* role_effect_timer;

signals:

public slots:


};


#endif // MAINSCENE_H
