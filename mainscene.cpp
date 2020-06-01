#include "mainscene.h"
#include "config.h"
#include "QIcon"
#include <QPainter>
#include <QKeyEvent>
#include<QTimer>
#include<QPoint>
#include<math.h>
#include<QDebug>
#include<QMessageBox>
#include<QLabel>
#include"tipwidow.h"
MainScene::MainScene(QWidget *parent)//MainScene构造函数
    : QWidget(parent)
{
    nowMap=1;
    tipfont.setFamily("Light");
    tipfont.setPointSize(22);
    tipfont.setBold(true);
    m_scores=0;
    speedup_buff_last=0;
    initsene();//调用初始化场景

    playGame();//启动游戏

}

void MainScene::initsene()
{
    srand( (unsigned)time( NULL ) );
    setFixedSize(GAME_WIDTH+400,GAME_HEIGHT);//设置窗口尺寸

    QLabel *rule=new QLabel(this);
    rule->setText("操作按键:\n"
                  "方向控制:W,A,S,D\n"
                  "攻击：J\n\n"
                  "敌人老家hp:\n\n"
                  "剩余复活次数:\n\n"
                  "玩家老家hp:\n\n"
                  "玩家状态:\n\n"
                  "玩家得分:\n\n"
                  "当前所处关卡:\n\n");
    rule->setFont(tipfont);
    rule->setAlignment(Qt::AlignTop);
    rule->setGeometry(1300,0,500,500);


    setWindowTitle(GAME_NAME);//设置标题

    setWindowIcon(QIcon(GAME_ICON));//加载图标

    m_backmapobj.initWall();//设置墙壁

    m_myhomeobj.setPosition(620,960-90);//玩家老家

    m_enemyhomeobj.setPosition(620,0);//敌人老家

    m_Timer.setInterval(GAME_RATE);//帧率设置

}

void MainScene::playGame()
{

    m_Timer.start();//启动定时器


    connect(&m_Timer,&QTimer::timeout,[=]() //监听定时器发送的信号
    {
        if(tip.isclose==true)//进入第二关
        {
            tip.isclose=false;
            goSecondMap();
        }

        if(m_mytankobj.isalive==false)reborn();//复活

        buffToSence();//出现buff

        enemyToSence();//敌人出场

        updatePosition(); //更新游戏中元素的坐标

        update();//绘制到屏幕中

        collisionDetection();//碰撞检测

        isDftOrScs();//判定是否通关
    });
}

void MainScene::updatePosition()
{
    //更新玩家坦克坐标
    if(m_mytankobj.ismove==true)
    {
        int newtankX=m_mytankobj.m_mytankX;
        int newtankY=m_mytankobj.m_mytankY;
        int step=m_mytankobj.step;
        switch (m_mytankobj.dir) {
        case 1:newtankY-=step;break;
        case 2:newtankY+=step;break;
        case 3:newtankX-=step;break;
        case 4:newtankX+=step;break;
        }
        //边界检测
        if(newtankX<0)newtankX=0;
        if(newtankX>GAME_WIDTH-m_mytankobj.m_mytankRect.width())newtankX=GAME_WIDTH-m_mytankobj.m_mytankRect.width();
        if(newtankY<0)newtankY=0;
        if(newtankY>GAME_HEIGHT-m_mytankobj.m_mytankRect.height())newtankY=GAME_HEIGHT-m_mytankobj.m_mytankRect.height();
        m_mytankobj.setTankPosition(newtankX,newtankY);//更新坐标
    }

    //更新玩家子弹坐标
    for(int i=0;i<BULLET_NUM;i++)
    {

        if(m_mytankobj.m_bullets[i].m_free==false)//子弹处于发射中
        {
            m_mytankobj.m_bullets[i].setBulletPosition();
        }
    }

    //更新敌人子弹坐标
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false)
        {
            for(int j=0;j<BULLET_NUM;j++)
            {
                if(m_enemyobj[i].m_enemyBullets[j].m_free==false)
                {
                    m_enemyobj[i].m_enemyBullets[j].setBulletPosition();
                }
            }
        }

    }

    //敌人移动
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false)
        {
            m_enemyobj[i].m_Enemy_Second++;//敌人拐弯时间戳+1

            m_enemyobj[i].m_Enemy_Shot_Second++;//敌人发射时间戳+1
            int newdir=m_enemyobj[i].dir;//新方向
            if(m_enemyobj[i].m_Enemy_Second==ENEMY_TRUN_RATE)//时间到，改变方向  rate=10*ETR
            {
                newdir=1+rand()%4;//随机取一个方向
                m_enemyobj[i].m_Enemy_Second=0;//时间戳初始化
            }



            m_enemyobj[i].setEnemyDir(newdir);//重新设置方向

            int step=m_enemyobj[i].step;//获取移动步数

            int newenemX,newenemY;//新位置
            if(m_enemyobj[i].dir==1)
            {
                newenemX=m_enemyobj[i].m_enemyX;
                newenemY=m_enemyobj[i].m_enemyY-step;
            }
            if(m_enemyobj[i].dir==2)
            {
                newenemX=m_enemyobj[i].m_enemyX;
                newenemY=m_enemyobj[i].m_enemyY+step;
            }
            if(m_enemyobj[i].dir==3)
            {
                newenemX=m_enemyobj[i].m_enemyX-step;
                newenemY=m_enemyobj[i].m_enemyY;
            }
            if(m_enemyobj[i].dir==4)
            {
                newenemX=m_enemyobj[i].m_enemyX+step;
                newenemY=m_enemyobj[i].m_enemyY;
            }
            //边界判断
            if(newenemX<0)newenemX=0;
            if(newenemX>GAME_WIDTH-m_mytankobj.m_mytankRect.width())newenemX=GAME_WIDTH-m_enemyobj[i].m_Rect.width();
            if(newenemY<0)newenemY=0;
            if(newenemY>GAME_HEIGHT-m_mytankobj.m_mytankRect.height())newenemY=GAME_HEIGHT-m_enemyobj[i].m_Rect.height();
            m_enemyobj[i].setEnemyPosition(newenemX,newenemY);


            //敌人发射子弹
            if(m_enemyobj[i].m_Enemy_Shot_Second==ENEMY_SHOT_RATE)
            {
                int isshot=rand()%2;
                if(isshot==0)m_enemyobj[i].m_Enemy_Shot_Second=0;
                else
                {
                    m_enemyobj[i].shoot(m_enemyobj[i].dir);
                    m_enemyobj[i].m_Enemy_Shot_Second=0;
                }
            }
        }
    }

    //爆炸
    for(int i=0;i<BOMB_NUM;i++)
    {
        if(m_bombs[i].m_free==false)
        {
            m_bombs[i].updateNoBomb();
        }
    }


}



