#ifndef CONFIG_H
#define CONFIG_H

//游戏界面配置
#define GAME_WIDTH 1280//宽度
#define GAME_HEIGHT 960//高度
#define GAME_NAME "坦克大战"
#define GAME_RESOURCE_PATH "./resource.rcc"  //rcc路径
#define GAME_ICON ":/resource/u=529426770,2724737800&fm=26&gp=0.jpg" //程序图标路径
#define GAME_RATE 10 //游戏帧率

#define BACK_MAP_PATH ":/resource/backg.gif" //背景图片路径

#define MY_TANK1_PATH ":/resource/GoodTank1.png" //玩家坦克图片
#define MY_TANK2_PATH ":/resource/GoodTank2.png"
#define MY_TANK3_PATH ":/resource/GoodTank3.png"
#define MY_TANK4_PATH ":/resource/GoodTank4.png"

#define BULLETUP_PATH ":/resource/bulletU.gif"//子弹图片
#define BULLETDOWN_PATH ":/resource/bulletD.gif"
#define BULLETLEFT_PATH ":/resource/bulletL.gif"
#define BULLETRIGHT_PATH ":/resource/bulletR.gif"

#define ENEMY_TANK_UP_PATH ":/resource/enemyup.png"
#define ENEMY_TANK_DOWN_PATH ":/resource/enemydown.png"
#define ENEMY_TANK_LEFT_PATH ":/resource/enemyleft.png"
#define ENEMY_TANK_RIGHT_PATH ":/resource/enemyright.png"

#define BULLET_SPEED 5//子弹速度
#define BULLET_NUM 50//弹夹容量

#define ENEMY_NUM 5 //敌人数量
#define ENEMY_TRUN_RATE 200 //敌人拐弯频率

#define BOMB_PATH1 ":/resource/e1.gif"//爆炸图片路径
#define BOMB_PATH2 ":/resource/e2.gif"
#define BOMB_PATH3 ":/resource/e3.gif"
#define BOMB_PATH4 ":/resource/e4.gif"
#define BOMB_PATH5 ":/resource/e5.gif"
#define BOMB_PATH6 ":/resource/e6.gif"
#define BOMB_PATH7 ":/resource/e7.gif"
#define BOMB_PATH8 ":/resource/e8.gif"
#define BOMB_PATH9 ":/resource/e9.gif"
#define BOMB_PATH10 ":/resource/e10.gif"
#define BOMB_PATH11 ":/resource/e11.gif"
#define BOMB_PATH12 ":/resource/e12.gif"
#define BOMB_PATH13 ":/resource/e13.gif"
#define BOMB_PATH14 ":/resource/e14.gif"
#define BOMB_PATH15 ":/resource/e15.gif"
#define BOMB_PATH16 ":/resource/e16.gif"

#define BOMB_NUM 20 //爆炸数量
#define BOMB_IMAGENUM 16//爆炸图片数量
#define BOMB_INTERCAL 6//爆炸时间间隔

#define WALL_PATH ":/resource/square0.jpg"//墙壁路径
#define WALL_NUM 1500 //墙壁数量
#define WALL_SIZE 16//墙壁边长
#define WALL 1//令1为墙壁

#define ENEMY_SHOT_RATE 80//敌人发射子弹频率

#define REBORN_INTERVAL 200//复活时间

#define MYHOME_PATH ":/resource/home.png"
#define ENEMYHOME_PATH ":/resource/home1.png"

#define TREE_PATH ":/resource/tree.png"

#define TREE_NUM 400 //树林数量
#define TREE_SIZE 16//树林边长

#define STONE_PATH ":/resource/stone.png"
#define STONE_NUM 400 //石头数量
#define STONE_SIZE 16 //石头边长

#define YUKINO ":/resource/mylogo.png"
#define TIP_BACK_PATH ":/resource/tipback.png"

#define LOVE_PASS_PATH ":/resource/cgtpass.png"//通关爱心
#define WINTHEGAME ":/resource/winthegame.png"
#define LOSETHEGAME ":/resource/losethegame.png"

#define SPEED_UP_PATH ":/resource/speedup.png"
#define BUFF_NUM 4

#define BUFF_IN_INTERVAL 500//buff出现的时间
#define BUFF_LAST 2000//buff持续时间

#endif // CONFIG_H
