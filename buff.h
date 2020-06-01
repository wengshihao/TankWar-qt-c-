#ifndef BUFF_H
#define BUFF_H

#include <config.h>
#include<QPixmap>
#include<QRect>
class buff
{
public:
    buff();
    QPixmap m_speedup_buff;
    int m_X;
    int m_Y;
    bool m_free;
    int m_bufftimer;
    QRect m_Rect;
    void setPosition(int x,int y);
};

#endif // BUFF_H