void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,m_backmapobj.m_backmap_positionY,m_backmapobj.m_backmap);//绘制地图

    painter.drawPixmap(1280,0,m_backmapobj.m_tipback);
    painter.drawPixmap(1480,760,m_backmapobj.m_mylogo);

    //敌人老家血量
    QString hp_todraw = QString::number(m_enemyhomeobj.hp, 10);
    painter.setFont(tipfont);
    painter.drawText(1480,158,hp_todraw);

    //玩家老家血量
    QString hpofme_todraw = QString::number(m_myhomeobj.hp, 10);
    painter.setFont(tipfont);
    painter.drawText(1480,289,hpofme_todraw);

    //玩家命数
    QString livesOfme = QString::number(m_mytankobj.lives, 10);
    painter.setFont(tipfont);
    painter.drawText(1500,222,livesOfme);

    //玩家状态
    if(m_mytankobj.isalive)
        painter.drawText(1440,354,"存活");
    else painter.drawText(1440,354,"复活中...");
    if(m_mytankobj.step==2)
    {
        painter.drawText(1500,354,",加速");
    }
    //所处关卡
    QString inmap = QString::number(nowMap, 10);
    painter.setFont(tipfont);
    painter.drawText(1500,484,inmap);

    //玩家得分
    QString scoreOfme = QString::number(m_scores, 10);
    painter.setFont(tipfont);
    painter.drawText(1440,418,scoreOfme);


    if(m_myhomeobj.isalive==true)//绘制老家
    {
        painter.drawPixmap(m_myhomeobj.m_X,m_myhomeobj.m_Y,m_myhomeobj.m_myHome);
    }
    if(m_enemyhomeobj.isalive==true)
    {
        painter.drawPixmap(m_enemyhomeobj.m_X,m_enemyhomeobj.m_Y,m_enemyhomeobj.m_enemyHome);
    }

    //绘制墙壁
    for(int i=0;i<WALL_NUM;i++)
    {
        if(m_backmapobj.walls[i].m_free==false)
        {
            painter.drawPixmap(m_backmapobj.walls[i].m_WallX,m_backmapobj.walls[i].m_WallY,m_backmapobj.walls[i].m_Wall);
        }
    }

    //绘制石头
    for(int i=0;i<STONE_NUM;i++)
    {
        if(m_backmapobj.stones[i].m_free==false)
        {
            painter.drawPixmap(m_backmapobj.stones[i].m_X,m_backmapobj.stones[i].m_Y,m_backmapobj.stones[i].m_stone);
        }
    }


    //绘制玩家坦克
    if(m_mytankobj.isalive==true)
    {

        switch (m_mytankobj.dir) {
        case 1:painter.drawPixmap(m_mytankobj.m_mytankX,m_mytankobj.m_mytankY,m_mytankobj.m_mytank1);break;
        case 2:painter.drawPixmap(m_mytankobj.m_mytankX,m_mytankobj.m_mytankY,m_mytankobj.m_mytank2);break;
        case 3:painter.drawPixmap(m_mytankobj.m_mytankX,m_mytankobj.m_mytankY,m_mytankobj.m_mytank3);break;
        case 4:painter.drawPixmap(m_mytankobj.m_mytankX,m_mytankobj.m_mytankY,m_mytankobj.m_mytank4);break;
        }
    }

    //绘制玩家子弹
    for(int i=0;i<BULLET_NUM;i++)
    {

        if(m_mytankobj.m_bullets[i].m_free==false)
        {
            if(m_mytankobj.m_bullets[i].bulletDir==1)
                painter.drawPixmap(m_mytankobj.m_bullets[i].m_X,m_mytankobj.m_bullets[i].m_Y,m_mytankobj.m_bullets[i].m_BulletUP);
            if(m_mytankobj.m_bullets[i].bulletDir==2)
                painter.drawPixmap(m_mytankobj.m_bullets[i].m_X,m_mytankobj.m_bullets[i].m_Y,m_mytankobj.m_bullets[i].m_BulletDown);
            if(m_mytankobj.m_bullets[i].bulletDir==3)
                painter.drawPixmap(m_mytankobj.m_bullets[i].m_X,m_mytankobj.m_bullets[i].m_Y,m_mytankobj.m_bullets[i].m_BulletLeft);
            if(m_mytankobj.m_bullets[i].bulletDir==4)
                painter.drawPixmap(m_mytankobj.m_bullets[i].m_X,m_mytankobj.m_bullets[i].m_Y,m_mytankobj.m_bullets[i].m_BulletRight);
        }
    }

    //绘制敌人子弹
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false)
        {
            for(int j=0;j<BULLET_NUM;j++)
            {
                if(m_enemyobj[i].m_enemyBullets[j].m_free==false)
                {
                    if(m_enemyobj[i].m_enemyBullets[j].bulletDir==1)
                    {
                        painter.drawPixmap(m_enemyobj[i].m_enemyBullets[j].m_X,m_enemyobj[i].m_enemyBullets[j].m_Y,m_enemyobj[i].m_enemyBullets[j].m_BulletUP);
                    }
                    if(m_enemyobj[i].m_enemyBullets[j].bulletDir==2)
                    {
                        painter.drawPixmap(m_enemyobj[i].m_enemyBullets[j].m_X,m_enemyobj[i].m_enemyBullets[j].m_Y,m_enemyobj[i].m_enemyBullets[j].m_BulletDown);
                    }
                    if(m_enemyobj[i].m_enemyBullets[j].bulletDir==3)
                    {
                        painter.drawPixmap(m_enemyobj[i].m_enemyBullets[j].m_X,m_enemyobj[i].m_enemyBullets[j].m_Y,m_enemyobj[i].m_enemyBullets[j].m_BulletLeft);
                    }
                    if(m_enemyobj[i].m_enemyBullets[j].bulletDir==4)
                    {
                        painter.drawPixmap(m_enemyobj[i].m_enemyBullets[j].m_X,m_enemyobj[i].m_enemyBullets[j].m_Y,m_enemyobj[i].m_enemyBullets[j].m_BulletRight);
                    }
                }
            }
        }
