#include "hp_role.h"
#include "ui_hp_role.h"

HP_Role::HP_Role(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HP_Role)
{
    ui->setupUi(this);
}

HP_Role::~HP_Role()
{
    delete ui;
}
