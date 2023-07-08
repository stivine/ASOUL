#include "mainscene.h"
#include "acao_follow.h"
#include "ui_info.h"

//调节游戏的数值平衡时可以随时更改，主要包括升级所需经验、硬币的壁垒
int HP_list[10] = {0, 10, 15, 20, 25, 30};
int SP_list[10] = {0, 2, 3, 5, 8, 9, 10, 12, 15, 18};
int AT_list[10] = {0, 5, 7, 9, 15, 20, 30, 50};
int global_xx_level_list[10] = {0, 5, 10, 20, 40, 60, 100};
int global_weapon_level_list[10] = {0, 5, 10, 20, 40, 60, 100};
int ava_atsp_list[10] = {0, 5, 10, 20, 40, 60, 100};
int diana_atsp_list[10] = {0, 5, 10, 20, 40, 60, 100};
int global_getcoin_list[10]={0,1,2,3,4,5,6,7,8,9};
int Exp_list[10]={0,2,4,8,15,30,50,100,200};


Mainscene::Mainscene(QWidget *parent, int x) : QWidget(parent), Role(nullptr), Roletype(x), Weapontype(x) {

    //基本游戏元素初始化
    mainInit();

    //ui界面设置
    this->ui_info = new Ui::Info();
    ui_info->setupUi(this);
    ui_info->Expbar->setValue(0);
    int *Exp_p = &Exp;
    int *Level_p = &Level;
    QPixmap coinimg(":/img/coin.png");
    coinimg.scaled(30, 30);
    ui_info->coin_img->setPixmap(coinimg);
    ui_info->coin_number->setText(QString::number(global_coin_number));
    ui_info->coin_number->setStyleSheet("color:red");
    ui_info->levelNumber->display(Level);
    infoupdatetimer = new QTimer();
    infoupdatetimer->start(10);
    connect(infoupdatetimer, &QTimer::timeout, [=]() {
        if (*Exp_p >= Maxexp) {

            qDebug() << "升级了！！";
            *Exp_p = 0;
            (*Level_p)++;
            Maxexp=Exp_list[*Level_p];
            ui_info->levelNumber->display(Level);
            QDialog *upgradeDialog = new QDialog(this);
            upgradeDialog->setWindowTitle("升级");
            upgradeDialog->setFixedSize(QSize(700, 400));
            QLabel *label = new QLabel("恭喜您升级了！", upgradeDialog);
            label->setAlignment(Qt::AlignCenter);
            int temp = QRandomGenerator::global()->bounded(0, 4);
            int posy = 0;
            QPushButton AT_levelupbutton("升级攻击力");
            QPushButton SP_levelupbutton("升级敏捷度");
            QPushButton HP_levelupbutton("升级生命力");
            QPushButton ATSP_levelupbutton("升级攻击速率");
            AT_levelupbutton.setFont(QFont("Aa新华霜剑体",20));
            AT_levelupbutton.setIcon(QIcon(":/img/icon_diana.png"));
            AT_levelupbutton.setIconSize(QSize(75,75));
            SP_levelupbutton.setFont(QFont("Aa新华霜剑体",20));
            SP_levelupbutton.setIcon(QIcon(":/img/icon_eileen.png"));
            SP_levelupbutton.setIconSize(QSize(75,75));
            HP_levelupbutton.setFont(QFont("Aa新华霜剑体",20));
            HP_levelupbutton.setIcon(QIcon(":/img/icon_bella.png"));
            HP_levelupbutton.setIconSize(QSize(75,75));
            ATSP_levelupbutton.setFont(QFont("Aa新华霜剑体",20));
            ATSP_levelupbutton.setIcon(QIcon(":/img/icon_ava.png"));
            ATSP_levelupbutton.setIconSize(QSize(75,75));


            if (temp != 0) {

                AT_levelupbutton.setParent(upgradeDialog);
                AT_levelupbutton.move(0, posy);
                posy += 100;
                connect(&AT_levelupbutton, &QPushButton::clicked, [=]() {
                    AT_level++;
                    upgradeDialog->done(QDialog::Accepted);
                    Role.AT = AT_list[AT_level];
                });
            }
            if (temp != 1) {
                HP_levelupbutton.setParent(upgradeDialog);
                HP_levelupbutton.move(0, posy);
                posy += 100;
                connect(&HP_levelupbutton, &QPushButton::clicked, [=]() {
                    HP_level++;
                    upgradeDialog->done(QDialog::Accepted);
                    Role.HP = Role.HP_max = HP_list[HP_level];

                });
            }
            if (temp != 2) {
                SP_levelupbutton.setParent(upgradeDialog);
                SP_levelupbutton.move(0, posy);
                posy += 100;
                connect(&SP_levelupbutton, &QPushButton::clicked, [=]() {
                    SP_level++;
                    upgradeDialog->done(QDialog::Accepted);
                    Role.SP = SP_list[SP_level];
                });
            }

            if (temp != 3) {
                ATSP_levelupbutton.move(0, posy);
                posy += 100;
                ATSP_levelupbutton.setParent(upgradeDialog);
                connect(&ATSP_levelupbutton, &QPushButton::clicked, [=]() {
                    ATSP_level++;
                    upgradeDialog->done(QDialog::Accepted);
                    switch (Roletype) {
                        case DIANA:
                            Role.ATSP = diana_atsp_list[ATSP_level];

                            break;
                        case AVA:
                            Role.ATSP = ava_atsp_list[ATSP_level];
                            Avaattacktimer->stop();
                            Avaattacktimer->start(Role.ATSP);
                            break;
                    }

                });
            }
            pause();
            ispause = 1;
            // 在升级对话框中添加控件...
            upgradeDialog->exec();
            restart();
            ispause = 0;
        }
        ui_info->Expbar->setValue(Exp * 1.0 / Maxexp * 100);
        QString text_AT_base = "攻击力：Lv.";
        QString text_AT_value = QString::number(AT_level);
        QString text_AT = text_AT_base + text_AT_value;
        ui_info->ATlevel_label->setText(text_AT);
        ui_info->ATlevel_label->setStyleSheet("color:red;");
        QString text_HP_base = "生命力：Lv.";
        QString text_HP_value = QString::number(HP_level);
        QString text_HP = text_HP_base + text_HP_value;
        ui_info->HPlevel_label->setText(text_HP);
        ui_info->HPlevel_label->setStyleSheet("color:red;");
        QString text_SP_base = "敏捷度：Lv.";
        QString text_SP_value = QString::number(SP_level);
        QString text_SP = text_SP_base + text_SP_value;
        ui_info->SPlevel_label->setText(text_SP);
        ui_info->SPlevel_label->setStyleSheet("color:red;");
        QString text_ATSP_base = "攻击速度：Lv.";
        QString text_ATSP_value = QString::number(ATSP_level);
        QString text_ATSP = text_ATSP_base + text_ATSP_value;
        ui_info->ATSPlevel_label->setText(text_ATSP);
        ui_info->ATSPlevel_label->setStyleSheet("color:red;");
    });
    shophide();

    timerInit();




    //敌人移动定时器
    Acaomovetimer = new QTimer(this);
    Acaomovetimer->start(10);
    connect(Acaomovetimer, &QTimer::timeout, [=]() {
        for (auto acao: acaolist) {
            if (acao->HP <= 0) {
                acao->HP = ACAOHP;
                acao->Gameobjectdelete(Gamescene);
                if (acaolist.contains(acao))acaolist.removeOne(acao);
                (*Exp_p)++;
                generate_drop(acao->x(), acao->y());
            }
            if (acao->x() >= WINDOWSW || acao->x() <= 0) {
                acao->direction_x = -acao->direction_x;
            }
            if (acao->y() >= WINDOWSH || acao->y() <= 0) {
                acao->direction_y = -acao->direction_y;
            }
            acao->AcaoMove(QPointF(acao->direction_x, acao->direction_y));
        }
        for (auto acao_follow: acao_followlist) {
            if (acao_follow->HP <= 0) {
                acao_follow->HP = ACAOHP;
                if (acao_follow->islongrange)acao_follow->Acao_longrangeshoottimer->stop();
                acao_follow->Gameobjectdelete(Gamescene);
                if (acao_followlist.contains(acao_follow))acao_followlist.removeOne(acao_follow);
                (*Exp_p)++;
                generate_drop(acao_follow->x(), acao_follow->y());
            }
            double a = Role.x() - acao_follow->x();
            double b = Role.y() - acao_follow->y();
            double l = sqrt(a * a + b * b);
            acao_follow->direction_x = a / l;
            acao_follow->direction_y = b / l;
            acao_follow->Acao_follow::AcaoMove(QPointF(acao_follow->direction_x, 0));
            for (int i = 0; i < 2; i++) {
                if (acao_follow->collidesWithItem(&obstacle[i])) {
                    acao_follow->Acao_follow::AcaoMove(QPointF(-(acao_follow->direction_x), 0));
                }
            }
            acao_follow->Acao_follow::AcaoMove(QPointF(0, acao_follow->direction_y));
            for (int i = 0; i < 2; i++) {
                if (acao_follow->collidesWithItem(&obstacle[i])) {
                    acao_follow->Acao_follow::AcaoMove(QPointF(0, -(acao_follow->direction_y)));
                }
            }

        }
    });


    //子弹发射定时器
    if (Roletype == DIANA) {
        Bulletshoottimer = new QTimer(this);
        Bulletshoottimer->start(1000);
        connect(Bulletshoottimer, &QTimer::timeout, this, &Mainscene::Bulletshoot);
    }

    //子弹移动控制

    connect(Bulletmovetimer, &QTimer::timeout, [=]() {
        for (auto bullet: bulletlist) {
            if ((bullet->direction == 0 && bullet->x() > bullet->initial_x + 500) ||
                (bullet->direction == 2 && bullet->x() < bullet->initial_x - 500) ||
                (bullet->direction == 3 && bullet->y() > bullet->initial_y + 500) ||
                (bullet->direction == 4 && bullet->y() < bullet->initial_y - 500) ||
                (bullet->direction == 5 && (bullet->x() > WINDOWSW || bullet->y() > WINDOWSH)) ||
                bullet->collidesWithItem(&obstacle[0]) ||
                bullet->collidesWithItem(&obstacle[1])
                    ) {
                bullet->Gameobjectdelete(Gamescene);
                if (bulletlist.contains(bullet))bulletlist.removeOne(bullet);

            }
            switch (bullet->direction) {
                case 0:
                    bullet->BulletMove(QPoint(1, 0));
                    break;
                case 2:
                    bullet->BulletMove(QPoint(-1, 0));
                    break;
                case 3:
                    bullet->BulletMove(QPoint(0, 1));
                    break;
                case 4:
                    bullet->BulletMove(QPoint(0, -1));
                    break;
                case 5: {
                    bullet->BulletMove(bullet->acao_longrangedirection_x, bullet->acao_longrangedirection_y);
                    break;
                }
            }
        }

    });




    //向晚武器
    if (Roletype == AVA) {
        Weapon_Ava_Init();
    }



    //碰撞检测定时器
    Collisiontimer = new QTimer(this);
    Collisiontimer->start(5);
    connect(Collisiontimer, &QTimer::timeout, [=]() {
        Collision();
    });
    //敌方近战攻击
    Acaoattacktimer = new QTimer(this);
    Acaoattacktimer->start(1000);
    connect(Acaoattacktimer, &QTimer::timeout, [=]() {
        for (auto acao: acaolist) {
            if (acao->collidesWithItem(&Role)) {
                Role.HP -= acao->AT;
                switch (Roletype) {
                    case DIANA: {
                        diana_pain_sound->play();
                        break;
                    }
                    case AVA: {
                        ava_pain_sound->play();
                        break;
                    }
                }
                roleEffect();
            }
        }
        for (auto acao_follow: acao_followlist) {
            if (acao_follow->collidesWithItem(&Role)) {
                Role.HP -= acao_follow->AT;
                switch (Roletype) {
                    case DIANA: {
                        diana_pain_sound->play();
                        break;
                    }
                    case AVA: {
                        ava_pain_sound->play();
                        break;
                    }
                }
                roleEffect();
            }
        }
    });


}

