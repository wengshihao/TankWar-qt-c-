#include "map.h"
#include "config.h"
#include <QDebug>
Map::Map()
{
    //地图背景图片操作
    m_backmap.load(BACK_MAP_PATH);//加载图片
    m_mylogo.load(YUKINO);
    m_tipback.load(TIP_BACK_PATH);
    m_backmap_positionY=0;
}

void Map::mapPosition()
{
    m_backmap_positionY=0;
}

void Map::initWall()//设置地图中的事物
{
    //画四列竖着的墙

    for(int p=0;p<6;p++)
    {
        int begx=0;
        int num;
        if(p==0)begx=100,num=15;
        else if(p==1)begx=350,num=15;
        else if(p==4)begx=550,num=6;
        else if(p==5)begx=900-200,num=6;
        else if(p==2)begx=900,num=15;
        else if(p==3)begx=1150,num=15;
        int i,j;
        int begy=100;
        if(p==4||p==5)begy=150;
        for(i=begx;i<begx+WALL_SIZE*3;i+=WALL_SIZE)
        {
            for(j=begy;j<begy+WALL_SIZE*num;j+=WALL_SIZE)
            {
                for(int k=0;k<WALL_NUM;k++)
                {
                    if(walls[k].m_free==true)
                    {
                        //qDebug("%d %d",i,j);
                        walls[k].m_free=false;
                        walls[k].setWallPosition(i,j);
                        break;
                    }
                }
            }
        }
        //qDebug("%d %d\n",i,j);
        begx=i-3*WALL_SIZE;
        begy=j+200;
        //qDebug("%d %d\n",begx,begy);
        for(i=begx;i<begx+WALL_SIZE*3;i+=WALL_SIZE)
        {
            for(j=begy;j<begy+WALL_SIZE*num;j+=WALL_SIZE)
            {
                for(int k=0;k<WALL_NUM;k++)
                {
                    if(walls[k].m_free==true)
                    {
                        //qDebug("%d %d",i,j);

                        walls[k].m_free=false;
                        walls[k].setWallPosition(i,j);
                        break;
                    }
                }
            }
        }
    }

    //画两行横着的墙
    int begx,begy;
    for(int i=0;i<2;i++)
    {
      if(i==0)begx=170;
      else begx=170+800;
      begy=180+250;
      for(int i=begx;i<begx+WALL_SIZE*10;i+=WALL_SIZE)
      {
          for(int j=begy;j<begy+WALL_SIZE*3;j+=WALL_SIZE)
          {
              for(int k=0;k<WALL_NUM;k++)
              {
                  if(walls[k].m_free==true)
                  {
                      //qDebug("%d %d",i,j);

                      walls[k].m_free=false;
                      walls[k].setWallPosition(i,j);
                      break;
                  }
              }
          }
        }
    }
    //画围绕老家的墙壁

    begx=550;
    begy=960;
    for(int i=begx;i<begx+WALL_SIZE*3;i+=WALL_SIZE)
    {
        for(int j=begy;j>begy-WALL_SIZE*8;j-=WALL_SIZE)
        {
            for(int k=0;k<WALL_NUM;k++)
            {
                if(walls[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);

                    walls[k].m_free=false;
                    walls[k].setWallPosition(i,j);
                    break;
                }
            }
        }
    }
    begx=720;
    begy=960;
    for(int i=begx;i<begx+WALL_SIZE*3;i+=WALL_SIZE)
    {
        for(int j=begy;j>begy-WALL_SIZE*8;j-=WALL_SIZE)
        {
            for(int k=0;k<WALL_NUM;k++)
            {
                if(walls[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);

                    walls[k].m_free=false;
                    walls[k].setWallPosition(i,j);
                    break;
                }
            }
        }
    }
    begx=580;
    begy=830;
    for(int i=begx;i<begx+WALL_SIZE*10;i+=WALL_SIZE)
    {
        for(int j=begy;j>begy-WALL_SIZE*3;j-=WALL_SIZE)
        {
            for(int k=0;k<WALL_NUM;k++)
            {
                if(walls[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);

                    walls[k].m_free=false;
                    walls[k].setWallPosition(i,j);
                    break;
                }
            }
        }
    }

    //敌人老家墙壁
    begx=550;
    begy=0;
    for(int i=begx;i<begx+WALL_SIZE*3;i+=WALL_SIZE)
    {
        for(int j=begy;j<begy+WALL_SIZE*6;j+=WALL_SIZE)
        {
            for(int k=0;k<WALL_NUM;k++)
            {
                if(walls[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);

                    walls[k].m_free=false;
                    walls[k].setWallPosition(i,j);
                    break;
                }
            }
        }
    }
    begx=550+WALL_SIZE*11;
    begy=0;
    for(int i=begx;i<begx+WALL_SIZE*3;i+=WALL_SIZE)
    {
        for(int j=begy;j<begy+WALL_SIZE*6;j+=WALL_SIZE)
        {
            for(int k=0;k<WALL_NUM;k++)
            {
                if(walls[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);

                    walls[k].m_free=false;
                    walls[k].setWallPosition(i,j);
                    break;
                }
            }
        }
    }
    begy=begy+WALL_SIZE*6;
    for(int i=550+STONE_SIZE;i<550+STONE_SIZE*12;i+=STONE_SIZE)
    {
        for(int k=0;k<STONE_NUM;k++)
        {
            if(stones[k].m_free==true)
            {
                //qDebug("%d %d",i,j);
                stones[k].m_free=false;
                stones[k].setStonePosition(i,begy);
                break;
            }
        }
    }





      //设置树林
    //中间一块
    begx=GAME_WIDTH/2-5*TREE_SIZE;
    begy=GAME_HEIGHT/2-13*TREE_SIZE;
    for(int i=begx;i<begx+TREE_SIZE*12;i+=TREE_SIZE)
    {
        for(int j=begy;j<begy+TREE_SIZE*11;j+=TREE_SIZE)
        {
            for(int k=0;k<TREE_NUM;k++)
            {
                if(trees[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    trees[k].m_free=false;
                    trees[k].setTreePosition(i,j);
                    break;
                }
            }
        }
    }

    //左边一块
    begx=200;
    begy=100;
    for(int i=begx;i<begx+TREE_SIZE*5;i+=TREE_SIZE)
    {
        for(int j=begy;j<begy+TREE_SIZE*11;j+=TREE_SIZE)
        {
            for(int k=0;k<TREE_NUM;k++)
            {
                if(trees[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    trees[k].m_free=false;
                    trees[k].setTreePosition(i,j);
                    break;
                }
            }
        }
    }
    begx=200;
    begy=600;
    for(int i=begx;i<begx+TREE_SIZE*5;i+=TREE_SIZE)
    {
        for(int j=begy;j<begy+TREE_SIZE*8;j+=TREE_SIZE)
        {
            for(int k=0;k<TREE_NUM;k++)
            {
                if(trees[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    trees[k].m_free=false;
                    trees[k].setTreePosition(i,j);
                    break;
                }
            }
        }
    }

    //右边一块
    begx=1000;
    begy=100;
    for(int i=begx;i<begx+TREE_SIZE*5;i+=TREE_SIZE)
    {
        for(int j=begy;j<begy+TREE_SIZE*11;j+=TREE_SIZE)
        {
            for(int k=0;k<TREE_NUM;k++)
            {
                if(trees[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    trees[k].m_free=false;
                    trees[k].setTreePosition(i,j);
                    break;
                }
            }
        }
    }
    begx=1000;
    begy=600;
    for(int i=begx;i<begx+TREE_SIZE*5;i+=TREE_SIZE)
    {
        for(int j=begy;j<begy+TREE_SIZE*8;j+=TREE_SIZE)
        {
            for(int k=0;k<TREE_NUM;k++)
            {
                if(trees[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    trees[k].m_free=false;
                    trees[k].setTreePosition(i,j);
                    break;
                }
            }
        }
    }


    //石头

    begx=GAME_WIDTH/2-100+10;
    begy=GAME_HEIGHT/2+150;
    for(int i=begx;i<begx+STONE_SIZE*13;i+=STONE_SIZE)
    {
        for(int k=0;k<STONE_NUM;k++)
        {
            if(stones[k].m_free==true)
            {
                //qDebug("%d %d",i,j);
                stones[k].m_free=false;
                stones[k].setStonePosition(i,begy);
                break;
            }
        }
    }
    begx=0;
    begy=100+STONE_SIZE;
    for(int i=begx;i<begx+STONE_SIZE*6;i+=STONE_SIZE)
    {
        for(int j=begy;j<begy+STONE_SIZE*5;j+=STONE_SIZE)
        {
            for(int k=0;k<STONE_NUM;k++)
            {
                if(stones[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    stones[k].m_free=false;
                    stones[k].setStonePosition(i,j);
                    break;
                }
            }

        }
    }
    begx=0;
    begy=700;
    for(int i=begx;i<begx+STONE_SIZE*6;i+=STONE_SIZE)
    {
        for(int j=begy;j<begy+STONE_SIZE*4;j+=STONE_SIZE)
        {
            for(int k=0;k<STONE_NUM;k++)
            {
                if(stones[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    stones[k].m_free=false;
                    stones[k].setStonePosition(i,j);
                    break;
                }
            }

        }
    }
    begx=GAME_WIDTH-5*STONE_SIZE;
    begy=700;
    for(int i=begx;i<begx+STONE_SIZE*5;i+=STONE_SIZE)
    {
        for(int j=begy;j<begy+STONE_SIZE*4;j+=STONE_SIZE)
        {
            for(int k=0;k<STONE_NUM;k++)
            {
                if(stones[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    stones[k].m_free=false;
                    stones[k].setStonePosition(i,j);
                    break;
                }
            }

        }
    }
    begx=GAME_WIDTH-5*STONE_SIZE;
    begy=100+WALL_SIZE;
    for(int i=begx;i<begx+STONE_SIZE*5;i+=STONE_SIZE)
    {
        for(int j=begy;j<begy+STONE_SIZE*5;j+=STONE_SIZE)
        {
            for(int k=0;k<STONE_NUM;k++)
            {
                if(stones[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    stones[k].m_free=false;
                    stones[k].setStonePosition(i,j);
                    break;
                }
            }

        }
    }


}

void Map::initScondMap()
{
    //场景重置
    for(int i=0;i<WALL_NUM;i++)walls[i].m_free=true;
    for(int i=0;i<STONE_NUM;i++)stones[i].m_free=true;
    for(int i=0;i<TREE_NUM;i++)trees[i].m_free=true;

    int begx,begy;
    begx=0;
    begy=200;
    for(int i=begx;i<=1000;i+=WALL_SIZE)
    {
        for(int j=begy;j<begy+WALL_SIZE*3;j+=WALL_SIZE)
        {
            for(int k=0;k<WALL_NUM;k++)
            {
                if(walls[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);

                    walls[k].m_free=false;
                    walls[k].setWallPosition(i,j);
                    break;
                }
            }
        }
    }

    begx=1016;
    begy=200;
    for(int i=begx;i<=1280;i+=WALL_SIZE)
    {
        for(int j=begy;j<begy+WALL_SIZE*3;j+=WALL_SIZE)
        {
            for(int k=0;k<TREE_NUM;k++)
            {
                if(trees[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    trees[k].m_free=false;
                    trees[k].setTreePosition(i,j);
                    break;
                }
            }
        }
    }

    begx=280;
    begy=400;
    for(int i=begx;i<=1280;i+=WALL_SIZE)
    {
        for(int j=begy;j<begy+WALL_SIZE*3;j+=WALL_SIZE)
        {
            for(int k=0;k<WALL_NUM;k++)
            {
                if(walls[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);

                    walls[k].m_free=false;
                    walls[k].setWallPosition(i,j);
                    break;
                }
            }
        }
    }

    begx=0;
    begy=400;
    for(int i=begx;i+WALL_SIZE<=280;i+=WALL_SIZE)
    {
        for(int j=begy;j<begy+WALL_SIZE*3;j+=WALL_SIZE)
        {
            for(int k=0;k<TREE_NUM;k++)
            {
                if(trees[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    trees[k].m_free=false;
                    trees[k].setTreePosition(i,j);
                    break;
                }
            }
        }
    }


    begx=0;
    begy=600;
    for(int i=begx;i<=1000;i+=WALL_SIZE)
    {
        for(int j=begy;j<begy+WALL_SIZE*3;j+=WALL_SIZE)
        {
            for(int k=0;k<WALL_NUM;k++)
            {
                if(walls[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);

                    walls[k].m_free=false;
                    walls[k].setWallPosition(i,j);
                    break;
                }
            }
        }
    }
    begx=1016;
    begy=600;
    for(int i=begx;i<=1280;i+=WALL_SIZE)
    {
        for(int j=begy;j<begy+WALL_SIZE*3;j+=WALL_SIZE)
        {
            for(int k=0;k<TREE_NUM;k++)
            {
                if(trees[k].m_free==true)
                {
                    //qDebug("%d %d",i,j);
                    trees[k].m_free=false;
                    trees[k].setTreePosition(i,j);
                    break;
                }
            }
        }
    }

    begx=400;
    begy=100;
    for(int i=begx;i<begx+STONE_SIZE*35;i+=STONE_SIZE)
    {
        for(int k=0;k<STONE_NUM;k++)
        {
            if(stones[k].m_free==true)
            {
                //qDebug("%d %d",i,j);
                stones[k].m_free=false;
                stones[k].setStonePosition(i,begy);
                break;
            }
        }
    }



}