\
    }

    //绘制敌人
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false)
        {
            if(m_enemyobj[i].dir==1)
            {
                painter.drawPixmap(m_enemyobj[i].m_enemyX,m_enemyobj[i].m_enemyY,m_enemyobj[i].m_enemyUP);
            }
            if(m_enemyobj[i].dir==2)
            {
                painter.drawPixmap(m_enemyobj[i].m_enemyX,m_enemyobj[i].m_enemyY,m_enemyobj[i].m_enemyDown);
            }
            if(m_enemyobj[i].dir==3)
            {
                painter.drawPixmap(m_enemyobj[i].m_enemyX,m_enemyobj[i].m_enemyY,m_enemyobj[i].m_enemyLeft);
            }
            if(m_enemyobj[i].dir==4)
            {
                painter.drawPixmap(m_enemyobj[i].m_enemyX,m_enemyobj[i].m_enemyY,m_enemyobj[i].m_enemyRight);
            }
        }
    }

    //绘制爆炸
    for(int i=0;i<BOMB_NUM;i++)
    {
        if(m_bombs[i].m_free==false)
        {
            painter.drawPixmap(m_bombs[i].m_bombX,m_bombs[i].m_bombY,m_bombs[i].m_pixarr[m_bombs[i].m_index]);
        }
    }
    //test for碰撞变颜色*****************
    /*
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false)
        {
            for(int j=m_mytankobj.m_mytankX;j<=m_mytankobj.m_mytankX+m_mytankobj.m_mytankRect.width();j++)
            {
                for(int k=m_mytankobj.m_mytankY;k<=m_mytankobj.m_mytankY+m_mytankobj.m_mytankRect.height();k++)
                {
                    if(m_enemyobj[i].m_Rect.contains(QPoint(j,k)))
                    {

                        QPen mypen;
                        mypen.setWidth(1);
                        mypen.setColor(Qt::red);
                        painter.setPen(mypen);
                        painter.drawPoint(j,k);
                    }
                }
            }
        }
    }
    */
    //**********************
    //绘制buff
    for(int i=0;i<BUFF_NUM;i++)
    {
        if(m_buffs[i].m_free==false)
        {
            painter.drawPixmap(m_buffs[i].m_X,m_buffs[i].m_Y,m_buffs[i].m_speedup_buff);
        }
    }
    //绘制树林
    for(int i=0;i<TREE_NUM;i++)
    {
        if(m_backmapobj.trees[i].m_free==false)
        {
            painter.drawPixmap(m_backmapobj.trees[i].m_X,m_backmapobj.trees[i].m_Y,m_backmapobj.trees[i].m_tree);
        }
    }


}



void MainScene::keyPressEvent(QKeyEvent *event)
{
    //键盘控制移动方向
    if(event->key()==Qt::Key_W)
    {
        m_mytankobj.setdir(1);
        m_mytankobj.ismove=true;
    }
    else if(event->key()==Qt::Key_S)
    {
        m_mytankobj.setdir(2);
        m_mytankobj.ismove=true;
    }
    else if(event->key()==Qt::Key_A)
    {
        m_mytankobj.setdir(3);
        m_mytankobj.ismove=true;
    }
    else if(event->key()==Qt::Key_D)
    {
        m_mytankobj.setdir(4);
        m_mytankobj.ismove=true;
    }

    //发射并传递发射方向
    if(event->key()==Qt::Key_J)
    {
        m_mytankobj.shoot(m_mytankobj.dir);
    }
}