void Mainscene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W: {
            keylist.append(event->key());
            break;
        }
        case Qt::Key_A: {
            keylist.append(event->key());
            break;
        }
        case Qt::Key_S: {
            keylist.append(event->key());
            break;
        }
        case Qt::Key_D: {
            keylist.append(event->key());
            break;
        }
        case Qt::Key_Escape: {
            if (scene == ingame) {
                if (!ispause) {
                    pause();
                    ispause = 1;
                    //暂停item（按esc恢复游戏）、自杀、存档
                    pause_item = new QGraphicsPixmapItem(QPixmap(":/img/pause.png"));
                    pause_item->setScale(1.8);
                    Gamescene->addItem(pause_item);
                    pause_item->setPos(WINDOWSW / 2 - pause_item->pixmap().width() * pause_item->scale() / 2,
                                       WINDOWSH / 2 - pause_item->pixmap().height() * pause_item->scale() / 2);
                    save_button = new QPushButton("存档");
                    save_button->setParent(this);
                    save_button->move(800, 400);
                    save_button->setFixedSize(300, 100);
                    save_button->show();
                    save_button->setIcon(QIcon(":/img/icon_ava.png"));
                    save_button->setIconSize(QSize(90,100));
                    save_button->setFont(QFont("Aa新华霜剑体",20));
                    suicide_button = new QPushButton("结束本局");
                    suicide_button->setParent(this);
                    suicide_button->move(800, 600);
                    suicide_button->setFixedSize(300, 100);
                    suicide_button->show();
                    suicide_button->setIcon(QIcon(":/img/icon6.gif"));
                    suicide_button->setIconSize(QSize(100,100));
                    suicide_button->setFont(QFont("Aa新华霜剑体",20));
                    connect(save_button, &QPushButton::clicked, this, &Mainscene::save);
                    connect(suicide_button, &QPushButton::clicked, this, &Mainscene::suicide);
                } else {
                    Gamescene->removeItem(pause_item);
                    if (pause_item)delete pause_item;
                    if (save_button)delete save_button;
                    if (suicide_button)delete suicide_button;
                    restart();
                    ispause = 0;
                }
            }
            break;
        }
    }
}


void Mainscene::keyReleaseEvent(QKeyEvent *event) {
    if (keylist.contains(event->key())) {
        keylist.removeOne(event->key());
    }
}

void Mainscene::Rolemove() {
//    QPixmap pix,pix2,pix3,pix4;
//    switch (this->Roletype) {
//    case DIANA:{
//        pix.load(":/img/Diana.png");
//        pix = pix.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        pix2.load(":/img/Diana2.png");
//        pix2 = pix2.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        pix3.load(":/img/Diana3.webp");
//        pix3 = pix3.scaled(160, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        pix4.load(":/img/Diana4.webp");
//        pix4 = pix4.scaled(160, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);break;}
//    case AVA:{
//        pix.load(":/img/Ava.webp");
//        pix = pix.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        pix2.load(":/img/Ava2.webp");
//        pix2 = pix2.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        pix3.load(":/img/Ava3.webp");
//        pix3 = pix3.scaled(160, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        pix4.load(":/img/Ava4.webp");
//        pix4 = pix4.scaled(160, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);break;}
//    }

    for (int keyCode: keylist) {
        switch (keyCode) {
            case Qt::Key_W: {
                if (!ispause) {
                    Role.moveBy(0, -(SP_list[SP_level]));
                    for (int i = 0; i < 2; i++) {
                        if (Role.collidesWithItem(&obstacle[i])) {
                            Role.moveBy(0, SP_list[SP_level]);
                        }
                    }
                    if (Roletype == DIANA)Role.setPixmap(pix4_diana);
                    else if (Roletype == AVA)Role.setPixmap(pix4_ava);
                    face = 4;
                }
                break;
            }
            case Qt::Key_A: {
                if (!ispause) {
                    Role.moveBy(-SP_list[SP_level], 0);
                    for (int i = 0; i < 2; i++) {
                        if (Role.collidesWithItem(&obstacle[i])) {
                            Role.moveBy(SP_list[SP_level], 0);
                        }
                    }
                    if (Roletype == DIANA)Role.setPixmap(pix2_diana);
                    else if (Roletype == AVA)Role.setPixmap(pix2_ava);
                    face = 2;
                }
                break;
            }
            case Qt::Key_S: {
                if (!ispause) {
                    Role.moveBy(0, SP_list[SP_level]);
                    for (int i = 0; i < 2; i++) {
                        if (Role.collidesWithItem(&obstacle[i])) {
                            Role.moveBy(0, -SP_list[SP_level]);
                        }
                    }
                    if (Roletype == DIANA)Role.setPixmap(pix3_diana);
                    else if (Roletype == AVA)Role.setPixmap(pix3_ava);
                    face = 3;
                }
                break;
            }
            case Qt::Key_D: {
                if (!ispause) {
                    Role.moveBy(SP_list[SP_level], 0);
                    for (int i = 0; i < 2; i++) {
                        if (Role.collidesWithItem(&obstacle[i])) {
                            Role.moveBy(-SP_list[SP_level], 0);
                        }
                    }
                    if (Roletype == DIANA)Role.setPixmap(pix_diana);
                    else if (Roletype == AVA)Role.setPixmap(pix_ava);
                    face = 0;
                }
                break;
            }
        }
    }
    if (!ispause) {
        if (Role.x() < 0) {
            Role.setX(0);
        }
        if (Role.y() < 0) {
            Role.setY(0);
        }
        if (Role.x() > this->width() - Role.pixmap().width()) {
            Role.setX(this->width() - Role.pixmap().width());
        }
        if (Role.y() > this->height() - Role.pixmap().height()) {
            Role.setY(this->height() - Role.pixmap().height());
        }
    }


}

