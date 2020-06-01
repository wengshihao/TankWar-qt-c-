#include "buff.h"

buff::buff()
{
    m_speedup_buff.load(SPEED_UP_PATH);
    m_free=true;
    m_Rect.setWidth(m_speedup_buff.width());
    m_Rect.setHeight(m_speedup_buff.height());
    m_bufftimer=0;
}

void buff::setPosition(int x, int y)
{
    m_X=x;
    m_Y=y;
    m_Rect.moveTo(m_X,m_Y);
}
