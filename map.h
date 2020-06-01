#ifndef MAP_H
#define MAP_H
#include<QPixmap>
#include"wall.h"
#include"config.h"
#include<QMap>
#include "tree.h"
#include "stone.h"
class Map
{
public:
    Map();

    //地图坐标
    void mapPosition();
    void initWall();
    void initScondMap();

public:
    QPixmap m_backmap;
    QPixmap m_mylogo;
    QPixmap m_tipback;
    int m_backmap_positionY;
    Wall walls[WALL_NUM];
    Tree trees[TREE_NUM];
    Stone stones[STONE_NUM];
};

#endif // MAP_H
