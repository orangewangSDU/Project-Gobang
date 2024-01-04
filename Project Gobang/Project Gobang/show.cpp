#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<graphics.h>
#include"show.h"
#include"play.h"
#include"fupan.h"
#include"Mystruct.h"

void open_welcome_interface()    //开启游戏界面
{
	initgraph(800, 800);
	loadimage(&background, "background.jpg", 800, 800);
	putimage(0, 0, &background);
}

void init_chessboard()   //初始化棋盘
{
	setbkcolor(YELLOW);//设置背景颜色为黄色
	cleardevice();
	for (int i = 0; i < 15; i++)
	{
		setlinestyle(PS_SOLID, 2);//线形为实线，宽度为2
		setlinecolor(BLACK);//线的颜色设置为黑色
		line(90, 90 + i * INTERVAL, 90 + 14 * INTERVAL, 90 + i * INTERVAL);//横线
		line(90 + i * INTERVAL, 90, 90 + i * INTERVAL, 90 + 14 * INTERVAL);//竖线
	}
	setlinestyle(PS_SOLID, 4);
	setlinecolor(BLACK);
	rectangle(90, 90, 90 + 14 * INTERVAL, 90 + 14 * INTERVAL);//边框适当加粗
	setfillcolor(BLACK);
	//棋盘上有五个点需要重点标记，符合棋盘特征
	solidcircle(90 + 7 * INTERVAL, 90 + 7 * INTERVAL, 5);
	solidcircle(90 + 3 * INTERVAL, 90 + 3 * INTERVAL, 5);
	solidcircle(90 + 11 * INTERVAL, 90 + 11 * INTERVAL, 5);
	solidcircle(90 + 3 * INTERVAL, 90 + 11 * INTERVAL, 5);
	solidcircle(90 + 11 * INTERVAL, 90 + 3 * INTERVAL, 5);
}

void set_button_on_mode()//设置模式选择页面界面上相应的按钮
{
	setbkmode(TRANSPARENT);
	settextstyle(70, 40, _T("宋体"));//设置文字的高度，宽度，字体
	settextcolor(WHITE);
	outtextxy(155, 30, "五子棋 Gobang");//游戏说明
	setlinestyle(PS_SOLID, 4);
	setlinecolor(WHITE);
	rectangle(240, 120, 480, 200);
	setfillcolor(BLACK);
	fillrectangle(240, 120, 480, 200);
	settextstyle(76, 55, _T("Consolas"));
	settextcolor(WHITE);
	outtextxy(265, 122, "PVP");//diyige
	setlinestyle(PS_SOLID, 4);
	setlinecolor(WHITE);
	rectangle(240, 200, 480, 300);
	setfillcolor(BLACK);
	fillrectangle(240, 200, 480, 300);
	settextstyle(76, 55, _T("Consolas"));
	settextcolor(WHITE);
	outtextxy(265, 202, "PVE");//dierge
	setlinestyle(PS_SOLID, 4);
	setlinecolor(WHITE);
	rectangle(240, 280, 480, 400);
	setfillcolor(BLACK);
	fillrectangle(240, 280, 480, 400);
	settextstyle(76, 55, _T("Consolas"));
	settextcolor(WHITE);
	outtextxy(265, 282, "EVE");//disange
	setlinestyle(PS_SOLID, 4);
	setlinecolor(WHITE);
	rectangle(240, 360, 480, 440);
	setfillcolor(BLACK);
	fillrectangle(240, 360, 480, 440);
	settextstyle(76, 40, _T("Consolas"));
	settextcolor(WHITE);
	outtextxy(270, 362, "复盘");//disige
	settextstyle(30, 15, _T("Times New Roman"));
	settextcolor(WHITE);
	setlinecolor(WHITE);
	rectangle(450, 720, 780, 770);
	setfillcolor(BLACK);
	fillrectangle(450, 720, 790, 780);
	outtextxy(450, 720, "Made by Orange Wang");//版权声明
	outtextxy(450, 750, "王奕澄 202200460093");
}

void PVE_level_button()//加载PVE中选择难度的按钮
{
	settextstyle(50, 20, 0);
	settextcolor(BLACK);
	outtextxy(520, 100, "请选择难度：");
	settextstyle(70, 30, 0);
	settextcolor(BLACK);
	outtextxy(570, 200, "简单");
	outtextxy(570, 300, "中等");
	outtextxy(570, 400, "困难");
}

void draw0()   //绘制开始界面
{
	putimage(0, 0, &background);
	set_button_on_mode();
	if (button.flag) //给鼠标所指的选项加红框
	{
		setlinestyle(PS_SOLID, 4);
		setlinecolor(RED);
		rectangle(240, 120 + button.x * 80, 480, 200 + button.x * 80);
	}
}

void draw_PVP()         //绘制PVP界面
{
	putimage(0, 0, &background);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);

	init_chessboard();
	if (mode == 1)
	{
		if (pos.player == black)
		{
			settextstyle(40, 18, 0);
			settextcolor(BLACK);
			outtextxy(580, 250, "该黑棋了");
		}
		if (pos.player == white)
		{
			settextstyle(40, 18, 0);
			settextcolor(BLACK);
			outtextxy(580, 250, "该白棋了");
		}
	}
	for (int i = 0; i < ROWS; i++) //在棋盘上绘制棋子
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (chessboard[i][j] == black)
			{
				setfillcolor(BLACK);
				solidcircle(90 + j * INTERVAL, 90 + i * INTERVAL, 13);
			}
			else if (chessboard[i][j] == white)
			{
				setfillcolor(WHITE);
				solidcircle(90 + j * INTERVAL, 90 + i * INTERVAL, 13);
			}
		}
	}
	if (pos.isshow) //落子位置显示
	{
		setlinestyle(PS_SOLID, 3);
		setlinecolor(BLUE);
		rectangle(pos.col * INTERVAL + 78, pos.row * INTERVAL + 78, pos.col * INTERVAL + 102, pos.row * INTERVAL + 102);
	}
}

