#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include"show.h"
#include"play.h"
#include"fupan.h"
#include"Mystruct.h"

void choose_level(ExMessage* msg2) //选择难度
{
	if (msg2->message == WM_MOUSEMOVE)
	{
		if (msg2->x >= 576 && msg2->x <= 744)
		{
			if (msg2->y >= 196 && msg2->y <= 295)
			{
				levels.level = easy;
				levels.ischoose = true;
			}
			else if (msg2->y >= 296 && msg2->y <= 395)
			{
				levels.level = medium;
				levels.ischoose = true;
			}
			else if (msg2->y >= 396 && msg2->y <= 495)
			{
				levels.level = hard;
				levels.ischoose = true;
			}
		}
	}
	if (msg2->message == WM_LBUTTONDOWN)//选择(已经选择了) 
	{
		panduan = 1;
		result = 0;
		levels.ischoose = false;
	}
}

void choose_order(ExMessage* msg2) //选择先后手
{
	if (msg2->message == WM_MOUSEMOVE)
	{
		if (msg2->x >= 576 && msg2->x <= 744)
		{
			if (msg2->y >= 196 && msg2->y <= 284)
			{
				orders.ischoose = true;
				orders.order = 1;
			}
		}
		if (msg2->x >= 576 && msg2->x <= 744)
		{
			if (msg2->y >= 296 && msg2->y <= 384)
			{
				orders.ischoose = true;
				orders.order = 2;
			}
		}
	}
	if (msg2->message == WM_LBUTTONDOWN)//选择 
	{
		if (orders.order == 1)
		{
			result = IDCANCEL;
			orders.ischoose = false;
		}
		if (orders.order == 2)
		{
			result = IDOK;
			orders.ischoose = false;
		}

	}
}

bool judge(int r, int c) //判断游戏是否结束
{
	int who = pos.player;//判断玩家是否获胜
	//横向判断
	for (int i = c - 4; i <= c; i++)//行号0-14
	{
		if (i >= 0 && i <= 10)
		{
			if (chessboard[r][i] == who && chessboard[r][i + 1] == who && chessboard[r][i + 2] == who && chessboard[r][i + 3] == who && chessboard[r][i + 4] == who)
			{
				return true;
			}
		}
	}
	//纵向判断
	for (int i = r - 4; i <= r; i++)//列号0-14
	{
		if (i >= 0 && i <= 10)
		{
			if (chessboard[i][c] == who && chessboard[i + 1][c] == who && chessboard[i + 2][c] == who && chessboard[i + 3][c] == who && chessboard[i + 4][c] == who)
			{
				return true;
			}
		}
	}
	//左下右上判断
	for (int i = r - 4, j = c + 4; i <= r; i++, j--)
	{
		if (i <= 10 && i >= 0 && j <= 14 && j >= 4)
		{
			if (chessboard[i][j] == who && chessboard[i + 1][j - 1] == who && chessboard[i + 2][j - 2] == who && chessboard[i + 3][j - 3] == who && chessboard[i + 4][j - 4] == who)
			{
				return true;
			}
		}
	}
	//左上右下判断
	for (int i = r - 4, j = c - 4; i <= r; i++, j++)
	{
		if (i <= 10 && i >= 0 && j <= 10 && j >= 0)
		{
			if (chessboard[i][j] == who && chessboard[i + 1][j + 1] == who && chessboard[i + 2][j + 2] == who && chessboard[i + 3][j + 3] == who && chessboard[i + 4][j + 4] == who)
			{
				return true;
			}
		}
	}
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (chessboard[i][j] == 0)
			{
				return false;
			}
			if (i == 14 && j == 14)
			{
				heqi = true;
				return true;
			}
		}
	}
	return false;
}

