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


void open_welcome_interface();   //开启游戏界面
void init_chessboard();          //初始化棋盘
void set_button_on_mode();       //设置模式选择页面界面上相应的按钮
void PVE_level_button();         //加载PVE中选择难度的按钮
void draw0();                    //绘制开始界面
void draw_PVP();                 //绘制PVP界面
void PVE_order_button();         //加载PVE选择先后手的按钮
void draw_PVE();                 //绘制PVE界面
void draw_EVE();                 //绘制EVE界面
void button_move(ExMessage* msg);//标红鼠标所指位置处的按钮
void button_down(ExMessage* msg);//选择模式界面点击按钮