void PVE_order_button()//加载PVE选择先后手的按钮
{
	settextstyle(70, 30, 0);
	settextcolor(BLACK);
	outtextxy(550, 100, "请选择：");
	settextstyle(70, 30, 0);
	settextcolor(BLACK);
	outtextxy(570, 200, "先手");
	outtextxy(570, 300, "后手");
}

void draw_PVE()   //绘制PVE界面
{
	putimage(0, 0, &background);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);

	init_chessboard();
	if (result == 0 && panduan == 0)
	{
		PVE_level_button();
		if (levels.ischoose)
		{
			if (levels.level == easy)
			{
				setlinestyle(PS_SOLID, 3);
				setlinecolor(RED);
				rectangle(570, 200, 730, 280);
			}
			if (levels.level == medium)
			{
				setlinestyle(PS_SOLID, 3);
				setlinecolor(RED);
				rectangle(570, 300, 730, 380);
			}
			if (levels.level == hard)
			{
				setlinestyle(PS_SOLID, 3);
				setlinecolor(RED);
				rectangle(570, 400, 730, 480);
			}
		}

	}

	if (mode == 2 && panduan != 0)
	{
		if (pve.turn == 1 && pve.player == black) //提示语
		{
			settextstyle(40, 18, 0);
			settextcolor(BLACK);
			outtextxy(580, 250, "该黑棋了");
		}
		if (pve.turn == 1 && pve.player == white)
		{
			settextstyle(40, 18, 0);
			settextcolor(BLACK);
			outtextxy(580, 250, "该白棋了");
		}
	}

	if (result == 0 && panduan != 0)
	{
		PVE_order_button();
		if (orders.ischoose)
		{
			if (orders.order == 1)
			{
				setlinestyle(PS_SOLID, 3);
				setlinecolor(RED);
				rectangle(570, 200, 730, 280);
			}
			if (orders.order == 2)
			{
				setlinestyle(PS_SOLID, 3);
				setlinecolor(RED);
				rectangle(570, 300, 730, 380);
			}
		}
	}

	for (int i = 0; i < ROWS; i++) //在棋盘上绘制棋子
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (chessboard[i][j] == black)
			{
				setfillcolor(BLACK);
				solidcircle(90 + j * INTERVAL, 90 + i * INTERVAL, 13);
			}
			else if (chessboard[i][j] == white)
			{
				setfillcolor(WHITE);
				solidcircle(90 + j * INTERVAL, 90 + i * INTERVAL, 13);
			}
		}
	}
	if (pos.isshow) //蓝框落子位置显示
	{
		setlinestyle(PS_SOLID, 3);
		setlinecolor(BLUE);
		rectangle(pos.col * INTERVAL + 78, pos.row * INTERVAL + 78, pos.col * INTERVAL + 102, pos.row * INTERVAL + 102);
	}
}

void draw_EVE()    //绘制EVE界面
{
	putimage(0, 0, &background);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);

	init_chessboard();
	for (int i = 0; i < ROWS; i++) //在棋盘上绘制棋子
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (chessboard[i][j] == black)
			{
				setfillcolor(BLACK);
				solidcircle(90 + j * INTERVAL, 90 + i * INTERVAL, 13);
			}
			else if (chessboard[i][j] == white)
			{
				setfillcolor(WHITE);
				solidcircle(90 + j * INTERVAL, 90 + i * INTERVAL, 13);
			}
		}
	}
	if (pos.isshow) //落子位置显示
	{
		setlinestyle(PS_SOLID, 3);
		setlinecolor(BLUE);
		rectangle(pos.col * INTERVAL + 78, pos.row * INTERVAL + 78, pos.col * INTERVAL + 102, pos.row * INTERVAL + 102);
	}
}

void button_move(ExMessage* msg)//标红鼠标所指位置处的按钮
{
	for (int i = 0; i < 4; i++) //一共四个按钮
	{
		if (msg->x >= 239 && msg->x <= 481) //x坐标的范围
		{
			if (msg->y >= 119 + i * 80 && msg->y <= 201 + i * 80) //y坐标的范围
			{
				button.flag = true;
				button.x = i;
			}
		}
	}
}

void button_down(ExMessage* msg)//选择模式界面点击按钮
{
	mode = button.x + 1;
	if (mode != 4)
	{
		FILE* fp;
		fp = fopen("duiju.txt", "r");
		if (fp == NULL)//r:文件必须存在，只允许读
		{
			int e = MessageBox(GetHWnd(), "存储对局信息的文件不存在或打开失败，即将为您创建！", "提醒", MB_OK);
			fp = fopen("duiju.txt", "w");
			fclose(fp);
		}
		else
		{
			fp = fopen("duiju.txt", "w");//文件存在的话先把权限改为w,用"w"打开的文件只能向该文件写入。若打开的文件不存在，则以指定的文件名建立该文件，若打开的文件已经存在，则将该文件删去，重建一个新文件。
			fclose(fp);
		}
	}
}