void pve_press(ExMessage* msg)    //PVE下棋
{
	if (pos.isshow == true)
	{
		if (msg->message == WM_LBUTTONDOWN)
		{
			pos.player = pve.player;
			if (chessboard[pos.row][pos.col] != 0)
			{
				MessageBox(GetHWnd(), "这里不能放棋子嗷！", "警告", MB_OKCANCEL);
				return;
			}
			FILE* fp;
			fp = fopen("duiju.txt", "a");
			fprintf(fp, "%d %d %d\n", pos.row, pos.col, pos.player);
			fclose(fp);
			chessboard[pos.row][pos.col] = pve.player;
			pve.turn = 0;
		}
	}
	if (judge(pos.row, pos.col) != false)
	{
		pos.isshow = false;
		draw_PVE();
		int d = MessageBox(GetHWnd(), "游戏结束", "你赢了，是否再来一把", MB_OKCANCEL);
		if (d == IDOK)
		{
			result = 0;
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					chessboard[i][j] = 0;//清空棋盘
				}
			}
			pve.turn = 3;
			panduan = 0;
			return;
		}
		if (d == IDCANCEL)
		{
			result = 0;
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					chessboard[i][j] = 0;
				}
			}
			mode = 0;
			panduan = 0;
		}
	}
}

void mouse_move(ExMessage* msg)    //鼠标移动显示棋子落点
{
	pos.isshow = false;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			int gridx = j * INTERVAL + 90;
			int gridy = i * INTERVAL + 90;
			if (abs(msg->x - gridx) <= 12 && abs(msg->y - gridy) <= 12)
			{
				pos.isshow = true;
				pos.row = i;
				pos.col = j;
			}
		}
	}
}

void mouse_press(ExMessage* msg)  //点击鼠标下棋
{
	if (pos.isshow == true)
	{
		if (msg->message == WM_LBUTTONDOWN)
		{
			if (chessboard[pos.row][pos.col] != 0)//点击的位置已有棋子
			{
				MessageBox(GetHWnd(), "这里不能放棋子嗷！", "警告", MB_OKCANCEL);
				return;
			}
			chessboard[pos.row][pos.col] = pos.player;
			FILE* fp; //记录对局信息
			fp = fopen("duiju.txt", "a");//打开或新建一个文本文件，可以读，但只允许在文件末尾追写
			fprintf(fp, "%d %d %d\n", pos.row, pos.col, pos.player);
			fclose(fp);
			if (judge(pos.row, pos.col))
			{
				pos.isshow = false;
				if (pos.player == black)
				{
					draw_PVP();
					int conti = MessageBox(GetHWnd(), "黑棋赢了,是否再来一局", "游戏结束", MB_OKCANCEL);
					if (conti == IDOK) //再来一局
					{
						fp = fopen("duiju.txt", "w");
						fclose(fp);
						for (int i = 0; i < 15; i++)
						{
							for (int j = 0; j < 15; j++)
							{
								chessboard[i][j] = 0;     //清空棋盘
							}
						}
						return;
					}
					if (conti == IDCANCEL)
					{
						for (int i = 0; i < 15; i++)
						{
							for (int j = 0; j < 15; j++)
							{
								chessboard[i][j] = 0;
							}
						}
						mode = 0;
						return;
					}
				}
				if (pos.player == white)
				{
					draw_PVP();
					int conti = MessageBox(GetHWnd(), "白棋赢了,是否再来一局", "游戏结束", MB_OKCANCEL);
					if (conti == IDOK) //再来一局
					{
						for (int i = 0; i < 15; i++)
						{
							for (int j = 0; j < 15; j++)
							{
								chessboard[i][j] = 0;
							}
						}
					}
					if (conti == IDCANCEL)
					{
						for (int i = 0; i < 15; i++)
						{
							for (int j = 0; j < 15; j++)
							{
								chessboard[i][j] = 0;
							}
						}
						mode = 0;
						return;
					}
				}
			}
			if (pos.player == black)
			{
				pos.player = white;
			}
			else
			{
				pos.player = black;
			}

		}
	}
}

