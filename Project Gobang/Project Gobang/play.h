#pragma once

#define ROWS 15         //行数，国际标准棋盘15x15
#define COLUMNS 15      //列数，国际标准棋盘15x15
#define INTERVAL 30     //棋盘间隔
#define black 1         //黑棋
#define white 2         //白棋
#define xian 1          //先手
#define hou 0           //后手
#define easy 100        //简单模式
#define medium 10       //中等模式
#define hard 1          //困难模式

extern IMAGE background;//背景图片
extern int mode;//0代表初始，1、2、3、4为四个功能
extern int chessboard[ROWS][COLUMNS];//定义棋盘
extern bool heqi;//判断是否和棋
extern int result;//判断点击了确定或取消,0：未操作
extern int dierbu;//0：走下一步；2：IDCANCEL终止
extern int level1;//设置难度：easy简单，medium中等，hard困难(有宏定义)
extern int panduan;//判断是否设置了难度



void choose_level(ExMessage* msg2); //选择难度
void choose_order(ExMessage* msg2); //选择先后手
bool judge(int r, int c);           //判断游戏是否结束
void pve_press(ExMessage* msg);     //PVE下棋
void mouse_move(ExMessage* msg);    //鼠标移动显示棋子落点
void mouse_press(ExMessage* msg);   //点击鼠标下棋
void ai(int level1);                //AI算法，计算对应权值并比较(越简单的模式，对于四子的权值越低，两子的权值越高)