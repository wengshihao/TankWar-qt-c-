#ifndef TREE_H
#define TREE_H

#include <config.h>
#include<QPixmap>
#include<QRect>
class Tree
{
public:
    Tree();
    void setTreePosition(int x,int y);

public:
    QPixmap m_tree;
    int m_X;
    int m_Y;
    bool m_free;
    QRect m_TreeRect;


};

#endif // TREE_H
