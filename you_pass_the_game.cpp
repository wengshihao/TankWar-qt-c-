#include "you_pass_the_game.h"
#include<QLabel>
#include<QPainter>
#include"config.h"
#include <QKeyEvent>
you_pass_the_game::you_pass_the_game(QWidget *parent)
    : QWidget(parent)
{
    isclose=false;
    tip_font.setFamily("MS Shell Dlg 2");
    tip_font.setPointSize(22);
    tip_font.setBold(true);
    setFixedSize(800,400);
    setStyleSheet("background-color: rgb(255,255,255)");
    loveforpass.load(WINTHEGAME);
    update();
    setTip();
}
void you_pass_the_game::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_K)
    {
        exit(0);
    }
}


void you_pass_the_game::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,loveforpass);

}

void you_pass_the_game::setTip()
{

    QLabel *rule=new QLabel(this);
    rule->setText("恭喜通过所有关\n\n按K结束游戏");
    rule->setFont(tip_font);
    rule->setAlignment(Qt::AlignTop);
    rule->setGeometry(500,120,300,400);
}

you_pass_the_game::~you_pass_the_game()
{

}
