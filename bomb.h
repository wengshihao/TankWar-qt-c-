#ifndef BOMB_H
#define BOMB_H
#include<QPixmap>
#include<QVector>

class Bomb
{
public:
    Bomb();

    void updateNoBomb();

public:
    QVector<QPixmap>m_pixarr;//存放爆炸图片

    //爆炸位置
    int m_bombX;
    int m_bombY;

    bool m_free;//爆炸状态
    int m_recoder;//爆炸切图时间戳
    int m_index;//加载图片的下标


};

#endif // BOMB_H