void MainScene::enemyToSence()
{
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false)return;//但凡有一个敌人则不刷新
    }

    for(int i=0;i<ENEMY_NUM;i++)
    {
        m_enemyobj[i].m_free=false;//设置不空闲
    }
    if(nowMap==1)
    {

        m_enemyobj[0].setEnemyPosition(100,400);
        m_enemyobj[1].setEnemyPosition(450,100);
        m_enemyobj[2].setEnemyPosition(820,100);
        m_enemyobj[2].setEnemyDir(2);
        m_enemyobj[3].setEnemyPosition(1050,150);
        m_enemyobj[3].setEnemyDir(4);
        m_enemyobj[4].setEnemyPosition(550,550);
        m_enemyobj[4].setEnemyDir(3);
    }
    else
    {
        m_enemyobj[0].setEnemyPosition(60,20);
        m_enemyobj[0].setEnemyDir(4);
        m_enemyobj[1].setEnemyPosition(500,500);
        m_enemyobj[2].setEnemyPosition(700,700);
        m_enemyobj[2].setEnemyDir(2);
        m_enemyobj[3].setEnemyPosition(700,700);
        m_enemyobj[3].setEnemyDir(4);
        m_enemyobj[4].setEnemyPosition(300,500);
        m_enemyobj[4].setEnemyDir(3);
    }

    //以下代码作废原因：随机数生成时间较长
    /*
    srand( (unsigned)time( NULL ) );
    for(int i=0;i<ENEMY_NUM;i++)
    {
        m_enemyobj[i].m_free=false;//设置不空闲
        m_enemyobj[i].setEnemyDir(1+rand()%4);//设置方向
        //设置位置
        int newx=rand()%1280;
        int newy=rand()%960;
         m_enemyobj[i].setEnemyPosition(newx,newy);
        int flag=false;

        //出生不与墙壁重合
        for(int j=0;j<WALL_NUM;j++)
        {
            if(m_backmapobj.walls[j].m_WallRect.right()+5<m_enemyobj[i].m_Rect.left()
              ||m_backmapobj.walls[j].m_WallRect.left()>m_enemyobj[i].m_Rect.right()+5
              ||m_backmapobj.walls[j].m_WallRect.bottom()+5<m_enemyobj[i].m_Rect.top()
              ||m_backmapobj.walls[j].m_WallRect.top()>m_enemyobj[i].m_Rect.bottom()+5)
            {
            continue;
            }
            flag=true;
        }

        //出生不与石头重合
        int flag2=false;
        for(int j=0;j<STONE_NUM;j++)
        {

            if(m_backmapobj.stones[j].m_Rect.right()+5<m_enemyobj[i].m_Rect.left()
               ||m_backmapobj.stones[j].m_Rect.left()>m_enemyobj[i].m_Rect.right()+5
               ||m_backmapobj.stones[j].m_Rect.bottom()+5<m_enemyobj[i].m_Rect.top()
               ||m_backmapobj.stones[j].m_Rect.top()>m_enemyobj[i].m_Rect.bottom()+5)
            {
            continue;
            }
            else flag2=true;
        }


        //出生不与玩家老家重合
        int flag3=false;
        if(m_myhomeobj.m_HomeRect.right()+5<m_enemyobj[i].m_Rect.left()
           ||m_myhomeobj.m_HomeRect.left()>m_enemyobj[i].m_Rect.right()+5
           ||m_myhomeobj.m_HomeRect.bottom()+5<m_enemyobj[i].m_Rect.top()
           ||m_myhomeobj.m_HomeRect.top()>m_enemyobj[i].m_Rect.bottom()+5)
        {
            flag3=false;
        }
        else flag3=true;

        //出生不与敌人老家重合
        int flag4=false;
        if(m_enemyhomeobj.m_HomeRect.right()+5<m_enemyobj[i].m_Rect.left()
           ||m_enemyhomeobj.m_HomeRect.left()>m_enemyobj[i].m_Rect.right()+5
           ||m_enemyhomeobj.m_HomeRect.bottom()+5<m_enemyobj[i].m_Rect.top()
           ||m_enemyhomeobj.m_HomeRect.top()>m_enemyobj[i].m_Rect.bottom()+5)
        {
            flag4=false;
        }
        else flag4=true;


        while(flag||flag2||flag3||flag4)
        {
            newx=rand()%1280;
            newy=rand()%960;
            m_enemyobj[i].setEnemyPosition(newx,newy);
            flag=false;
            for(int j=0;j<WALL_NUM;j++)
            {
                if(m_backmapobj.walls[j].m_WallRect.right()+5<m_enemyobj[i].m_Rect.left()
                      ||m_backmapobj.walls[j].m_WallRect.left()>m_enemyobj[i].m_Rect.right()+5
                      ||m_backmapobj.walls[j].m_WallRect.bottom()+5<m_enemyobj[i].m_Rect.top()
                      ||m_backmapobj.walls[j].m_WallRect.top()>m_enemyobj[i].m_Rect.bottom()+5)
                {
                    continue;
                }
                flag=true;
            }

            flag2=false;
            for(int j=0;j<STONE_NUM;j++)
            {

                if(m_backmapobj.stones[j].m_Rect.right()+5<m_enemyobj[i].m_Rect.left()
                   ||m_backmapobj.stones[j].m_Rect.left()>m_enemyobj[i].m_Rect.right()+5
                   ||m_backmapobj.stones[j].m_Rect.bottom()+5<m_enemyobj[i].m_Rect.top()
                   ||m_backmapobj.stones[j].m_Rect.top()>m_enemyobj[i].m_Rect.bottom()+5)
                {
                continue;
                }
                else flag2=true;
            }
        }
        qDebug("%d*%d",newx,newy);
        m_enemyobj[i].setEnemyPosition(newx,newy);
    }
    */
}

