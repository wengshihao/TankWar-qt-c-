#include "tipwidow.h"
#include <QLabel>
#include "config.h"
#include <QPainter>
#include<QFont>
#include <QKeyEvent>
tipwidow::tipwidow(QWidget *parent)
    : QWidget(parent)
{
    isclose=false;
    tip_font.setFamily("MS Shell Dlg 2");
    tip_font.setPointSize(22);
    tip_font.setBold(true);
    setFixedSize(800,400);
    setStyleSheet("background-color: rgb(255,255,255)");
    loveforpass.load(LOVE_PASS_PATH);
    update();
    setTip();
}

void tipwidow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_K)
    {
        isclose=true;
        QWidget::close();
    }
}


void tipwidow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
     painter.drawPixmap(0,0,loveforpass);
}

void tipwidow::setTip()
{

    QLabel *rule=new QLabel(this);
    rule->setText("恭喜通关\n\n按K进入下一关....");
    rule->setFont(tip_font);
    rule->setAlignment(Qt::AlignTop);
    rule->setGeometry(500,120,300,400);
}

tipwidow::~tipwidow()
{

}