void ai(int level1)//AI算法，计算对应权值并比较(越简单的模式，对于四子的权值越低，两子的权值越高)，电脑下在全场权值最高的地方
{
	pos.player = pve.AI;
	int weight[15][15] = { 0 };//权值
	for (int i = 0; i < 15; i++)//行
	{
		for (int j = 0; j < 15; j++)//列
		{
			if (chessboard[i][j] != 0)//有棋子的地方不用算了
			{
				continue;
			}
			for (int m = i - 4; m < i + 5; m++)
			{//行数-4：环境判断防止越界
				for (int n = j - 4; n < j + 5; n++)
				{
					if (m >= 0 && n >= 0 && m <= 14 && n <= 14)
					{
						if (chessboard[m][n] == 0)
						{
							weight[i][j] = weight[i][j] + 2;
						}
						else if (chessboard[m][n] == pve.AI)//此处是电脑的棋子
						{
							weight[i][j] = weight[i][j] + 1;
						}
						else if (chessboard[m][n] == pve.player)//此处是玩家的棋子
						{
							weight[i][j] = weight[i][j] - 1;
						}
					}
				}
			}//环境设置
//------------------------------------------------------------------------------------------------
			chessboard[i][j] = pve.AI;//判断AI
			for (int m = i - 4; m <= i; m++)
			{
				if (m <= 10 && m >= 0)
				{
					if (chessboard[m][j] != pve.player && chessboard[m + 1][j] != pve.player && chessboard[m + 2][j] != pve.player && chessboard[m + 3][j] != pve.player && chessboard[m + 4][j] != pve.player)
					{
						if (chessboard[m][j] + chessboard[m + 1][j] + chessboard[m + 2][j] + chessboard[m + 3][j] + chessboard[m + 4][j] == pve.AI * 5)
						{
							weight[i][j] = weight[i][j] + 10000000 / level1;
						}
					}//竖向获胜
					if (chessboard[m][j] != pve.player && chessboard[m + 1][j] != pve.player && chessboard[m + 2][j] != pve.player && chessboard[m + 3][j] != pve.player && chessboard[m + 4][j] != pve.player)
					{
						if (chessboard[m][j] + chessboard[m + 1][j] + chessboard[m + 2][j] + chessboard[m + 3][j] + chessboard[m + 4][j] == pve.AI * 4)
						{
							weight[i][j] = weight[i][j] + 100000 / level1;
						}
					}//竖向四子
					if (chessboard[m][j] != pve.player && chessboard[m + 1][j] != pve.player && chessboard[m + 2][j] != pve.player && chessboard[m + 3][j] != pve.player && chessboard[m + 4][j] != pve.player)
					{
						if (chessboard[m][j] + chessboard[m + 1][j] + chessboard[m + 2][j] + chessboard[m + 3][j] + chessboard[m + 4][j] == pve.AI * 3)
						{
							weight[i][j] = weight[i][j] + 3000 * level1;
						}
					}//竖向三子
					if (chessboard[m][j] != pve.player && chessboard[m + 1][j] != pve.player && chessboard[m + 2][j] != pve.player && chessboard[m + 3][j] != pve.player && chessboard[m + 4][j] != pve.player)
					{
						if (chessboard[m][j] + chessboard[m + 1][j] + chessboard[m + 2][j] + chessboard[m + 3][j] + chessboard[m + 4][j] == pve.AI * 2)
						{
							weight[i][j] = weight[i][j] + 600 * level1;
						}
					}//竖向两子
				}
			}
			for (int m = j - 4; m <= j; m++)
			{
				if (m <= 10 && m >= 0)
				{
					if (chessboard[i][m] != pve.player && chessboard[i][m + 1] != pve.player && chessboard[i][m + 2] != pve.player && chessboard[i][m + 3] != pve.player && chessboard[i][m + 4] != pve.player)
					{
						if (chessboard[i][m] + chessboard[i][m + 1] + chessboard[i][m + 2] + chessboard[i][m + 3] + chessboard[i][m + 4] == pve.AI * 5)
						{
							weight[i][j] = weight[i][j] + 10000000 / level1;
						}
					}//横向获胜
					if (chessboard[i][m] != pve.player && chessboard[i][m + 1] != pve.player && chessboard[i][m + 2] != pve.player && chessboard[i][m + 3] != pve.player && chessboard[i][m + 4] != pve.player)
					{
						if (chessboard[i][m] + chessboard[i][m + 1] + chessboard[i][m + 2] + chessboard[i][m + 3] + chessboard[i][m + 4] == pve.AI * 4)
						{
							weight[i][j] = weight[i][j] + 100000 / level1;
						}
					}//横向四子
					if (chessboard[i][m] != pve.player && chessboard[i][m + 1] != pve.player && chessboard[i][m + 2] != pve.player && chessboard[i][m + 3] != pve.player && chessboard[i][m + 4] != pve.player)
					{
						if (chessboard[i][m] + chessboard[i][m + 1] + chessboard[i][m + 2] + chessboard[i][m + 3] + chessboard[i][m + 4] == pve.AI * 3)
						{
							weight[i][j] = weight[i][j] + 3000 * level1;
						}
					}//横向三子
					if (chessboard[i][m] != pve.player && chessboard[i][m + 1] != pve.player && chessboard[i][m + 2] != pve.player && chessboard[i][m + 3] != pve.player && chessboard[i][m + 4] != pve.player)
					{
						if (chessboard[i][m] + chessboard[i][m + 1] + chessboard[i][m + 2] + chessboard[i][m + 3] + chessboard[i][m + 4] == pve.AI * 2)
						{
							weight[i][j] = weight[i][j] + 600 * level1;
						}
					}//横向两子
				}
			}
			for (int m = i - 4, n = j - 4; m <= i; m++, n++)
			{
				if (m <= 10 && m >= 0 && n <= 10 && n >= 0)
				{
					if (chessboard[m][n] != pve.player && chessboard[m + 1][n + 1] != pve.player && chessboard[m + 2][n + 2] != pve.player && chessboard[m + 3][n + 3] != pve.player && chessboard[m + 4][n + 4] != pve.player)
					{
						if (chessboard[m][n] + chessboard[m + 1][n + 1] + chessboard[m + 2][n + 2] + chessboard[m + 3][n + 3] + chessboard[m + 4][n + 4] == pve.AI * 5)
						{
							weight[i][j] = weight[i][j] + 10000000 / level1;
						}
					}//左上右下斜向获胜
					if (chessboard[m][n] != pve.player && chessboard[m + 1][n + 1] != pve.player && chessboard[m + 2][n + 2] != pve.player && chessboard[m + 3][n + 3] != pve.player && chessboard[m + 4][n + 4] != pve.player)
					{
						if (chessboard[m][n] + chessboard[m + 1][n + 1] + chessboard[m + 2][n + 2] + chessboard[m + 3][n + 3] + chessboard[m + 4][n + 4] == pve.AI * 4)
						{
							weight[i][j] = weight[i][j] + 100000 / level1;
						}
					}//左上右下斜向四子
					if (chessboard[m][n] != pve.player && chessboard[m + 1][n + 1] != pve.player && chessboard[m + 2][n + 2] != pve.player && chessboard[m + 3][n + 3] != pve.player && chessboard[m + 4][n + 4] != pve.player)
					{
						if (chessboard[m][n] + chessboard[m + 1][n + 1] + chessboard[m + 2][n + 2] + chessboard[m + 3][n + 3] + chessboard[m + 4][n + 4] == pve.AI * 3)
						{
							weight[i][j] = weight[i][j] + 3000 * level1;
						}
					}//左上右下斜向三子
					if (chessboard[m][n] != pve.player && chessboard[m + 1][n + 1] != pve.player && chessboard[m + 2][n + 2] != pve.player && chessboard[m + 3][n + 3] != pve.player && chessboard[m + 4][n + 4] != pve.player)
					{
						if (chessboard[m][n] + chessboard[m + 1][n + 1] + chessboard[m + 2][n + 2] + chessboard[m + 3][n + 3] + chessboard[m + 4][n + 4] == pve.AI * 2)
						{
							weight[i][j] = weight[i][j] + 600 * level1;
						}
					}//左上右下斜向两子
				}
			}
			for (int m = i + 4, n = j - 4; m >= i; m--, n++)
			{
				if (m <= 14 && m >= 4 && n <= 10 && n >= 0)
				{
					if (chessboard[m][n] != pve.player && chessboard[m - 1][n + 1] != pve.player && chessboard[m - 2][n + 2] != pve.player && chessboard[m - 3][n + 3] != pve.player && chessboard[m - 4][n + 4] != pve.player)
					{
						if (chessboard[m][n] + chessboard[m - 1][n + 1] + chessboard[m - 2][n + 2] + chessboard[m - 3][n + 3] + chessboard[m - 4][n + 4] == pve.AI * 5)
						{
							weight[i][j] = weight[i][j] + 10000000 / level1;
						}
					}//左下右上斜向获胜
					if (chessboard[m][n] != pve.player && chessboard[m - 1][n + 1] != pve.player && chessboard[m - 2][n + 2] != pve.player && chessboard[m - 3][n + 3] != pve.player && chessboard[m - 4][n + 4] != pve.player)
					{
						if (chessboard[m][n] + chessboard[m - 1][n + 1] + chessboard[m - 2][n + 2] + chessboard[m - 3][n + 3] + chessboard[m - 4][n + 4] == pve.AI * 4)
						{
							weight[i][j] = weight[i][j] + 100000 / level1;
						}
					}//左下右上斜向四子
					if (chessboard[m][n] != pve.player && chessboard[m - 1][n + 1] != pve.player && chessboard[m - 2][n + 2] != pve.player && chessboard[m - 3][n + 3] != pve.player && chessboard[m - 4][n + 4] != pve.player)
					{
						if (chessboard[m][n] + chessboard[m - 1][n + 1] + chessboard[m - 2][n + 2] + chessboard[m - 3][n + 3] + chessboard[m - 4][n + 4] == pve.AI * 3)
						{
							weight[i][j] = weight[i][j] + 3000 * level1;
						}
					}//左下右上斜向三子
					if (chessboard[m][n] != pve.player && chessboard[m - 1][n + 1] != pve.player && chessboard[m - 2][n + 2] != pve.player && chessboard[m - 3][n + 3] != pve.player && chessboard[m - 4][n + 4] != pve.player)
					{
						if (chessboard[m][n] + chessboard[m - 1][n + 1] + chessboard[m - 2][n + 2] + chessboard[m - 3][n + 3] + chessboard[m - 4][n + 4] == pve.AI * 2)
						{
							weight[i][j] = weight[i][j] + 600 * level1;
						}
					}//左下右上斜向两子

				}
			}
			//---------------------------------------------------------------------------------------------------------			
			chessboard[i][j] = pve.player;//判断player
			for (int m = i - 4; m <= i; m++)
			{
				if (m <= 10 && m >= 0)
				{
					if (chessboard[m][j] != pve.AI && chessboard[m + 1][j] != pve.AI && chessboard[m + 2][j] != pve.AI && chessboard[m + 3][j] != pve.AI && chessboard[m + 4][j] != pve.AI)
					{
						if (chessboard[m][j] + chessboard[m + 1][j] + chessboard[m + 2][j] + chessboard[m + 3][j] + chessboard[m + 4][j] == pve.player * 5)
						{
							weight[i][j] = weight[i][j] + 1000000 / level1;
						}
					}//竖向获胜
					if (chessboard[m][j] != pve.AI && chessboard[m + 1][j] != pve.AI && chessboard[m + 2][j] != pve.AI && chessboard[m + 3][j] != pve.AI && chessboard[m + 4][j] != pve.AI)
					{
						if (chessboard[m][j] + chessboard[m + 1][j] + chessboard[m + 2][j] + chessboard[m + 3][j] + chessboard[m + 4][j] == pve.player * 4)
						{
							weight[i][j] = weight[i][j] + 80000 / level1;
						}
					}//竖向四子
					if (chessboard[m][j] != pve.AI && chessboard[m + 1][j] != pve.AI && chessboard[m + 2][j] != pve.AI && chessboard[m + 3][j] != pve.AI && chessboard[m + 4][j] != pve.AI)
					{
						if (chessboard[m][j] + chessboard[m + 1][j] + chessboard[m + 2][j] + chessboard[m + 3][j] + chessboard[m + 4][j] == pve.player * 3)
						{
							weight[i][j] = weight[i][j] + 2000 * level1;
						}
					}//竖向三子
					if (chessboard[m][j] != pve.AI && chessboard[m + 1][j] != pve.AI && chessboard[m + 2][j] != pve.AI && chessboard[m + 3][j] != pve.AI && chessboard[m + 4][j] != pve.AI)
					{
						if (chessboard[m][j] + chessboard[m + 1][j] + chessboard[m + 2][j] + chessboard[m + 3][j] + chessboard[m + 4][j] == pve.player * 2)
						{
							weight[i][j] = weight[i][j] + 400 * level1;
						}
					}//竖向两子
				}
			}
			for (int m = j - 4; m <= j; m++)
			{
				if (m <= 10 && m >= 0)
				{
					if (chessboard[i][m] != pve.AI && chessboard[i][m + 1] != pve.AI && chessboard[i][m + 2] != pve.AI && chessboard[i][m + 3] != pve.AI && chessboard[i][m + 4] != pve.AI)
					{
						if (chessboard[i][m] + chessboard[i][m + 1] + chessboard[i][m + 2] + chessboard[i][m + 3] + chessboard[i][m + 4] == pve.player * 5)
						{
							weight[i][j] = weight[i][j] + 1000000 / level1;
						}
					}//横向获胜
					if (chessboard[i][m] != pve.AI && chessboard[i][m + 1] != pve.AI && chessboard[i][m + 2] != pve.AI && chessboard[i][m + 3] != pve.AI && chessboard[i][m + 4] != pve.AI)
					{
						if (chessboard[i][m] + chessboard[i][m + 1] + chessboard[i][m + 2] + chessboard[i][m + 3] + chessboard[i][m + 4] == pve.player * 4)
						{
							weight[i][j] = weight[i][j] + 80000 / level1;
						}
					}//横向四子
					if (chessboard[i][m] != pve.AI && chessboard[i][m + 1] != pve.AI && chessboard[i][m + 2] != pve.AI && chessboard[i][m + 3] != pve.AI && chessboard[i][m + 4] != pve.AI)
					{
						if (chessboard[i][m] + chessboard[i][m + 1] + chessboard[i][m + 2] + chessboard[i][m + 3] + chessboard[i][m + 4] == pve.player * 3)
						{
							weight[i][j] = weight[i][j] + 2000 * level1;
						}
					}//横向三子
					if (chessboard[i][m] != pve.AI && chessboard[i][m + 1] != pve.AI && chessboard[i][m + 2] != pve.AI && chessboard[i][m + 3] != pve.AI && chessboard[i][m + 4] != pve.AI)
					{
						if (chessboard[i][m] + chessboard[i][m + 1] + chessboard[i][m + 2] + chessboard[i][m + 3] + chessboard[i][m + 4] == pve.player * 2)
						{
							weight[i][j] = weight[i][j] + 400 * level1;
						}
					}//横向两子
				}
			}

			for (int m = i - 4, n = j - 4; m <= i; m++, n++)
			{
				if (m <= 10 && m >= 0 && n <= 10 && n >= 0)
				{
					if (chessboard[m][n] != pve.AI && chessboard[m + 1][n + 1] != pve.AI && chessboard[m + 2][n + 2] != pve.AI && chessboard[m + 3][n + 3] != pve.AI && chessboard[m + 4][n + 4] != pve.AI)
					{
						if (chessboard[m][n] + chessboard[m + 1][n + 1] + chessboard[m + 2][n + 2] + chessboard[m + 3][n + 3] + chessboard[m + 4][n + 4] == pve.player * 5)
						{
							weight[i][j] = weight[i][j] + 1000000 / level1;
						}
					}//左下右上斜向获胜
					if (chessboard[m][n] != pve.AI && chessboard[m + 1][n + 1] != pve.AI && chessboard[m + 2][n + 2] != pve.AI && chessboard[m + 3][n + 3] != pve.AI && chessboard[m + 4][n + 4] != pve.AI)
					{
						if (chessboard[m][n] + chessboard[m + 1][n + 1] + chessboard[m + 2][n + 2] + chessboard[m + 3][n + 3] + chessboard[m + 4][n + 4] == pve.player * 4)
						{
							weight[i][j] = weight[i][j] + 80000 / level1;
						}
					}//左下右上斜向四子
					if (chessboard[m][n] != pve.AI && chessboard[m + 1][n + 1] != pve.AI && chessboard[m + 2][n + 2] != pve.AI && chessboard[m + 3][n + 3] != pve.AI && chessboard[m + 4][n + 4] != pve.AI)
					{
						if (chessboard[m][n] + chessboard[m + 1][n + 1] + chessboard[m + 2][n + 2] + chessboard[m + 3][n + 3] + chessboard[m + 4][n + 4] == pve.player * 3)
						{
							weight[i][j] = weight[i][j] + 2000 * level1;
						}
					}//左下右上斜向三子
					if (chessboard[m][n] != pve.AI && chessboard[m + 1][n + 1] != pve.AI && chessboard[m + 2][n + 2] != pve.AI && chessboard[m + 3][n + 3] != pve.AI && chessboard[m + 4][n + 4] != pve.AI)
					{
						if (chessboard[m][n] + chessboard[m + 1][n + 1] + chessboard[m + 2][n + 2] + chessboard[m + 3][n + 3] + chessboard[m + 4][n + 4] == pve.player * 2)
						{
							weight[i][j] = weight[i][j] + 400 * level1;
						}
					}//左下右上斜向两子

				}
			}
			for (int m = i + 4, n = j - 4; m >= i; m--, n++)
			{
				if (m <= 14 && m >= 4 && n <= 10 && n >= 0)
				{
					if (chessboard[m][n] != pve.AI && chessboard[m - 1][n + 1] != pve.AI && chessboard[m - 2][n + 2] != pve.AI && chessboard[m - 3][n + 3] != pve.AI && chessboard[m - 4][n + 4] != pve.AI)
					{
						if (chessboard[m][n] + chessboard[m - 1][n + 1] + chessboard[m - 2][n + 2] + chessboard[m - 3][n + 3] + chessboard[m - 4][n + 4] == pve.player * 5)
						{
							weight[i][j] = weight[i][j] + 1000000 / level1;
						}
					}//左下右上斜向获胜
					if (chessboard[m][n] != pve.AI && chessboard[m - 1][n + 1] != pve.AI && chessboard[m - 2][n + 2] != pve.AI && chessboard[m - 3][n + 3] != pve.AI && chessboard[m - 4][n + 4] != pve.AI)
					{
						if (chessboard[m][n] + chessboard[m - 1][n + 1] + chessboard[m - 2][n + 2] + chessboard[m - 3][n + 3] + chessboard[m - 4][n + 4] == pve.player * 4)
						{
							weight[i][j] = weight[i][j] + 80000 / level1;
						}
					}//左下右上斜向四子
					if (chessboard[m][n] != pve.AI && chessboard[m - 1][n + 1] != pve.AI && chessboard[m - 2][n + 2] != pve.AI && chessboard[m - 3][n + 3] != pve.AI && chessboard[m - 4][n + 4] != pve.AI)
					{
						if (chessboard[m][n] + chessboard[m - 1][n + 1] + chessboard[m - 2][n + 2] + chessboard[m - 3][n + 3] + chessboard[m - 4][n + 4] == pve.player * 3)
						{
							weight[i][j] = weight[i][j] + 2000 * level1;
						}
					}//左下右上斜向三子
					if (chessboard[m][n] != pve.AI && chessboard[m - 1][n + 1] != pve.AI && chessboard[m - 2][n + 2] != pve.AI && chessboard[m - 3][n + 3] != pve.AI && chessboard[m - 4][n + 4] != pve.AI)
					{
						if (chessboard[m][n] + chessboard[m - 1][n + 1] + chessboard[m - 2][n + 2] + chessboard[m - 3][n + 3] + chessboard[m - 4][n + 4] == pve.player * 2)
						{
							weight[i][j] = weight[i][j] + 400 * level1;
						}
					}//左下右上斜向两子

				}
			}
			//------------------------------------------------------------------------------------------------
			chessboard[i][j] = 0;
		}
	}
	int a = 0, b = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (weight[i][j] > weight[a][b])
			{
				a = i, b = j;
			}
		}
	}
	//printf("%d ", weight[a][b]);
	//printf("%d\n", weight[a - 1][b + 2]);
	//AI计算----------------------------------------------------------------------------------------------
	if (mode != 3)
	{
		for (int m = 0; m < 15; m++)
		{
			for (int n = 0; n < 15; n++)
			{
				if (chessboard[m][n] != 0)
				{
					goto here;
				}
				if (m == 14 && n == 14)
				{
					a = 7, b = 7;
				}
			}
		}
	}
	srand(time(NULL));
	if (mode == 3)
	{
		for (int m = 0; m < 15; m++)
		{
			for (int n = 0; n < 15; n++)
			{
				if (chessboard[m][n] != 0)
				{
					goto here;
				}
				if (m == 14 && n == 14)//场上一个子也没有的时候随机先下一个
				{
					a = rand() % 14, b = rand() % 14;
				}
			}
		}
	}