void MainScene::collisionDetection()//碰撞检测
{
    //坦克之间相互碰撞
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false&&m_mytankobj.isalive==true)
        {
            if(m_enemyobj[i].m_Rect.intersects(m_mytankobj.m_mytankRect))
            {
                m_enemyobj[i].m_free=true;
                m_mytankobj.isalive=false;
                m_mytankobj.lives--;
                for(int k=0;k<BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_free)//空闲则爆炸
                    {
                        m_bombs[k].m_free=false;//爆炸中
                        m_bombs[k].m_bombX=m_mytankobj.m_mytankX;
                        m_bombs[k].m_bombY=m_mytankobj.m_mytankY;
                        break;
                    }
                }
                for(int k=0;k<BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_free)//空闲则爆炸
                    {
                        m_bombs[k].m_free=false;//爆炸中
                        m_bombs[k].m_bombX=m_enemyobj[i].m_enemyX;
                        m_bombs[k].m_bombY=m_enemyobj[i].m_enemyY;
                        break;
                    }
                }
            }
        }
    }
    for(int i=0;i<BULLET_NUM;i++)//击中敌人老家
    {
        if(m_mytankobj.m_bullets[i].m_free==false)
        {
            if(m_mytankobj.m_bullets[i].m_RectUP.intersects(m_enemyhomeobj.m_HomeRect)&&m_enemyhomeobj.isalive==true)
            {
                m_mytankobj.m_bullets[i].m_free=true;
                m_enemyhomeobj.hp--;
                if(!m_enemyhomeobj.hp)
                {
                    m_enemyhomeobj.isalive=false;
                }
                for(int k=0;k<BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_free)//空闲则爆炸
                    {
                        m_bombs[k].m_free=false;//爆炸中
                        m_bombs[k].m_bombX=m_enemyhomeobj.m_X;
                        m_bombs[k].m_bombY=m_enemyhomeobj.m_Y;
                        break;
                    }
                }
                break;
            }
        }
    }

    //自杀
    for(int i=0;i<BULLET_NUM;i++)
    {
        if(m_mytankobj.m_bullets[i].m_free==false)
        {
            if(m_mytankobj.m_bullets[i].m_RectUP.intersects(m_myhomeobj.m_HomeRect)&&m_myhomeobj.isalive==true)
            {
                m_mytankobj.m_bullets[i].m_free=true;
                m_myhomeobj.hp--;
                if(!m_myhomeobj.hp)
                {
                    m_myhomeobj.isalive=false;
                }
                for(int k=0;k<BOMB_NUM;k++)
                {
                    if(m_bombs[k].m_free)//空闲则爆炸
                    {
                        m_bombs[k].m_free=false;//爆炸中
                        m_bombs[k].m_bombX=m_myhomeobj.m_X;
                        m_bombs[k].m_bombY=m_myhomeobj.m_Y;
                        break;
                    }
                }
                break;
            }
        }
    }

    //击中自己老家
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false)
        {
            for(int j=0;j<BULLET_NUM;j++)
            {
                if(m_enemyobj[i].m_enemyBullets[j].m_free==false)
                {
                    if(m_enemyobj[i].m_enemyBullets[j].m_RectUP.intersects(m_myhomeobj.m_HomeRect))
                    {
                        m_myhomeobj.hp--;
                        m_enemyobj[i].m_enemyBullets[j].m_free=true;//不加出秒杀bug

                        if(!m_myhomeobj.hp)
                        {
                            m_myhomeobj.isalive=false;
                        }
                        for(int k=0;k<BOMB_NUM;k++)
                        {
                            if(m_bombs[k].m_free)//空闲则爆炸
                            {
                                m_bombs[k].m_free=false;//爆炸中
                                m_bombs[k].m_bombX=m_myhomeobj.m_X;
                                m_bombs[k].m_bombY=m_myhomeobj.m_Y;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    //命中敌人
    for(int i=0;i<ENEMY_NUM;i++)//遍历所有非空闲敌人
    {
        if(m_enemyobj[i].m_free==false)
        {
            for(int j=0;j<BULLET_NUM;j++)//遍历所有非空闲子弹
            {
                if(m_mytankobj.m_bullets[j].m_free==false)
                {
                    QRect bulletrect;
                    bulletrect.setWidth(m_mytankobj.m_bullets[j].m_BulletUP.width());
                    bulletrect.setHeight(m_mytankobj.m_bullets[j].m_BulletUP.height());
                    bulletrect.moveTo(m_mytankobj.m_bullets[j].m_X,m_mytankobj.m_bullets[j].m_Y);

                    if(m_enemyobj[i].m_Rect.intersects(bulletrect))//子弹与敌人的矩形框相交
                    {
                        m_enemyobj[i].m_free=true;//闲置敌人
                        m_mytankobj.m_bullets[j].m_free=true;//闲置子弹
                        m_scores+=150;
                        //爆炸
                        for(int k=0;k<BOMB_NUM;k++)
                        {
                            if(m_bombs[k].m_free)//空闲则爆炸
                            {
                                m_bombs[k].m_free=false;//爆炸中

                                //爆炸位置设为敌人位置
                                m_bombs[k].m_bombX=m_enemyobj[i].m_enemyX;
                                m_bombs[k].m_bombY=m_enemyobj[i].m_enemyY;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    //检测玩家与墙壁碰撞
    for(int i=0;i<WALL_NUM;i++)
    {
        if(m_backmapobj.walls[i].m_free==false)
        {
            /*bug代码
            if(m_backmapobj.walls[i].m_WallRect.right()+5<m_mytankobj.m_mytankRect.left()
                    ||m_backmapobj.walls[i].m_WallRect.left()>m_mytankobj.m_mytankRect.right()+5
                    ||m_backmapobj.walls[i].m_WallRect.bottom()+5<m_mytankobj.m_mytankRect.top()
                    ||m_backmapobj.walls[i].m_WallRect.top()>m_mytankobj.m_mytankRect.bottom()+5)
            {
                continue;
            }*/

            if(m_mytankobj.dir==1)
            {
                if(m_backmapobj.walls[i].m_WallRect.right()+1<m_mytankobj.m_mytankRect.left()
                        ||m_backmapobj.walls[i].m_WallRect.left()>m_mytankobj.m_mytankRect.right()+1
                        ||m_backmapobj.walls[i].m_WallRect.bottom()+5<m_mytankobj.m_mytankRect.top()
                        ||m_backmapobj.walls[i].m_WallRect.top()>m_mytankobj.m_mytankRect.bottom()+1)
                    continue;
            }
            else if(m_mytankobj.dir==2)
            {
                if(m_backmapobj.walls[i].m_WallRect.right()+1<m_mytankobj.m_mytankRect.left()
                        ||m_backmapobj.walls[i].m_WallRect.left()>m_mytankobj.m_mytankRect.right()+1
                        ||m_backmapobj.walls[i].m_WallRect.bottom()+1<m_mytankobj.m_mytankRect.top()
                        ||m_backmapobj.walls[i].m_WallRect.top()>m_mytankobj.m_mytankRect.bottom()+5)
                    continue;
            }
            else if(m_mytankobj.dir==3)
            {
                if(m_backmapobj.walls[i].m_WallRect.right()+5<m_mytankobj.m_mytankRect.left()
                        ||m_backmapobj.walls[i].m_WallRect.left()>m_mytankobj.m_mytankRect.right()+1
                        ||m_backmapobj.walls[i].m_WallRect.bottom()+1<m_mytankobj.m_mytankRect.top()
                        ||m_backmapobj.walls[i].m_WallRect.top()>m_mytankobj.m_mytankRect.bottom()+1)
                    continue;
            }
            else if(m_mytankobj.dir==4)
            {
                if(m_backmapobj.walls[i].m_WallRect.right()+1<m_mytankobj.m_mytankRect.left()
                        ||m_backmapobj.walls[i].m_WallRect.left()>m_mytankobj.m_mytankRect.right()+5
                        ||m_backmapobj.walls[i].m_WallRect.bottom()+1<m_mytankobj.m_mytankRect.top()
                        ||m_backmapobj.walls[i].m_WallRect.top()>m_mytankobj.m_mytankRect.bottom()+1)
                    continue;
            }
            m_mytankobj.ismove=false;
        }
    }

    //检测敌人与墙壁碰撞
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false)
        {
            for(int j=0;j<WALL_NUM;j++)
            {
                if(m_backmapobj.walls[j].m_free==false)
                {
                    /*bug代码
                    if(m_backmapobj.walls[j].m_WallRect.right()+5<m_enemyobj[i].m_Rect.left()
                            ||m_backmapobj.walls[j].m_WallRect.left()>m_enemyobj[i].m_Rect.right()+5
                            ||m_backmapobj.walls[j].m_WallRect.bottom()+5<m_enemyobj[i].m_Rect.top()
                            ||m_backmapobj.walls[j].m_WallRect.top()>m_enemyobj[i].m_Rect.bottom()+5)
                    {
                        continue;
                    }*/
                    if(m_enemyobj[i].dir==1)
                    {
                        if(m_backmapobj.walls[j].m_WallRect.right()+1<m_enemyobj[i].m_Rect.left()
                                ||m_backmapobj.walls[j].m_WallRect.left()>m_enemyobj[i].m_Rect.right()+1
                                ||m_backmapobj.walls[j].m_WallRect.bottom()+5<m_enemyobj[i].m_Rect.top()
                                ||m_backmapobj.walls[j].m_WallRect.top()>m_enemyobj[i].m_Rect.bottom()+1)
                            continue;
                    }
                    if(m_enemyobj[i].dir==2)
                    {
                        if(m_backmapobj.walls[j].m_WallRect.right()+1<m_enemyobj[i].m_Rect.left()
                                ||m_backmapobj.walls[j].m_WallRect.left()>m_enemyobj[i].m_Rect.right()+1
                                ||m_backmapobj.walls[j].m_WallRect.bottom()+1<m_enemyobj[i].m_Rect.top()
                                ||m_backmapobj.walls[j].m_WallRect.top()>m_enemyobj[i].m_Rect.bottom()+5)
                            continue;
                    }
                    if(m_enemyobj[i].dir==3)
                    {
                        if(m_backmapobj.walls[j].m_WallRect.right()+5<m_enemyobj[i].m_Rect.left()
                                ||m_backmapobj.walls[j].m_WallRect.left()>m_enemyobj[i].m_Rect.right()+1
                                ||m_backmapobj.walls[j].m_WallRect.bottom()+1<m_enemyobj[i].m_Rect.top()
                                ||m_backmapobj.walls[j].m_WallRect.top()>m_enemyobj[i].m_Rect.bottom()+1)
                            continue;
                    }
                    if(m_enemyobj[i].dir==4)
                    {
                        if(m_backmapobj.walls[j].m_WallRect.right()+1<m_enemyobj[i].m_Rect.left()
                                ||m_backmapobj.walls[j].m_WallRect.left()>m_enemyobj[i].m_Rect.right()+5
                                ||m_backmapobj.walls[j].m_WallRect.bottom()+1<m_enemyobj[i].m_Rect.top()
                                ||m_backmapobj.walls[j].m_WallRect.top()>m_enemyobj[i].m_Rect.bottom()+1)
                            continue;
                    }
                    int lastdir=m_enemyobj[i].dir;
                    int newdir=lastdir;
                    while(newdir==lastdir)newdir=1+rand()%4;
                    m_enemyobj[i].dir=newdir;
                }
            }
        }
    }



    //检测玩家与石头碰撞
    for(int i=0;i<STONE_NUM;i++)
    {
        if(m_backmapobj.stones[i].m_free==false)
        {
            if(m_mytankobj.dir==1)
            {
                if(m_backmapobj.stones[i].m_Rect.right()+1<m_mytankobj.m_mytankRect.left()
                        ||m_backmapobj.stones[i].m_Rect.left()>m_mytankobj.m_mytankRect.right()+1
                        ||m_backmapobj.stones[i].m_Rect.bottom()+5<m_mytankobj.m_mytankRect.top()
                        ||m_backmapobj.stones[i].m_Rect.top()>m_mytankobj.m_mytankRect.bottom()+1)
                    continue;
            }
            else if(m_mytankobj.dir==2)
            {
                if(m_backmapobj.stones[i].m_Rect.right()+1<m_mytankobj.m_mytankRect.left()
                        ||m_backmapobj.stones[i].m_Rect.left()>m_mytankobj.m_mytankRect.right()+1
                        ||m_backmapobj.stones[i].m_Rect.bottom()+1<m_mytankobj.m_mytankRect.top()
                        ||m_backmapobj.stones[i].m_Rect.top()>m_mytankobj.m_mytankRect.bottom()+5)
                    continue;
            }
            else if(m_mytankobj.dir==3)
            {
                if(m_backmapobj.stones[i].m_Rect.right()+5<m_mytankobj.m_mytankRect.left()
                        ||m_backmapobj.stones[i].m_Rect.left()>m_mytankobj.m_mytankRect.right()+1
                        ||m_backmapobj.stones[i].m_Rect.bottom()+1<m_mytankobj.m_mytankRect.top()
                        ||m_backmapobj.stones[i].m_Rect.top()>m_mytankobj.m_mytankRect.bottom()+1)
                    continue;
            }
            else if(m_mytankobj.dir==4)
            {
                if(m_backmapobj.stones[i].m_Rect.right()+1<m_mytankobj.m_mytankRect.left()
                        ||m_backmapobj.stones[i].m_Rect.left()>m_mytankobj.m_mytankRect.right()+5
                        ||m_backmapobj.stones[i].m_Rect.bottom()+1<m_mytankobj.m_mytankRect.top()
                        ||m_backmapobj.stones[i].m_Rect.top()>m_mytankobj.m_mytankRect.bottom()+1)
                    continue;
            }
            m_mytankobj.ismove=false;
        }
    }

    //检测敌人与石头碰撞
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false)
        {
            for(int j=0;j<STONE_NUM;j++)
            {
                if(m_backmapobj.stones[j].m_free==false)
                {
                    if(m_enemyobj[i].dir==1)
                    {
                        if(m_backmapobj.stones[j].m_Rect.right()+1<m_enemyobj[i].m_Rect.left()
                                ||m_backmapobj.stones[j].m_Rect.left()>m_enemyobj[i].m_Rect.right()+1
                                ||m_backmapobj.stones[j].m_Rect.bottom()+5<m_enemyobj[i].m_Rect.top()
                                ||m_backmapobj.stones[j].m_Rect.top()>m_enemyobj[i].m_Rect.bottom()+1)
                            continue;
                    }
                    if(m_enemyobj[i].dir==2)
                    {
                        if(m_backmapobj.stones[j].m_Rect.right()+1<m_enemyobj[i].m_Rect.left()
                                ||m_backmapobj.stones[j].m_Rect.left()>m_enemyobj[i].m_Rect.right()+1
                                ||m_backmapobj.stones[j].m_Rect.bottom()+1<m_enemyobj[i].m_Rect.top()
                                ||m_backmapobj.stones[j].m_Rect.top()>m_enemyobj[i].m_Rect.bottom()+5)
                            continue;
                    }
                    if(m_enemyobj[i].dir==3)
                    {
                        if(m_backmapobj.stones[j].m_Rect.right()+5<m_enemyobj[i].m_Rect.left()
                                ||m_backmapobj.stones[j].m_Rect.left()>m_enemyobj[i].m_Rect.right()+1
                                ||m_backmapobj.stones[j].m_Rect.bottom()+1<m_enemyobj[i].m_Rect.top()
                                ||m_backmapobj.stones[j].m_Rect.top()>m_enemyobj[i].m_Rect.bottom()+1)
                            continue;
                    }
                    if(m_enemyobj[i].dir==4)
                    {
                        if(m_backmapobj.stones[j].m_Rect.right()+1<m_enemyobj[i].m_Rect.left()
                                ||m_backmapobj.stones[j].m_Rect.left()>m_enemyobj[i].m_Rect.right()+5
                                ||m_backmapobj.stones[j].m_Rect.bottom()+1<m_enemyobj[i].m_Rect.top()
                                ||m_backmapobj.stones[j].m_Rect.top()>m_enemyobj[i].m_Rect.bottom()+1)
                            continue;
                    }
                    int lastdir=m_enemyobj[i].dir;
                    int newdir=lastdir;
                    while(newdir==lastdir)newdir=1+rand()%4;
                    m_enemyobj[i].dir=newdir;

                }
            }
        }
    }

    //检测子弹与墙壁碰撞
    for(int i=0;i<WALL_NUM;i++)
    {
        if(m_backmapobj.walls[i].m_free==false)
        {
            for(int j=0;j<BULLET_NUM;j++)
            {
                if(m_mytankobj.m_bullets[j].m_free==false)
                {
                    if(m_backmapobj.walls[i].m_WallRect.intersects(m_mytankobj.m_bullets[j].m_RectUP))
                    {
                        m_backmapobj.walls[i].m_free=true;//闲置墙壁
                        m_mytankobj.m_bullets[j].m_free=true;//闲置子弹

                        //遍历与其链接的墙壁
                        QPoint centernow=m_backmapobj.walls[i].m_WallRect.center();//目前矩形框的中心

                        for(int k=0;k<WALL_NUM;k++)//寻找与目前墙壁相切的墙壁消灭
                        {
                            if(m_backmapobj.walls[k].m_free==false)
                            {
                                QPoint center_bound=m_backmapobj.walls[k].m_WallRect.center();
                                if(abs(centernow.rx()-center_bound.rx())==WALL_SIZE&&centernow.ry()==center_bound.ry())
                                {
                                    m_backmapobj.walls[k].m_free=true;
                                }
                                else if(abs(centernow.ry()-center_bound.ry())==WALL_SIZE&&centernow.rx()==center_bound.rx())
                                {
                                    m_backmapobj.walls[k].m_free=true;
                                }

                            }
                        }
                        break;
                    }
                }
            }

        }
    }
    //敌人子弹碰撞
    for(int i=0;i<ENEMY_NUM;i++)
    {
        if(m_enemyobj[i].m_free==false)
        {
            for(int j=0;j<BULLET_NUM;j++)
            {
                if(m_enemyobj[i].m_enemyBullets[j].m_free==false)
                {
                    if(m_enemyobj[i].m_enemyBullets[j].m_RectUP.intersects(m_mytankobj.m_mytankRect)&&m_mytankobj.isalive)
                    {
                        m_mytankobj.isalive=false;
                        m_enemyobj[i].m_enemyBullets[j].m_free=true;
                        m_mytankobj.lives--;
                        for(int k=0;k<BOMB_NUM;k++)
                        {
                            if(m_bombs[k].m_free)//空闲则爆炸
                            {
                                m_bombs[k].m_free=false;//爆炸中
                                //爆炸位置设为玩家位置
                                m_bombs[k].m_bombX=m_mytankobj.m_mytankX;
                                m_bombs[k].m_bombY=m_mytankobj.m_mytankY;
                                break;
                            }
                        }
                        break;
                    }
                    for(int k=0;k<WALL_NUM;k++)
                    {
                        if(m_backmapobj.walls[k].m_free==false)
                        {
                            if(m_enemyobj[i].m_enemyBullets[j].m_RectUP.intersects(m_backmapobj.walls[k].m_WallRect))
                            {
                                m_backmapobj.walls[k].m_free=true;
                                m_enemyobj[i].m_enemyBullets[j].m_free=true;
                                break;
                            }
                        }
                    }
                }

            }
        }
    }


    //检测子弹与石头碰撞
    for(int i=0;i<STONE_NUM;i++)
    {
        if(m_backmapobj.stones[i].m_free==false)
        {
            for(int j=0;j<BULLET_NUM;j++)
            {
                if(m_mytankobj.m_bullets[j].m_free==false)
                {
                    if(m_backmapobj.stones[i].m_Rect.intersects(m_mytankobj.m_bullets[j].m_RectUP))
                    {
                        m_mytankobj.m_bullets[j].m_free=true;//闲置子弹
                        break;
                    }
                }
            }

        }
    }
    //敌人子弹碰撞
    for(int i=0;i<ENEMY_NUM;i++)
    {
        for(int j=0;j<BULLET_NUM;j++)
        {

            for(int k=0;k<STONE_NUM;k++)
            {
                if(m_backmapobj.stones[k].m_free==false)
                {
                    if(m_enemyobj[i].m_enemyBullets[j].m_RectUP.intersects(m_backmapobj.stones[k].m_Rect))
                    {
                        m_enemyobj[i].m_enemyBullets[j].m_free=true;
                        break;
                    }
                }
            }

        }
    }

    //吃buff
    for(int i=0;i<BUFF_NUM;i++)
    {
        if(m_buffs[i].m_free==false)
        {
            if(m_buffs[i].m_Rect.intersects(m_mytankobj.m_mytankRect))
            {
                m_buffs[i].m_free=true;
                m_buffs[i].m_bufftimer=0;
                speedup_buff_last=BUFF_LAST;
            }
        }
    }
}

void MainScene::reborn()
{
    if(m_mytankobj.isalive==true)return;
    m_mytankobj.mytank_second++;
    if(m_mytankobj.mytank_second==REBORN_INTERVAL)
    {
        m_mytankobj.isalive=true;
        m_mytankobj.initMytankPosition();
        m_mytankobj.mytank_second=0;
    }

}

void MainScene::isDftOrScs()
{
    if(m_mytankobj.lives==0)m_myhomeobj.isalive=false;
    if(m_myhomeobj.isalive&&m_enemyhomeobj.isalive)return;
    if(m_enemyhomeobj.isalive==false)m_enemyhomeobj.bomb_timer++;//给他足够时间让他爆炸动画结束的bug
    if(m_myhomeobj.isalive==false)m_myhomeobj.bomb_timer++;
    if(m_enemyhomeobj.isalive==false&&m_enemyhomeobj.bomb_timer==35)
    {
        m_enemyhomeobj.bomb_timer=0;
        if(nowMap==1)
        {
            tip.iswin=1;
            tip.show();
        }
        else
        {
            passit.show();
        }
    }
    if(m_myhomeobj.isalive==false&&m_myhomeobj.bomb_timer==35)
    {
        loseit.show();
        m_Timer.stop();
    }

}

void MainScene::goSecondMap()
{
    m_mytankobj.mytank_second=REBORN_INTERVAL-1;
    nowMap=2;
    m_enemyhomeobj.isalive=true;//敌人老家复活
    m_enemyhomeobj.hp=8;
    m_myhomeobj.hp=5;
    m_mytankobj.lives=5;
    for(int i=0;i<ENEMY_NUM;i++)m_enemyobj[i].m_free=true;//敌人滚蛋
    m_mytankobj.isalive=false;//我死
    m_backmapobj.initScondMap();//重置场景

}

void MainScene::buffToSence()
{
    if(speedup_buff_last>0)
    {
        m_mytankobj.step=2;
        speedup_buff_last--;
    }
    else m_mytankobj.step=1;

    for(int i=0;i<BUFF_NUM;i++)
    {
        if(m_buffs[i].m_free==true)
        {
            m_buffs[i].m_bufftimer++;
            break;
        }
    }
    for(int i=0;i<BUFF_NUM;i++)
    {
        if(m_buffs[i].m_free==true&&m_buffs[i].m_bufftimer==BUFF_IN_INTERVAL)
        {
            m_buffs[i].m_free=false;
            m_buffs[i].m_bufftimer=0;
            int newx=rand()%1280;
            int newy=rand()%960;
            m_buffs[i].setPosition(newx,newy);
            int flag=1;
            //不与墙壁重合
            for(int j=0;j<WALL_NUM;j++)
            {
                if(m_backmapobj.walls[j].m_free==false)
                {
                    if(m_backmapobj.walls[j].m_WallRect.intersects(m_buffs[i].m_Rect))
                    {
                        flag=0;
                        break;
                    }
                }
            }
            if(flag)
            {
                for(int j=0;j<STONE_NUM;j++)
                {
                    if(m_backmapobj.stones[j].m_free==false)
                    {
                        if(m_backmapobj.stones[j].m_Rect.intersects(m_buffs[i].m_Rect))
                        {
                            flag=0;
                            break;
                        }
                    }
                }
            }
            while(flag==0)
            {
                flag=1;
                newx=rand()%1280;
                newy=rand()%960;
                m_buffs[i].setPosition(newx,newy);
                for(int j=0;j<WALL_NUM;j++)
                {
                    if(m_backmapobj.walls[j].m_free==false)
                    {
                        if(m_backmapobj.walls[j].m_WallRect.intersects(m_buffs[i].m_Rect))
                        {
                            flag=0;
                            break;
                        }
                    }
                }
                if(flag)
                {
                    for(int j=0;j<STONE_NUM;j++)
                    {
                        if(m_backmapobj.stones[j].m_free==false)
                        {
                            if(m_backmapobj.stones[j].m_Rect.intersects(m_buffs[i].m_Rect))
                            {
                                flag=0;
                                break;
                            }
                        }
                    }
                }
            }
            m_buffs[i].setPosition(newx,newy);
            break;
        }
    }
}



MainScene::~MainScene()
{
}

