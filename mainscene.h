#ifndef MAINSCENE_H
#define MAINSCENE_H
#include <QWidget>
#include<QTimer>
#include "map.h"
#include "mytank.h"
#include "bullet.h"
#include "enemytank.h"
#include "bomb.h"
#include "home.h"
#include"tipwidow.h"
#include<QTime>
#include"you_pass_the_game.h"
#include"you_lose.h"
#include"buff.h"
class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //初始化背景
    void initsene();

    //时间戳
    QTimer m_Timer;

    //启动游戏
    void playGame();

    //更新游戏中元素的坐标
    void updatePosition();

    //绘制到主界面中
    void paintEvent(QPaintEvent *);

    //键盘按下事件
    void keyPressEvent(QKeyEvent *event);

    //背景对象
    Map m_backmapobj;

    //玩家坦克对象
    MyTank m_mytankobj;

    //敌人坦克对象
    EnemyTank m_enemyobj[ENEMY_NUM];

    //敌人出场
    void enemyToSence();

    //碰撞检测
    void collisionDetection();

    //爆炸数组
    Bomb m_bombs[BOMB_NUM];

    //复活玩家
    void reborn();

    //玩家老家
    Home m_myhomeobj;

    //敌人老家
    Home m_enemyhomeobj;

    //玩家得分
    int m_scores;

    //是否结束游戏
    void isDftOrScs();
    QFont tipfont;//字体
    buff m_buffs[BUFF_NUM];

    tipwidow tip;//提示框
    you_pass_the_game passit;
    you_lose loseit;
    int nowMap;//当前关卡
    void goSecondMap();//通往第二关
    void buffToSence();//出现buff
    int speedup_buff_last;//buff持续时间;


};
#endif // MAINSCENE_H
