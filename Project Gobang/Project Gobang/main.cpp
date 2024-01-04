//***********************************
//*  项目：Project Gobang
//*  程序：main.cpp                                       *
//*  功能：实现简单的五子棋小游戏                         *
//*        包含简单的PVP，PVE，EVE模式，并能够进行复盘    *
//*  作者：王奕澄，最后修改时间：2023年12月13日           *  
//*  学号：202200460093
//************************************

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include"show.h"
#include"play.h"
#include"fupan.h"

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

int chessboard[ROWS][COLUMNS];//定义棋盘
IMAGE background;//背景图片
int mode = 0;//0代表初始，1、2、3、4为四个功能
bool heqi = 0;//判断是否和棋
int result = 0;//判断点击了确定或取消,0：未操作
int dierbu = 0;//0：走下一步；2：IDCANCEL终止
int level1 = 0;//设置难度：easy简单，medium中等，hard困难(有宏定义)
int panduan = 0;//判断是否设置了难度

struct Order
{
	bool ischoose;
	int order;    //先手为1（xian），后手为0（hou）
}orders;

struct Level
{
	bool ischoose;
	int level;   //easy简单，medium中等，hard困难
}levels;

struct Button
{
	int x;     //第几个按钮
	bool flag; //是否标红
}button = { -1,false };

struct play  //pve和eve复用一个结构体
{
	int AI;    //AI或ai1
	int player;//玩家或ai2
	int turn;  //1:到你了;0:不到你;3:结束（因为取消为2所以不能用2了）
}pve;

struct Pos
{
	int row;
	int col;
	bool isshow;//是否显示落子位置
	int player;
}pos = { -1,-1,false,1 };//显示行列与判断

int main()
{
	open_welcome_interface();
	set_button_on_mode();
	ExMessage msg;//存储鼠标消息的变量
	while (true)
	{
		if (mode == 0)//主界面
		{
			BeginBatchDraw();
			draw0();
			EndBatchDraw();
			if (peekmessage(&msg, EX_MOUSE))
			{
				switch (msg.message)
				{
				case WM_MOUSEMOVE:
					button_move(&msg);
					break;
				case WM_LBUTTONDOWN:
					button_down(&msg);
					break;
				default:
					break;
				}
			}
		}
		if (mode == 1)//PVP界面
		{	
			BeginBatchDraw();
			draw_PVP();
			EndBatchDraw();
			ExMessage msg;
			if (peekmessage(&msg, EX_MOUSE)) 
			{
				switch (msg.message) 
				{
				case WM_MOUSEMOVE:
					mouse_move(&msg);
					break;
				case WM_LBUTTONDOWN:
					mouse_press(&msg);
					break;
				default:
					break;
				}
			}			
		}
		if (mode == 2)//PVE界面
		{
			BeginBatchDraw();
			draw_PVE();
			EndBatchDraw();
			if (panduan== 0)
			{
				if (peekmessage(&msg, EX_MOUSE))
				{	
					choose_level(&msg);
				}
			}
			level1 = levels.level;//设置ai算法难度
			if (result == 0&&levels.level!=0) 
			{
				pve.turn = 3;
				if (peekmessage(&msg, EX_MOUSE)) 
				{				
					choose_order(&msg);
				}
			}

			if (result != 0) 
			{
				if (result == IDOK) 
				{
					pve.AI = black;
					pve.player = white;
					pve.turn = 0;
					result = 3;
				}
				if (result == IDCANCEL)
				{
					pve.AI = white;
					pve.player = black;
					pve.turn = 1;
					result = 3;
				}
				if (pve.turn == 1) 
				{
					ExMessage msg;
					if (peekmessage(&msg, EX_MOUSE)) 
					{
						switch (msg.message) 
						{
						case WM_MOUSEMOVE:
							mouse_move(&msg);
							break;
						case WM_LBUTTONDOWN:
							pve_press(&msg);
							break;
						default:
							break;
						}
					}
				}//玩家下棋
				else if (pve.turn == 0) //电脑下棋
				{
					ai(level1);
				}
			}
		}
		if (mode == 3)//EVE界面
		{
			dierbu = 0;
			BeginBatchDraw();
			draw_EVE();
			EndBatchDraw();
			pve.AI = black;
			pve.player = white;
			ai(hard);//直接上困难模式
			if (dierbu != 2) 
			{
				BeginBatchDraw();
				draw_EVE();
				EndBatchDraw();
				pve.AI =  white;
				pve.player = black;
				ai(hard);
			}
		}
		if (mode == 4)//复盘
		{
			fupan();
			int qu = MessageBox(GetHWnd(), "是否再次复盘", "复盘结束", MB_OKCANCEL);
			if (qu == IDCANCEL) 
			{
				for (int i = 0; i < 15; i++) 
				{
					for (int j = 0; j < 15; j++) 
					{
						chessboard[i][j] = 0;
					}
				}//扫干净棋盘
				mode = 0;
			}
			if (qu == IDOK) 
			{
				for (int i = 0; i < 15; i++) 
				{
					for (int j = 0; j < 15; j++) 
					{
						chessboard[i][j] = 0;
					}
				}//扫干净棋盘
				mode = 4;
			}
		}		
	}
	getchar();//延迟退出便于调试
	return 0;
}