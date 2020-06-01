#include "tree.h"
#include "config.h"
Tree::Tree()
{
    m_tree.load(TREE_PATH);

    m_X=0;
    m_Y=0;
    m_free=true;
    m_TreeRect.setWidth(m_tree.width());
    m_TreeRect.setHeight(m_tree.height());
    m_TreeRect.moveTo(m_X,m_Y);
}

void Tree::setTreePosition(int x, int y)
{
    m_X=x;
    m_Y=y;
    m_TreeRect.moveTo(m_X,m_Y);
}