void Mainscene::mainInit()
{
    Gameobjectpool::Instance()->Init();
    this->setFixedSize(WINDOWSW, WINDOWSH);
    this->setWindowTitle("想让她们活下去的藤君");
    Mainview.setSceneRect(QRect(0, 0, WINDOWSW, WINDOWSH));
    Gamescene = new QGraphicsScene;
    Gamescene->setSceneRect(QRect(0, 0, WINDOWSW, WINDOWSH));
    Mainbackground.setPixmap(QPixmap(":/img/Main.jpg"));
    Gamescene->addItem(&Mainbackground);
    Mainview.setScene(Gamescene);
    Mainview.setParent(this);

    //音效设置
    ava_attack_sound = new QMediaPlayer;

    ava_pain_sound = new QMediaPlayer;
    ava_buy_sound = new QMediaPlayer;
    ava_buy_sound->setMedia(QMediaContent(QUrl("qrc:/bgm/ava_buy_sound.wav")));
    diana_attack_sound = new QMediaPlayer;
    diana_pain_sound = new QMediaPlayer;
    diana_buy_sound = new QMediaPlayer;
    diana_buy_sound->setMedia(QMediaContent(QUrl("qrc:/bgm/diana_buy_sound.wav")));
    bella_attack_sound = new QMediaPlayer;
    bella_attack_sound->setMedia(QMediaContent(QUrl("qrc:/bgm/bella_attack_sound.wav")));
    bella_pain_sound = new QMediaPlayer;
    bella_pain_sound->setMedia(QMediaContent(QUrl("qrc:/bgm/bella_pain_sound.wav")));
    bella_buy_sound = new QMediaPlayer;
    bella_buy_sound->setMedia(QMediaContent(QUrl("qrc:/bgm/bella_buy_sound.wav")));
    eileen_attack_sound = new QMediaPlayer;
    eileen_attack_sound->setMedia(QMediaContent(QUrl("qrc:/bgm/eileen_attack_sound.wav")));
    eileen_pain_sound = new QMediaPlayer;
    eileen_pain_sound->setMedia(QMediaContent(QUrl("qrc:/bgm/eileen_pain_sound.wav")));
    eileen_buy_sound = new QMediaPlayer;
    eileen_buy_sound->setMedia(QMediaContent(QUrl("qrc:/bgm/eileen_buy_sound.wav")));

    sound_list_diana_pain = new QMediaPlaylist(this);
    sound_list_diana_pain->addMedia(QMediaContent(QUrl("qrc:/bgm/diana_pain_sound.wav")));
    sound_list_diana_pain->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    diana_pain_sound->setPlaylist(sound_list_diana_pain);

    sound_list_ava_pain = new QMediaPlaylist(this);
    sound_list_ava_pain->addMedia(QMediaContent(QUrl("qrc:/bgm/ava_pain_sound.wav")));
    sound_list_ava_pain->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    ava_pain_sound->setPlaylist(sound_list_ava_pain);

    sound_list_diana_attack = new QMediaPlaylist(this);
    sound_list_diana_attack->addMedia(QMediaContent(QUrl("qrc:/bgm/diana_attack_sound.wav")));
    sound_list_diana_attack->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    diana_attack_sound->setPlaylist(sound_list_diana_attack);

    sound_list_ava_attack = new QMediaPlaylist(this);
    sound_list_ava_attack->addMedia(QMediaContent(QUrl("qrc:/bgm/ava_attack_sound.wav")));
    sound_list_ava_attack->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    ava_attack_sound->setPlaylist(sound_list_ava_attack);

    //图片加载

    pix_diana.load(":/img/Diana.png");
    pix_diana = pix_diana.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pix2_diana.load(":/img/Diana2.png");
    pix2_diana = pix2_diana.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pix3_diana.load(":/img/Diana3.webp");
    pix3_diana = pix3_diana.scaled(160, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pix4_diana.load(":/img/Diana4.webp");
    pix4_diana = pix4_diana.scaled(160, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    pix_ava.load(":/img/Ava.webp");
    pix_ava = pix_ava.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pix2_ava.load(":/img/Ava2.webp");
    pix2_ava = pix2_ava.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pix3_ava.load(":/img/Ava3.webp");
    pix3_ava = pix3_ava.scaled(160, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pix4_ava.load(":/img/Ava4.webp");
    pix4_ava = pix4_ava.scaled(160, 85, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    //障碍物加载

    QPixmap pix_obs(":/img/obstacle.jpg");
    pix_obs = pix_obs.scaled(150, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    obstacle[0].setPixmap(pix_obs);
    Gamescene->addItem(obstacle);
    obstacle[0].setPos(QPoint(200, 500));

    QPixmap pix_obs2(":/img/obstacle2.png");
    pix_obs2 = pix_obs2.scaled(150, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    obstacle[1].setPixmap(pix_obs2);
    Gamescene->addItem(&obstacle[1]);
    obstacle[1].setPos(QPoint(1000, 500));


    Gametimer = new QTimer(this);
    Gametimer->start(1000);
    connect(Gametimer, &QTimer::timeout, this, [=]() {
        gametime++;
        ui_info->lcdNumber->display(gametime);
    });


    QPixmap pix;
    MainRoletype = Roletype;
    switch (this->Roletype) {
        case DIANA:
            pix.load(":/img/Diana.png");
            break;
        case AVA:
            pix.load(":/img/Ava.webp");
            break;
    }

    pix = pix.scaled(150, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    Role.setPixmap(pix);
    Gamescene->addItem(&Role);
}

void Mainscene::timerInit()
{
    //角色移动定时器
    Rolemovetimer = new QTimer(this);
    Rolemovetimer->start(10);
    connect(Rolemovetimer, &QTimer::timeout, this, &Mainscene::Rolemove);


    //子弹移动定时器
    Bulletmovetimer = new QTimer(this);
    Bulletmovetimer->start(10);


    //敌人发射定时器
    Acaoshoottimer = new QTimer(this);
    Acaoshoottimer->start(5000);
    connect(Acaoshoottimer, &QTimer::timeout, this, &Mainscene::Acaoshoot);

    //追随版敌人发射定时器
    Acao_followshoottimer = new QTimer(this);
    Acao_followshoottimer->start(7000);
    connect(Acao_followshoottimer, &QTimer::timeout, this, &Mainscene::Acao_followshoot);
}

void Mainscene::Bulletshoot() {

    Gameobject *obj = Gameobjectpool::Instance()->GetgameObject(Gameobject::BULLET);
    Bullet *bullet = (Bullet *) obj;
    bullet->setPos(QPoint(Role.x(), Role.y()));
    bullet->setPixmap(QPixmap(":/img/bullet_new.png"));
//    bullet->setScale(0.02);
    bullet->direction = face;
    bullet->initial_x = Role.x();
    bullet->initial_y = Role.y();
    bullet->bullettype = ROLE_BULLET;
    this->Gamescene->addItem(bullet);
    bulletlist.append(bullet);

}

void Mainscene::Acaoshoot() {

    Gameobject *obj = Gameobjectpool::Instance()->GetgameObject(Gameobject::ACAO);
    Acao *acao = (Acao *) obj;
    int x = QRandomGenerator::global()->bounded(0, 4);
    switch (x) {
        case 0: {
            int y = QRandomGenerator::global()->bounded(10, WINDOWSH - 10);
            acao->setPos(WINDOWSW - 10, y);
            break;
        }
        case 1: {
            int y = QRandomGenerator::global()->bounded(10, WINDOWSH - 10);
            acao->setPos(10, y);
            break;
        }
        case 2: {
            int x = QRandomGenerator::global()->bounded(10, WINDOWSW - 10);
            acao->setPos(x, WINDOWSH - 10);
            break;
        }
        case 3: {
            int x = QRandomGenerator::global()->bounded(10, WINDOWSW - 10);
            acao->setPos(x, 10);
            break;
        }
    }
    double u = QRandomGenerator::global()->bounded(1.0);
    double v = QRandomGenerator::global()->bounded(1.0);
    double l = sqrt(pow(u, 2) + pow(v, 2));
    acao->direction_x = u / l;
    acao->direction_y = v / l;

    acao->setPixmap(QPixmap(":/img/Acao.gif"));
    acao->setScale(0.2);


    this->Gamescene->addItem(acao);
    acaolist.append(acao);
}

void Mainscene::Collision() {

    //我方子弹和敌方的碰撞检测
    for (auto bullet: bulletlist) {
        if (Roletype == DIANA) {
            for (int j = 0; j < acaolist.size(); j++) {
                if (bullet->collidesWithItem(acaolist[j]) && bullet->bullettype == ROLE_BULLET) {
                    qDebug() << "打中了！";
                    acaolist[j]->HP -= Role.AT;
                    acaoEffect(acaolist[j]);
                    diana_attack_sound->play();

                    bullet->Gameobjectdelete(Gamescene);
                    if (bulletlist.contains(bullet))bulletlist.removeOne(bullet);
                }
            }
            for (int j = 0; j < acao_followlist.size(); j++) {
                if (bullet->collidesWithItem(acao_followlist[j]) && bullet->bullettype == ROLE_BULLET) {
                    qDebug() << "打中了跟随版阿草！";
                    acao_followlist[j]->HP -= Role.AT;
                    acaoEffect(acao_followlist[j]);
                    diana_attack_sound->play();
                    bullet->Gameobjectdelete(Gamescene);
                    if (bulletlist.contains(bullet))bulletlist.removeOne(bullet);
                }
            }
        }
        //我被远程怪物打了

        if (bullet->collidesWithItem(&Role) && bullet->bullettype == ACAO_LONGRANGE_BULLET) {
            qDebug() << "被击中了！";
            roleEffect();
            Role.HP -= bullet->AT_LONGRANGE;
            switch (Roletype) {
                case DIANA: {
                    diana_pain_sound->play();
                    break;
                }
                case AVA: {
                    ava_pain_sound->play();
                    break;
                }
            }

            bullet->Gameobjectdelete(Gamescene);
            if (bulletlist.contains(bullet))bulletlist.removeOne(bullet);
        }
    }


    //我方死亡检测
    if (Role.HP <= 0) {
        pause();
        if (Roletype != MainRoletype) {
            switch (Roletype) {
                case AVA:
                    have_ava = 0;
                    break;
                case DIANA:
                    have_diana = 0;
                    break;
                case BELLA:
                    have_bella = 0;
                    break;
                case EILEEN:
                    have_eileen = 0;
                    break;
            }
        }
        if (!issuicide) {
            QDialog *reviveDialog = new QDialog(this);
            reviveDialog->setWindowTitle("是否复活");
            reviveDialog->setFixedSize(QSize(700, 400));
            QLabel *label = new QLabel("你的可供复活角色如下", reviveDialog);
            QPushButton revive_ava_button(reviveDialog);
            QPushButton revive_diana_button(reviveDialog);
            QPushButton revive_bella_button(reviveDialog);
            QPushButton revive_eileen_button(reviveDialog);
            revive_ava_button.setText("Ava，上啊！");
            revive_diana_button.setText("Diana，上啊！");
            revive_bella_button.setText("Bella，上啊！");
            revive_eileen_button.setText("Eileen，上啊！");
            revive_ava_button.setIcon(QIcon(":/img/icon_ava.png"));
            revive_ava_button.setIconSize(QSize(100,100));
            revive_ava_button.setFont(QFont("Aa新华霜剑体",20));

            revive_diana_button.setIcon(QIcon(":/img/icon_diana.png"));
            revive_diana_button.setIconSize(QSize(100,100));
            revive_diana_button.setFont(QFont("Aa新华霜剑体",20));

            revive_eileen_button.setIcon(QIcon(":/img/icon_eileen.png"));
            revive_eileen_button.setIconSize(QSize(100,100));
            revive_eileen_button.setFont(QFont("Aa新华霜剑体",20));

            revive_bella_button.setIcon(QIcon(":/img/icon_bella.png"));
            revive_bella_button.setIconSize(QSize(100,100));
            revive_bella_button.setFont(QFont("Aa新华霜剑体",20));
            if ((!have_ava || Roletype == AVA || MainRoletype == AVA))revive_ava_button.setEnabled(0);
            if ((!have_diana || Roletype == DIANA || MainRoletype == DIANA))revive_diana_button.setEnabled(0);
            if ((!have_bella || Roletype == BELLA || MainRoletype == BELLA))revive_bella_button.setEnabled(0);
            if ((!have_eileen || Roletype == EILEEN || MainRoletype == EILEEN))revive_eileen_button.setEnabled(0);
            revive_ava_button.move(0, 75);
            revive_diana_button.move(0, 150);
            revive_bella_button.move(0, 225);
            revive_eileen_button.move(0, 300);
            connect(&revive_ava_button, &QPushButton::clicked, reviveDialog, &QDialog::done);
            connect(&revive_diana_button, &QPushButton::clicked, reviveDialog, &QDialog::done);
            connect(&revive_bella_button, &QPushButton::clicked, reviveDialog, &QDialog::done);
            connect(&revive_eileen_button, &QPushButton::clicked, reviveDialog, &QDialog::done);
            connect(&revive_ava_button, &QPushButton::clicked, this, &Mainscene::revive_ava);
            connect(&revive_diana_button, &QPushButton::clicked, this, &Mainscene::revive_diana);
            connect(&revive_bella_button, &QPushButton::clicked, this, &Mainscene::revive_bella);
            connect(&revive_eileen_button, &QPushButton::clicked, this, &Mainscene::revive_eileen);
            reviveDialog->exec();
        }
        issuicide = 0;
        if (Role.HP <= 0) {
            gameover();
        } else {
            restart();
        }
    }

    //我方血量变化
    ui_info->HPbar->setValue(Role.HP / Role.HP_max * 100);

    //掉落物拾取
    for (auto drops: dropslist) {
        if (drops->collidesWithItem(&Role)) {
            switch (drops->Dropstype) {
                case COIN: {
                    global_coin_number+=global_getcoin_list[global_GC_level];
                    drops->Gameobjectdelete(Gamescene);
                    dropslist.removeOne(drops);
                    ui_info->coin_number->setText(QString::number(global_coin_number));
                    break;
                }
                case HEART: {
                    Role.HP = (Role.HP + 10 > Role.HP_max) ? Role.HP_max : Role.HP + 10;
                    drops->Gameobjectdelete(Gamescene);
                    dropslist.removeOne(drops);
                    break;
                }
            }
        }
    }
}

void Mainscene::Acao_followshoot() {
    Gameobject *obj = Gameobjectpool::Instance()->GetgameObject(Gameobject::ACAO_FOLLOW);
    Acao_follow *acao_follow = (Acao_follow *) obj;
    int x = QRandomGenerator::global()->bounded(0, 4);//这个整数随机数，满足左闭右开
    switch (x) {
        case 0: {
            int y = QRandomGenerator::global()->bounded(10, WINDOWSH - 10);
            acao_follow->setPos(WINDOWSW - 10, y);
            break;
        }
        case 1: {
            int y = QRandomGenerator::global()->bounded(10, WINDOWSH - 10);
            acao_follow->setPos(10, y);
            break;
        }
        case 2: {
            int x = QRandomGenerator::global()->bounded(10, WINDOWSW - 10);
            acao_follow->setPos(x, WINDOWSH - 10);
            break;
        }
        case 3: {
            int x = QRandomGenerator::global()->bounded(10, WINDOWSW - 10);
            acao_follow->setPos(x, 10);
            break;
        }
    }
    acao_follow->setPixmap(QPixmap(":/img/Acao_follow.webp"));
    acao_follow->setScale(0.1);
    if(gametime>20&&gametime<25){
        acao_follow->setPixmap(QPixmap(":/img/acao_boss.webp"));
        acao_follow->setScale(0.5);
        acao_follow->islongrange=0;
    }
    this->Gamescene->addItem(acao_follow);
    acao_followlist.append(acao_follow);
    qDebug() << "发射追随版阿草";

    if (acao_follow->islongrange) {
        acao_follow->Acao_longrangeshoottimer = new QTimer(acao_follow);
        acao_follow->Acao_longrangeshoottimer->start(4000);
        connect(acao_follow->Acao_longrangeshoottimer, &QTimer::timeout, [=]() {
            qDebug() << "敌方远程";
            Gameobject *obj = Gameobjectpool::Instance()->GetgameObject(Gameobject::BULLET);
            Bullet *bullet = (Bullet *) obj;
            bullet->bullettype = ACAO_LONGRANGE_BULLET;
            bullet->setPixmap(QPixmap(":/img/bullet_new.png"));
//            bullet->setScale(0.02);
            bullet->setPos(acao_follow->pos());
            double a = Role.x() - acao_follow->x();
            double b = Role.y() - acao_follow->y();
            double l = sqrt(a * a + b * b);
            bullet->direction = 5;
            bullet->acao_longrangedirection_x = a / l;
            bullet->acao_longrangedirection_y = b / l;
            bullet->AT_LONGRANGE = acao_follow->AT;
            this->Gamescene->addItem(bullet);
            bulletlist.append(bullet);
        });
    }
}

void Mainscene::gameover() {
    //信息相关
    AT_level = 1;
    SP_level = 1;
    HP_level = 1;
    ATSP_level = 1;
    gametime = 0;
    Exp = 0;
    this->ui_info->lcdNumber->display("0");
    this->ui_info->HPbar->hide();
    this->ui_info->Expbar->hide();
    this->ui_info->levellabel->hide();
    this->ui_info->levelNumber->hide();
    this->ui_info->ATlevel_label->hide();
    this->ui_info->ATSPlevel_label->hide();
    this->ui_info->SPlevel_label->hide();
    this->ui_info->HPlevel_label->hide();



    //回收子弹、敌方单位、掉落物
    for (auto bullet: bulletlist) {
        bullet->Gameobjectdelete(Gamescene);
        if (bulletlist.contains(bullet))bulletlist.removeOne(bullet);
    }
    for (auto acao: acaolist) {
        acao->Gameobjectdelete(Gamescene);
        if (acaolist.contains(acao))acaolist.removeOne(acao);
    }
    for (auto acao_follow: acao_followlist) {
        if (acao_follow->islongrange) {
            acao_follow->Acao_longrangeshoottimer->stop();
        }
        acao_follow->Gameobjectdelete(Gamescene);
        if (acao_followlist.contains(acao_follow))acao_followlist.removeOne(acao_follow);
    }
    for (auto drops: dropslist) {
        drops->Gameobjectdelete(Gamescene);
        dropslist.removeOne(drops);
    }
    Rolemovetimer->stop();
    Acao_followshoottimer->stop();
    Acaoshoottimer->stop();
    Collisiontimer->stop();
    Acaomovetimer->stop();
    if (Roletype == DIANA) {
        Bulletshoottimer->stop();
    }
    if (Roletype == AVA) {
        Avaattacktimer->stop();
    }
    Bulletmovetimer->stop();
    Gametimer->stop();

    QPixmap pix(":/img/Gameover.jpg");
    pix = pix.scaled(WINDOWSW, WINDOWSH, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Gameoverbackground.setPixmap(pix);
    Gameoverscene.addItem(&Gameoverbackground);
    Gameoverscene.setSceneRect(QRect(0, 0, WINDOWSW, WINDOWSH));
    Mainview.setScene(&Gameoverscene);

    continue_button = new QPushButton(this);
    continue_button->setText("CONTINUE");
    continue_button->setFixedSize(300, 75);
    continue_button->setFont(QFont("Aa新华霜剑体",20));
    continue_button->setIcon(QIcon(":/img/icon_eileen.png"));
    continue_button->setIconSize(QSize(80,80));
    continue_button->move(WINDOWSW / 2 - continue_button->width() / 2, WINDOWSH - 75);
    continue_button->show();
    connect(continue_button, &QPushButton::clicked, [=]() {
        global_ui_init();
    });
    scene = ingameover;
}

void Mainscene::pause() {
    ispause = 1;
//    Rolemovetimer->stop();
    Acao_followshoottimer->stop();
    Acaoshoottimer->stop();
    Collisiontimer->stop();
    for (auto acao_follow: acao_followlist) {
        if (acao_follow->islongrange)acao_follow->Acao_longrangeshoottimer->stop();
    }
    Acaomovetimer->stop();

    if (Roletype == DIANA) {
        Bulletshoottimer->stop();
    }
    if (Roletype == AVA) {
        Avaattacktimer->stop();
    }
    Bulletmovetimer->stop();
    Gametimer->stop();

    for (auto x: keylist) {
        keylist.removeOne(x);
    }
}

void Mainscene::restart() {
    Rolemovetimer->start(10);
    Acao_followshoottimer->start(3000);
    Acaoshoottimer->start(2000);
    Collisiontimer->start(5);
    Acaomovetimer->start(10);
    //
    if (Roletype == DIANA) {
        if (Bulletshoottimer == nullptr) {
            Bulletshoottimer = new QTimer;
        }
        Bulletshoottimer->start(1000);
        disconnect(Bulletshoottimer, &QTimer::timeout, this, &Mainscene::Bulletshoot);
        connect(Bulletshoottimer, &QTimer::timeout, this, &Mainscene::Bulletshoot);
    }
    if (Roletype == AVA) {
        Weapon_Ava_Init();
    }
    Bulletmovetimer->start(10);
    Gametimer->start(1000);
    for (auto acao_follow: acao_followlist) {
        if (acao_follow->islongrange)acao_follow->Acao_longrangeshoottimer->start(4000);
    }
    ispause = 0;
}

void Mainscene::generate_drop(qreal x, qreal y) {
    int flag = QRandomGenerator::global()->bounded(0, 3);//控制爆率！
    Gameobject *obj = Gameobjectpool::Instance()->GetgameObject(Gameobject::DROPS);
    Drops *drops = (Drops *) obj;
    switch (flag) {
        case 1: {
            qDebug() << "这里应该产生硬币";
            drops->type = Gameobject::DROPS;
            drops->Dropstype = COIN;
            drops->setPixmap(QPixmap(":/img/coin.png"));
            drops->setScale(0.7);
            this->Gamescene->addItem(drops);
            dropslist.append(drops);
            break;
        }
        case 2: {
            qDebug() << "这里应该产生心";
            drops->setPixmap(QPixmap(":/img/heart.png"));
            drops->type = Gameobject::DROPS;
            drops->Dropstype = HEART;
            drops->setScale(0.7);
            this->Gamescene->addItem(drops);
            dropslist.append(drops);
            break;
        }
    }
    drops->setX(x);
    drops->setY(y);
}

void Mainscene::global_ui_init() {
    Mainview.setScene(&Globalscene);
    Globalscene.setSceneRect(QRect(0, 0, WINDOWSW, WINDOWSH));
    Globalbackground.setPixmap(QPixmap(":/img/globalscene_background.png"));
    Globalscene.addItem(&Globalbackground);


    if (scene == ingameover) {
        continue_button->hide();
        ui_info->lcdNumber->hide();
    }
    if (newgame_button == nullptr) {
        newgame_button = new QPushButton(this);
        newgame_button->setText("New Game");
        newgame_button->setIcon(QIcon(":/img/icon4.gif"));
        newgame_button->setIconSize(QSize(120,120));
        newgame_button->setFont(QFont("Aa新华霜剑体",20));
        newgame_button->move(1400, 300);
        newgame_button->setFixedSize(350, 100);
    }
    newgame_button->show();
    if (!shop_button) {
        shop_button = new QPushButton(this);
        shop_button->setText("Shop");
        shop_button->setIcon(QIcon(":/img/icon6.gif"));
        shop_button->setIconSize(QSize(100,100));
        shop_button->setFont(QFont("Aa新华霜剑体",20));
        shop_button->move(1400, 500);
        shop_button->setFixedSize(350, 100);
    }
    shop_button->show();
    if (load_button == nullptr)load_button = new QPushButton(this);
    load_button->setText("Load");
    load_button->setIcon(QIcon(":/img/icon7.gif"));
    load_button->setIconSize(QSize(100,100));
    load_button->setFont(QFont("Aa新华霜剑体",20));
    load_button->move(1400, 700);
    load_button->setFixedSize(350, 100);
    load_button->show();
    Shopscene.setSceneRect(QRect(0, 0, WINDOWSW, WINDOWSH));
    disconnect(newgame_button, &QPushButton::clicked, this, &Mainscene::newgame);
    connect(newgame_button, &QPushButton::clicked, this, &Mainscene::newgame);
    disconnect(shop_button, &QPushButton::clicked, this, &Mainscene::shop);
    connect(shop_button, &QPushButton::clicked, this, &Mainscene::shop);
    connect(load_button, &QPushButton::clicked, this, [=]() {
        newgame();
        pause();
        load();
        restart();
    });
    scene = inglobal;
}

void Mainscene::newgame() {    //数值相关
    if (load_button != nullptr)delete load_button;
    load_button = nullptr;
    Roletype = MainRoletype;
    Role.HP = Role.HP_max = HP_list[1];
    Role.AT = AT_list[1];
    Role.SP = SP_list[1];
    Role.setX(0);
    Role.setY(0);
    face = 0;
    Level = 1;
    scene = ingame;
    //ui相关
    newgame_button->hide();
    shop_button->hide();
    ui_info->HPbar->setValue(Role.HP / Role.HP_max * 100);
    ui_info->HPbar->show();
    ui_info->Expbar->show();
    ui_info->lcdNumber->show();
    ui_info->levellabel->show();
    ui_info->ATlevel_label->show();
    ui_info->ATSPlevel_label->show();
    ui_info->SPlevel_label->show();
    ui_info->HPlevel_label->show();
    ui_info->levelNumber->display(Level);
    ui_info->levelNumber->show();
    //计时器相关
    Rolemovetimer->start(10);
    Acao_followshoottimer->start(3000);
    Acaoshoottimer->start(2000);
    Collisiontimer->start(5);
    Acaomovetimer->start(10);
    if (Roletype == DIANA) {
        Bulletshoottimer->start(1000);
    }
    if (Roletype == AVA) {
        Avaattacktimer->start(Ava_attack_sp);
    }
    Bulletmovetimer->start(10);
    Gametimer->start(1000);
    ispause = 0;
    Mainview.setScene(Gamescene);
}

void Mainscene::shop() {
    scene = inshop;
    Shopscene.setSceneRect(QRect(0, 0, WINDOWSW, WINDOWSH));
    Shopbackground.setPixmap(QPixmap(":/img/shopbackground.png"));
    Shopscene.addItem(&Shopbackground);
    if (load_button != nullptr)delete load_button;
    load_button = nullptr;
    Mainview.setScene(&Shopscene);
    shop_button->hide();
    newgame_button->hide();
    ui_info->label_global->show();
    ui_info->label_globalAT->show();
    ui_info->label_globalSP->show();
    ui_info->label_globalHP->show();
    ui_info->label_global_getcoin->show();
    ui_info->label_globalAT_number->show();
    ui_info->label_globalSP_number->show();
    ui_info->label_globalHP_number->show();
    ui_info->label_global_getcoin_number->show();
    ui_info->button_quit_shop->show();
    ui_info->button_buyAT->show();
    ui_info->button_buySP->show();
    ui_info->button_buyHP->show();
    ui_info->button_buyGC->show();

    if (!ava_pro) {
        ava_pro = new QGraphicsPixmapItem(QPixmap(":/img/avapro.png"));
        ava_pro->setScale(0.2);
        Shopscene.addItem(ava_pro);
    } else {
        ava_pro->show();
    }
    if (!diana_pro) {
        diana_pro = new QGraphicsPixmapItem(QPixmap(":/img/dianapro.png"));
        diana_pro->setScale(0.2);
        diana_pro->moveBy(400, 0);
        Shopscene.addItem(diana_pro);
    } else {
        diana_pro->show();
    }
    if (!bella_pro) {
        bella_pro = new QGraphicsPixmapItem(QPixmap(":/img/bellapro.png"));
        bella_pro->setScale(0.3);
        bella_pro->moveBy(400, 600);
        Shopscene.addItem(bella_pro);
    } else {
        bella_pro->show();
    }
    if (!eileen_pro) {
        eileen_pro = new QGraphicsPixmapItem(QPixmap(":/img/eileenpro.png"));
        eileen_pro->setScale(0.2);
        eileen_pro->moveBy(0, 600);
        Shopscene.addItem(eileen_pro);
    } else {
        eileen_pro->show();
    }

    if (!button_diana_buy) { button_diana_buy = new QPushButton("20 coins"); }
    if (have_diana) { button_diana_buy->setText("你已拥有"); }
    else { button_diana_buy->setText("20 coins"); }
    button_diana_buy->setParent(this);
    button_diana_buy->setFixedSize(100, 100);
    button_diana_buy->move(485, 320);
    button_diana_buy->show();
    connect(button_diana_buy, &QPushButton::clicked, this, [=]() {
        if (global_coin_number >= 20 && !have_diana) {
            global_coin_number -= 20;
            diana_buy_sound->play();
            ui_info->coin_number->setText(QString::number(global_coin_number));
            button_diana_buy->setText("你已拥有");
            button_diana_uprade->setEnabled(1);
            have_diana = 1;
        }
    });

    if (!button_ava_buy) { button_ava_buy = new QPushButton("20 coins"); }
    if (have_ava == 1)button_ava_buy->setText("你已拥有");
    else button_ava_buy->setText("20 coins");
    button_ava_buy->setParent(this);
    button_ava_buy->setFixedSize(100, 100);
    button_ava_buy->move(115, 320);
    button_ava_buy->show();
    connect(button_ava_buy, &QPushButton::clicked, this, [=]() {
        if (global_coin_number >= 20 && !have_ava) {
            global_coin_number -= 20;
            ava_buy_sound->play();
            ui_info->coin_number->setText(QString::number(global_coin_number));
            button_ava_buy->setText("你已拥有");
            button_ava_uprade->setEnabled(1);
            have_ava = 1;
        }
    });


    if (!button_bella_buy) {
        button_bella_buy = new QPushButton("20 coins");
    }
    if (have_bella)button_bella_buy->setText("你已拥有");
    else button_bella_buy->setText("20 coins");
    button_bella_buy->setParent(this);
    button_bella_buy->setFixedSize(100, 100);
    button_bella_buy->move(485, 940);
    button_bella_buy->show();
    connect(button_bella_buy, &QPushButton::clicked, this, [=]() {
        if (global_coin_number >= 20 && !have_bella) {
            global_coin_number -= 20;
            bella_buy_sound->play();
            ui_info->coin_number->setText(QString::number(global_coin_number));
            button_bella_buy->setText("你已拥有");
            button_bella_uprade->setEnabled(1);
            have_bella = 1;
        }
    });

    if (!button_eileen_buy) {
        button_eileen_buy = new QPushButton("20 coins");
    }
    if (have_eileen)button_eileen_buy->setText("你已拥有");
    else button_eileen_buy->setText("20 coins");
    button_eileen_buy->setParent(this);
    button_eileen_buy->setFixedSize(100, 100);
    button_eileen_buy->move(115, 940);
    button_eileen_buy->show();
    connect(button_eileen_buy, &QPushButton::clicked, this, [=]() {
        if (global_coin_number >= 20 && !have_eileen) {
            global_coin_number -= 20;
            ui_info->coin_number->setText(QString::number(global_coin_number));
            button_eileen_buy->setText("你已拥有");
            button_eileen_uprade->setEnabled(1);
            have_eileen = 1;
        }
    });


    //全局属性
    ui_info->label_globalAT_number->setText("Lv." + QString::number(global_AT_level));
    ui_info->label_globalHP_number->setText("Lv." + QString::number(global_HP_level));
    ui_info->label_globalSP_number->setText("Lv." + QString::number(global_SP_level));
    ui_info->label_global_getcoin_number->setText("Lv." + QString::number(global_GC_level));

    disconnect(ui_info->button_buyAT, &QPushButton::clicked, this, &Mainscene::global_label_AT_control);
    disconnect(ui_info->button_buySP, &QPushButton::clicked, this, &Mainscene::global_label_SP_control);
    disconnect(ui_info->button_buyHP, &QPushButton::clicked, this, &Mainscene::global_label_HP_control);
    disconnect(ui_info->button_buyGC, &QPushButton::clicked, this, &Mainscene::global_label_GC_control);

    connect(ui_info->button_buyAT, &QPushButton::clicked, this, &Mainscene::global_label_AT_control);
    connect(ui_info->button_buySP, &QPushButton::clicked, this, &Mainscene::global_label_SP_control);
    connect(ui_info->button_buyHP, &QPushButton::clicked, this, &Mainscene::global_label_HP_control);
    connect(ui_info->button_buyGC, &QPushButton::clicked, this, &Mainscene::global_label_GC_control);
    connect(ui_info->button_quit_shop, &QPushButton::clicked, [=]() {
        shophide();
        button_ava_buy->hide();
        button_diana_buy->hide();
        button_eileen_buy->hide();
        button_bella_buy->hide();
        bella_pro->hide();
        ava_pro->hide();
        diana_pro->hide();
        eileen_pro->hide();
        global_ui_init();
    });


    //武器全局
    button_ava_uprade = new QPushButton("Ava：Lv." + QString::number(global_Ava_level) + "\n" +
                                        QString::number(global_weapon_level_list[global_Ava_level]) + "coins");
    button_ava_uprade->setParent(this);
    button_ava_uprade->move(100, 0);
    button_ava_uprade->show();
    button_diana_uprade = new QPushButton("Diana：Lv." + QString::number(global_Diana_level) + "\n" +
                                          QString::number(global_weapon_level_list[global_Diana_level]) + "coins");
    button_diana_uprade->setParent(this);
    button_diana_uprade->move(500, 0);
    button_diana_uprade->show();
    button_bella_uprade = new QPushButton("Bella：Lv." + QString::number(global_Bella_level) + "\n" +
                                          QString::number(global_weapon_level_list[global_Bella_level]) + "coins");
    button_bella_uprade->setParent(this);
    button_bella_uprade->move(500, 600);
    button_bella_uprade->show();
    button_eileen_uprade = new QPushButton("Eileen：Lv." + QString::number(global_Eileen_level) + "\n" +
                                           QString::number(global_weapon_level_list[global_Eileen_level]) + "coins");
    button_eileen_uprade->setParent(this);
    button_eileen_uprade->move(100, 600);
    button_eileen_uprade->show();
    if (!have_ava) { button_ava_uprade->setEnabled(0); }
    if (!have_diana) { button_diana_uprade->setEnabled(0); }
    if (!have_bella) { button_bella_uprade->setEnabled(0); }
    if (!have_eileen) { button_eileen_uprade->setEnabled(0); }
    connect(button_ava_uprade, &QPushButton::clicked, this, &Mainscene::global_ava_control);
    connect(button_diana_uprade, &QPushButton::clicked, this, &Mainscene::global_diana_control);
    connect(button_bella_uprade, &QPushButton::clicked, this, &Mainscene::global_bella_control);
    connect(button_eileen_uprade, &QPushButton::clicked, this, &Mainscene::global_eileen_control);


}

void Mainscene::shophide() {
    //武器全局
    delete button_ava_uprade;
    button_ava_uprade = nullptr;
    delete button_diana_uprade;
    button_diana_uprade = nullptr;
    delete button_bella_uprade;
    button_bella_uprade = nullptr;
    delete button_eileen_uprade;
    button_eileen_uprade = nullptr;

    ui_info->label_global->hide();
    ui_info->label_globalAT->hide();
    ui_info->label_globalSP->hide();
    ui_info->label_globalHP->hide();
    ui_info->label_global_getcoin->hide();
    ui_info->label_globalAT_number->hide();
    ui_info->label_globalSP_number->hide();
    ui_info->label_globalHP_number->hide();
    ui_info->label_global_getcoin_number->hide();
    ui_info->button_quit_shop->hide();
    ui_info->button_buyAT->hide();
    ui_info->button_buySP->hide();
    ui_info->button_buyHP->hide();
    ui_info->button_buyGC->hide();
}

void Mainscene::global_diana_control() {
    if (global_coin_number >= global_weapon_level_list[global_Diana_level]) {
        global_coin_number -= global_weapon_level_list[global_Diana_level];
        ui_info->coin_number->setText(QString::number(global_coin_number));
        global_Diana_level++;
        button_diana_uprade->setText("Diana：Lv." + QString::number(global_Diana_level) + "\n" +
                                     QString::number(global_weapon_level_list[global_Diana_level]) + "coins");
    }
}

void Mainscene::global_ava_control() {
    if (global_coin_number >= global_weapon_level_list[global_Ava_level]) {
        global_coin_number -= global_weapon_level_list[global_Ava_level];
        ui_info->coin_number->setText(QString::number(global_coin_number));
        global_Ava_level++;
        button_ava_uprade->setText("Ava：Lv." + QString::number(global_Ava_level) + "\n" +
                                   QString::number(global_weapon_level_list[global_Ava_level]) + "coins");
    }
}

void Mainscene::global_bella_control() {
    if (global_coin_number >= global_weapon_level_list[global_Bella_level]) {
        global_coin_number -= global_weapon_level_list[global_Bella_level];
        ui_info->coin_number->setText(QString::number(global_coin_number));
        global_Bella_level++;
        button_bella_uprade->setText("Bella：Lv." + QString::number(global_Bella_level) + "\n" +
                                     QString::number(global_weapon_level_list[global_Bella_level]) + "coins");
    }
}

void Mainscene::global_eileen_control() {
    if (global_coin_number >= global_weapon_level_list[global_Eileen_level]) {
        global_coin_number -= global_weapon_level_list[global_Eileen_level];
        ui_info->coin_number->setText(QString::number(global_coin_number));
        global_Eileen_level++;
        button_eileen_uprade->setText("Eileen：Lv." + QString::number(global_Eileen_level) + "\n" +
                                      QString::number(global_weapon_level_list[global_Eileen_level]) + "coins");
    }
}

void Mainscene::global_label_AT_control() {
    if (global_coin_number - global_xx_level_list[global_AT_level] >= 0) {
        global_coin_number -= global_xx_level_list[global_AT_level];
        global_AT_level++;
        ui_info->label_globalAT_number->setText("Lv." + QString::number(global_AT_level));
        ui_info->coin_number->setText(QString::number(global_coin_number));
        ui_info->button_buyAT->setText(QString::number(global_xx_level_list[global_AT_level]) + "coins");
    }
}

void Mainscene::global_label_SP_control() {
    if (global_coin_number - global_xx_level_list[global_SP_level] >= 0) {
        global_coin_number -= global_xx_level_list[global_SP_level];
        global_SP_level++;
        ui_info->label_globalSP_number->setText("Lv." + QString::number(global_SP_level));
        ui_info->coin_number->setText(QString::number(global_coin_number));
        ui_info->button_buySP->setText(QString::number(global_xx_level_list[global_SP_level]) + "coins");
    }
}

void Mainscene::global_label_HP_control() {
    if (global_coin_number - global_xx_level_list[global_HP_level] >= 0) {
        global_coin_number -= global_xx_level_list[global_HP_level];
        global_HP_level++;
        ui_info->label_globalHP_number->setText("Lv." + QString::number(global_HP_level));
        ui_info->coin_number->setText(QString::number(global_coin_number));
        ui_info->button_buyHP->setText(QString::number(global_xx_level_list[global_HP_level]) + "coins");
    }
}

void Mainscene::global_label_GC_control()
{
    if (global_coin_number - global_xx_level_list[global_GC_level] >= 0) {
        global_coin_number -= global_xx_level_list[global_GC_level];
        global_GC_level++;
        ui_info->label_global_getcoin_number->setText("Lv." + QString::number(global_GC_level));
        ui_info->coin_number->setText(QString::number(global_coin_number));
        ui_info->button_buyGC->setText(QString::number(global_xx_level_list[global_GC_level]) + "coins");
    }

}


void Mainscene::revive_ava() {
    Roletype = Weapontype = AVA;
    Role.HP = Role.HP_max = HP_list[HP_level];
}

void Mainscene::revive_diana() {
    Roletype = Weapontype = DIANA;
    Role.HP = Role.HP_max = HP_list[HP_level];
}

void Mainscene::revive_bella() {
    Roletype = Weapontype = BELLA;
    Role.HP = Role.HP_max = HP_list[HP_level];
}

void Mainscene::revive_eileen() {
    Roletype = Weapontype = EILEEN;
    Role.HP = Role.HP_max = HP_list[HP_level];
}

void Mainscene::Weapon_Ava_Init() {

    Avaattacktimer = new QTimer(this);
    Avaattacktimer->start(Ava_attack_sp);

    connect(Avaattacktimer, &QTimer::timeout, [=]() {
        qDebug() << "大头攻击";

        for (auto acao: acaolist) {
            double dis = calcDistance(Role.x(), Role.y(), acao->pos().x(), acao->pos().y());
            if (dis < 130) {
                acao->HP -= AT_list[AT_level]+global_AT_level+global_Ava_level;
                acao->froze();
                acaoEffect(acao);
                ava_attack_sound->play();
                qDebug() << "我被我爹打中了";
            }
        }

        for (auto acao: acao_followlist) {
            double dis = calcDistance(Role.x(), Role.y(), acao->pos().x(), acao->pos().y());
//face==2&&acao->y()>Role.y()-5
//&&acao->y()<Role.y()+Role.pixmap().height()+5
//&&acao->x()<Role.x()-10
//&&acao->x()+acao->pixmap().width()>Role.x()
//&&(acao->pos())
//dis<100&&(
//(face==2)&&(acao->y()>Role.y()-acao->pixmap().height())&&(acao->y()<Role.y()+Role.pixmap().height()-acao->pixmap().height()/2))
//)
            if (dis < 130) {
                acao->HP -= AT_list[AT_level]+global_AT_level+global_Ava_level;
                acao->froze();
                acaoEffect(acao);
                ava_attack_sound->play();
                qDebug() << "被我跌打中了";
            }
        }
    });
}

void Mainscene::save() {
    QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss") + ".txt";
    QString filePath = QFileDialog::getSaveFileName(this, "保存存档", fileName);

    if (!filePath.isEmpty()) {
        // 组织需要存储的数据
        QString text = QString(
                "%1\r\n%2\r\n%3\r\n%4\r\n%5\r\n%6\r\n%7\r\n%8\r\n%9\r\n%10\r\n%11\r\n%12\r\n%13\r\n%14\r\n%15\r\n%16\r\n%17\r\n%18\r\n%19"
                "\r\n%20\r\n%21\r\n%22\r\n%23\r\n%24\r\n%25\r\n%26")
                .arg(scene)
                .arg(Roletype).arg(MainRoletype).arg(have_diana).arg(have_ava)
                .arg(have_eileen).arg(have_bella).arg(global_Diana_level)
                .arg(global_Ava_level).arg(global_Eileen_level).arg(global_Bella_level)
                .arg(global_AT_level).arg(global_SP_level).arg(global_HP_level).arg(global_coin_number)
                .arg(AT_level).arg(SP_level).arg(HP_level).arg(Exp)
                .arg(Level).arg(gametime).arg(acaolist.size()).arg(acao_followlist.size()).arg(Role.HP)
                .arg(Role.x()).arg(Role.y());
        // 创建并打开文件
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            // 将数据写入文件
            QTextStream out(&file);
            out << text;
        }
    }
}

void Mainscene::load() {

    QString Path = QFileDialog::getOpenFileName(this, "打开存档", "E:\\QTDocuments\\Tengjun\\save");
    qDebug() << Path << endl;
    QFile file(Path);
    file.open(QIODevice::Truncate | QIODevice::ReadOnly);
    QByteArray data_byte = file.readAll();
    QString text = QString::fromUtf8(data_byte);
    qDebug() << text << endl;
    QStringList text_splited = text.split("\r\n");
    int data[30];
    for (int i = 0; i < text_splited.length(); i++) {
        data[i] = text_splited.at(i).toInt();
    }
    for (int i = 0; i < text_splited.length(); i++) {
        qDebug() << data[i];
    }
    Roletype = data[1];
    if (Roletype != DIANA) {
        Bulletshoottimer->stop();
    }
    if (Roletype == AVA) {
        Avaattacktimer = new QTimer();
        Avaattacktimer->start(Ava_attack_sp);
    }
    MainRoletype = data[2];
    have_diana = data[3];
    have_ava = data[4];
    have_eileen = data[5];
    have_bella = data[6];
    global_Diana_level = data[7];
    global_Ava_level = data[8];
    global_Eileen_level = data[9];
    global_Bella_level = data[10];
    global_AT_level = data[11];
    global_SP_level = data[12];
    global_HP_level = data[13];
    global_coin_number = data[14];
    ui_info->coin_number->setText(QString::number(global_coin_number));
    if (!data[0]) {
        AT_level = data[15];
        SP_level = data[16];
        HP_level = data[17];
        Exp = data[18];
        Level = data[19];
        gametime = data[20];
        acaonumber = data[21];
        acao_follownumber = data[22];
        Role.HP = data[23];
        Role.setX(data[24]);
        Role.setY(data[25]);
    }
    loadGenerateAcao();
}

void Mainscene::suicide() {
    issuicide = 1;
    Role.HP = 0;
    Gamescene->removeItem(pause_item);
    if (pause_item)delete pause_item;
    if (save_button)delete save_button;
    if (suicide_button)delete suicide_button;
    restart();
    ispause = 0;
}

void Mainscene::loadGenerateAcao() {
    for (int i = 0; i < acaonumber; i++) {
        Acaoshoot();
    }
    for (int i = 0; i < acao_follownumber; i++) {
        Acao_followshoot();
    }
}


void Mainscene::roleEffect() {
    myeffect = new QGraphicsColorizeEffect();
    role_effect_timer = new QTimer;
    role_effect_timer->start(800);
    myeffect->setColor(Qt::red); // 将颜色设置为红色
    myeffect->setStrength(1); // 将透明度设置
    Role.setGraphicsEffect(myeffect);
    connect(role_effect_timer, &QTimer::timeout, [=]() {
        Role.setGraphicsEffect(nullptr);
    });
}

void Mainscene::acaoEffect(Acao *acao) {
    acao->acaoeffect = new QGraphicsColorizeEffect();
    acao->effecttimer = new QTimer;
    acao->effecttimer->start(800);
    switch (Roletype) {
        case DIANA: {
            acao->acaoeffect->setColor(Qt::red);
            break;
        }
        case AVA: {
            acao->acaoeffect->setColor(Qt::blue);
            break;
        }
    } // 将颜色设置为红色
    acao->acaoeffect->setStrength(2); // 将透明度设置

    acao->setGraphicsEffect(acao->acaoeffect);
    connect(acao->effecttimer, &QTimer::timeout, [=]() {
        acao->setGraphicsEffect(nullptr);
    });
}


