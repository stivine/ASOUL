#include "widget.h"
#include"mainscene.h"
#include "ui_widget.h"
#include "mainscene.h"

Widget::Widget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Widget) {

    this->setFixedSize(WINDOWSW, WINDOWSH);
    this->setWindowTitle("想让她们活下去的藤君");

    Gameview.setSceneRect(QRect(0, 0, WINDOWSW, WINDOWSH));
    Startscene.setSceneRect(QRect(0, 0, WINDOWSW, WINDOWSH));
    Startbackground.setPixmap(QPixmap(":/img/title.png"));
    Startscene.addItem(&Startbackground);
    Gameview.setScene(&Startscene);
    Gameview.setParent(this);



    //bgm播放

    bgm = new QMediaPlayer(this);
    bgm_list = new QMediaPlaylist(this);
    bgm_list->addMedia(QMediaContent(QUrl("qrc:/bgm/bgm.mp3")));
    bgm->setVolume(20);
    bgm_list->setPlaybackMode(QMediaPlaylist::Loop);
    bgm->setPlaylist(bgm_list);
    bgm->play();


    ui->setupUi(this);

    //button图标
    ui->newgamebutton->setIcon(QIcon(":/img/icon1.jpg"));
    ui->loadbutton->setIcon(QIcon(":/img/icon3.jpg"));
    ui->Rolechoose_Ava->hide();
    ui->Rolechoose_Diana->hide();
    ui->Rolechoose_Bella->hide();
    ui->Rolechoose_Eileen->hide();
    connect(ui->newgamebutton, &QPushButton::clicked, [=]() {
        Gameview.setScene(&Startscene);
        Rolechoosebackground.setPixmap(QPixmap(":/img/rolechoose.png"));
        Startscene.addItem(&Rolechoosebackground);
        delete ui->newgamebutton;
        delete ui->loadbutton;
        delete ui->label;

        ui->Rolechoose_Ava->show();
        ui->Rolechoose_Diana->show();
        ui->Rolechoose_Bella->show();
        ui->Rolechoose_Eileen->show();
    });
    connect(ui->Rolechoose_Diana, &QPushButton::clicked, [=]() {
        Mainscene *mainscene = new Mainscene(nullptr, DIANA);
        mainscene->setGeometry(this->geometry());
        this->hide();
        mainscene->show();
        mainscene->have_diana = 1;
    });
    connect(ui->Rolechoose_Ava, &QPushButton::clicked, [=]() {
        Mainscene *mainscene = new Mainscene(nullptr, AVA);
        mainscene->setGeometry(this->geometry());
        this->hide();
        mainscene->show();
        mainscene->have_ava = 1;
    });
//    connect(ui->Rolechoose_Bella,&QPushButton::clicked,[=](){
//        Mainscene* mainscene=new Mainscene;
//        mainscene->setGeometry(this->geometry());
//        this->hide();
//        mainscene->Roletype = mainscene->Weapontype = Bella;
//        mainscene->show();
//    });
//    connect(ui->Rolechoose_Eileen,&QPushButton::clicked,[=](){
//        Mainscene* mainscene=new Mainscene;
//        mainscene->setGeometry(this->geometry());
//        this->hide();
//        mainscene->Roletype = mainscene->Weapontype = Eileen;
//        mainscene->show();
//    });
    //***读档功能***
    connect(ui->loadbutton, &QPushButton::clicked, [=]() {
        this->hide();
        Mainscene *mainscene = new Mainscene(nullptr, DIANA);
        mainscene->Role.HP = mainscene->Role.HP_max;
        mainscene->setGeometry(this->geometry());
        mainscene->have_diana = 1;
        mainscene->pause();
        mainscene->load();
        mainscene->restart();
        mainscene->show();
    });
    //***存档功能***
}

Widget::~Widget() {
    delete ui;
}