here:;
	chessboard[a][b] = pve.AI;//ai落子
	FILE* fp;
	fp = fopen("duiju.txt", "a");
	fprintf(fp, "%d %d %d\n", a, b, pos.player);//行、列、行棋方
	fclose(fp);
	//以上为下棋操作
	if (judge(a, b))
	{
		pos.isshow = false;
		if (mode == 2)
		{
			draw_PVE();
		}
		else if (mode == 3)
		{
			draw_EVE();
		}
		int d = 0;
		if (mode == 2)
		{
			if (heqi)
			{
				d = MessageBox(GetHWnd(), "游戏结束", "和棋，是否再来一把", MB_OKCANCEL);
				heqi = false;
				panduan = 0;
			}
			else
			{
				d = MessageBox(GetHWnd(), "游戏结束", "你输了，是否再来一把", MB_OKCANCEL);
				panduan = 0;
			}//注：判断PVE获胜的部分在函数pve_press中
		}
		if (mode == 3)
		{
			if (heqi)
			{
				d = MessageBox(GetHWnd(), "游戏结束", "和棋，是否再来一把", MB_OKCANCEL);
				heqi = false;
			}
			else if (pos.player == black)
			{
				d = MessageBox(GetHWnd(), "游戏结束", "黑棋胜利，是否再来一把", MB_OKCANCEL);
				heqi = false;

			}
			else if (pos.player == white)
			{
				d = MessageBox(GetHWnd(), "游戏结束", "白棋胜利，是否再来一把", MB_OKCANCEL);
				heqi = false;
			}
		}
		if (d == IDOK)
		{
			FILE* fp;
			fp = fopen("duiju.txt", "w");
			fclose(fp);
			pos.isshow = false;
			result = 0;
			pve.turn = 3;
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					chessboard[i][j] = 0;
					dierbu = 2;
				}
			}
			return;
		}
		if (d == IDCANCEL)
		{
			result = 0;
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					chessboard[i][j] = 0;
					dierbu = 2;
				}
			}
			mode = 0;
		}
	}
	pve.turn = 1;
	Sleep(100);
}
