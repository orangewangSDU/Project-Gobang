#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<graphics.h>
#include"show.h"
#include"play.h"
#include"fupan.h"
#include"Mystruct.h"

void draw_fupan()
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

void fupan()//复盘
{
	FILE* fp;
	fp = fopen("duiju.txt", "r");
	int a, b;
	while (!feof(fp))
	{
		fscanf(fp, "%d ", &a);
		fscanf(fp, "%d ", &b);
		fscanf(fp, "%d\n", &chessboard[a][b]);
		BeginBatchDraw();
		draw_fupan();
		EndBatchDraw();
		Sleep(100);
	}
	fclose(fp);
}