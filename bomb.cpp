#include "bomb.h"
#include "config.h"
Bomb::Bomb()
{
    for(int i=1;i<=BOMB_IMAGENUM;i++)//加载所有爆炸图片
    {
        QString bombPath;
        switch (i) {
            case 1:bombPath=BOMB_PATH1;break;
            case 2:bombPath=BOMB_PATH2;break;
            case 3:bombPath=BOMB_PATH3;break;
            case 4:bombPath=BOMB_PATH4;break;
            case 5:bombPath=BOMB_PATH5;break;
            case 6:bombPath=BOMB_PATH6;break;
            case 7:bombPath=BOMB_PATH7;break;
            case 8:bombPath=BOMB_PATH8;break;
            case 9:bombPath=BOMB_PATH9;break;
            case 10:bombPath=BOMB_PATH10;break;
            case 11:bombPath=BOMB_PATH11;break;
            case 12:bombPath=BOMB_PATH12;break;
            case 13:bombPath=BOMB_PATH13;break;
            case 14:bombPath=BOMB_PATH14;break;
            case 15:bombPath=BOMB_PATH15;break;
            case 16:bombPath=BOMB_PATH16;break;
        }
        m_pixarr.push_back(QPixmap(bombPath));
    }

    //初始化爆炸坐标
    m_bombX=0;
    m_bombY=0;

    m_free=true;//初始化爆炸闲置

    m_index=0;//当前播放图片下标

    m_recoder=0;//爆炸间隔

}

void Bomb::updateNoBomb()
{
    if(m_free==true)return;//空闲状态的不爆炸
    m_recoder++;
    if(m_recoder<BOMB_INTERCAL)return;//未到达爆炸点，不切图
    m_recoder=0;//重置爆炸时间戳
    m_index++;//切图
    if(m_index>BOMB_IMAGENUM-1)//重置下标
    {
        m_index=0;
        m_free=true;
    }

}
