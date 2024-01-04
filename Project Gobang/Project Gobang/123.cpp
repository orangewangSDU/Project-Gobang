#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<easyx.h>
#include<stdlib.h>
#include<time.h>
#define JIANGE 30
#define HANG 15
#define LIE 15
IMAGE qipan;
int chuangkou = 1;
int panduan = 0;
int dierbu = 0;
bool heqi = false;
struct xianhou {
	bool choose;
	int shu;
}c = { false,-1 };//选择先后手
struct Pve
{
	int AI;
	int player;
	int turn;
}pve;//pve更换棋子
struct Pos {
	int row;
	int col;
	bool isshow;//shifouxianshi
	int player;
}pos = { -1,-1,false,1 };//显示行列与判断
struct button {
	int x;
	bool canshu;
}button123 = { -1,false };//选择模式
enum chess {
	none, black, white
};
int pan[HANG][LIE];
void twobutton() {
	settextstyle(80, 40, 0);
	settextcolor(WHITE);
	outtextxy(580, 300, "后手");
	outtextxy(580, 200, "先手");
}
bool judge(int r, int c) {
	//hengxiang
	int who = pos.player;
	for (int i = c - 4; i <= c; i++) {
		if (i <= 10 && i >= 0) {
			if (pan[r][i] == who && pan[r][i + 1] == who && pan[r][i + 2] == who
				&& pan[r][i + 3] == who && pan[r][i + 4] == who) {
				return true;
			}
		}
	}
	for (int i = r - 4; i <= r; i++) {
		if (i <= 10 && i >= 0) {
			if (pan[i][c] == who && pan[i + 1][c] == who && pan[i + 2][c] == who
				&& pan[i + 3][c] == who && pan[i + 4][c] == who) {
				return true;
			}
		}
	}
	for (int i = r - 4, j = c + 4; i <= r; i++, j--) {
		if (i <= 10 && i >= 0 && j <= 14 && j >= 4) {
			if (pan[i][j] == who && pan[i + 1][j - 1] == who && pan[i + 2][j - 2] == who
				&& pan[i + 3][j - 3] == who && pan[i + 4][j - 4] == who) {
				return true;
			}
		}
	}
	for (int i = r - 4, j = c - 4; i <= r; i++, j++) {
		if (i <= 10 && i >= 0 && j <= 10 && j >= 0) {
			if (pan[i][j] == who && pan[i + 1][j + 1] == who && pan[i + 2][j + 2] == who
				&& pan[i + 3][j + 3] == who && pan[i + 4][j + 4] == who) {
				return true;
			}
		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (pan[i][j] == 0)return false;
			if (i == 14 && j == 14) {
				heqi = true;
				return true;
			}
		}
	}
	return false;
}
void threebutton() {
	setlinestyle(PS_SOLID, 4);
	setlinecolor(WHITE);
	rectangle(220, 100, 580, 200);
	setfillcolor(BLACK);
	fillrectangle(220, 100, 580, 200);
	settextstyle(96, 90, _T("Consolas"));
	settextcolor(WHITE);
	outtextxy(265, 102, "PVP");//diyige
	setlinestyle(PS_SOLID, 4);
	setlinecolor(WHITE);
	rectangle(220, 200, 580, 300);
	setfillcolor(BLACK);
	fillrectangle(220, 200, 580, 300);
	settextstyle(96, 90, _T("Consolas"));
	settextcolor(WHITE);
	outtextxy(265, 202, "PVE");//dierge
	setlinestyle(PS_SOLID, 4);
	setlinecolor(WHITE);
	rectangle(220, 200, 580, 300);
	setfillcolor(BLACK);
	fillrectangle(220, 300, 580, 400);
	settextstyle(96, 90, _T("Consolas"));
	settextcolor(WHITE);
	outtextxy(265, 302, "EVE");//disange
	setlinestyle(PS_SOLID, 4);
	setlinecolor(WHITE);
	rectangle(220, 300, 580, 400);
	setfillcolor(BLACK);
	fillrectangle(220, 400, 580, 500);
	settextstyle(96, 60, _T("Consolas"));
	settextcolor(WHITE);
	outtextxy(280, 402, "复盘");//disige
}
void loadresource() {
	loadimage(&qipan, "qipan.jpg", 800, 600);
}
void draw1() {
	putimage(0, 0, &qipan);
	threebutton();
	if (button123.canshu) {
		setlinestyle(PS_SOLID, 4);
		setlinecolor(RED);
		rectangle(220, 100 + button123.x * 100, 580, 200 + button123.x * 100);
	}
}
void draw2() {
	putimage(0, 0, &qipan);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	//提示语
	if (chuangkou == 2) {
		if (pos.player == black) {
			settextstyle(40, 18, 0);
			settextcolor(WHITE);
			outtextxy(580, 250, "该黑棋了");
		}
		if (pos.player == white) {
			settextstyle(40, 18, 0);
			settextcolor(WHITE);
			outtextxy(580, 250, "该白棋了");
		}
	}
	if (chuangkou == 3) {
		if (pve.turn == 1 && pve.player == black) {
			settextstyle(40, 18, 0);
			settextcolor(WHITE);
			outtextxy(580, 250, "该你了(黑)");
		}
		if (pve.turn == 1 && pve.player == white) {
			settextstyle(40, 18, 0);
			settextcolor(WHITE);
			outtextxy(580, 250, "该你了(白)");
		}
	}
	//提示语
	if (panduan == 0) {
		if (chuangkou == 3) {
			twobutton();
			if (c.choose) {
				if (c.shu == 1) {
					setlinestyle(PS_SOLID, 3);
					setlinecolor(RED);
					rectangle(580, 200, 740, 280);
				}
				if (c.shu == 2) {
					setlinestyle(PS_SOLID, 3);
					setlinecolor(RED);
					rectangle(580, 300, 740, 380);
				}

			}
		}
	}
	for (int i = 0; i < 15; i++) {
		setlinestyle(PS_SOLID, 2);
		setlinecolor(BLACK);
		line(90, 90 + i * JIANGE, 90 + 14 * JIANGE, 90 + i * JIANGE);//横线
		line(90 + i * JIANGE, 90, 90 + i * JIANGE, 90 + 14 * JIANGE);//竖线
	}
	setlinestyle(PS_SOLID, 3);
	setlinecolor(BLACK);
	rectangle(90, 90, 90 + 14 * JIANGE, 90 + 14 * JIANGE);//jiacu边框
	setfillcolor(BLACK);
	solidcircle(90 + 7 * JIANGE, 90 + 7 * JIANGE, 5);
	solidcircle(90 + 3 * JIANGE, 90 + 3 * JIANGE, 5);
	solidcircle(90 + 11 * JIANGE, 90 + 11 * JIANGE, 5);
	solidcircle(90 + 3 * JIANGE, 90 + 11 * JIANGE, 5);
	solidcircle(90 + 11 * JIANGE, 90 + 3 * JIANGE, 5);
	//qizi
	for (int i = 0; i < HANG; i++) {
		for (int j = 0; j < LIE; j++) {
			if (pan[i][j] == black) {
				setfillcolor(BLACK);
				solidcircle(90 + j * JIANGE, 90 + i * JIANGE, 13);
			}
			else if (pan[i][j] == white) {
				setfillcolor(WHITE);
				solidcircle(90 + j * JIANGE, 90 + i * JIANGE, 13);
			}
		}
	}
	if (pos.isshow) {
		setlinestyle(PS_SOLID, 3);
		setlinecolor(BLUE);
		rectangle(pos.col * JIANGE + 78, pos.row * JIANGE + 78, pos.col * JIANGE + 102, pos.row * JIANGE + 102);
	}//落子位置显示

}
void buttonmove(ExMessage* msg1) {
	for (int i = 0; i < 4; i++) {
		if (msg1->x >= 202 && msg1->x <= 598) {
			if (msg1->y >= 102 + i * 100 && msg1->y <= 202 + i * 100) {
				button123.canshu = true;
				button123.x = i;
			}
		}
	}
}
void buttondown(ExMessage* msg1) {
	chuangkou = button123.x + 2;
	if (chuangkou != 5) 
	{
		FILE* fp;
		fp = fopen("duiju.txt", "w");
		fclose(fp);
	}
}
void mousemove(ExMessage* msg) {
	pos.isshow = false;
	for (int i = 0; i < HANG; i++) {
		for (int j = 0; j < LIE; j++) {
			int gridx = j * JIANGE + 90;
			int gridy = i * JIANGE + 90;
			if (abs(msg->x - gridx) <= 12 && abs(msg->y - gridy) <= 12) {
				pos.isshow = true;
				pos.row = i;
				pos.col = j;
			}
		}
	}
}
void mousepress(ExMessage* msg) {
	if (pos.isshow == true) {
		if (msg->message == WM_LBUTTONDOWN) {
			if (pan[pos.row][pos.col] != 0)return;
			pan[pos.row][pos.col] = pos.player;
			FILE* fp;
			fp = fopen("duiju.txt", "a");
			fprintf(fp, "%d\n%d\n%d\n", pos.row, pos.col, pos.player);
			fclose(fp);
			if (judge(pos.row, pos.col)) {
				pos.isshow = false;
				if (pos.player == black) {
					draw2();
					int conti = MessageBox(GetHWnd(), "黑棋赢了,是否继续玩耍", "游戏结束", MB_OKCANCEL);//
					if (conti == IDOK) {
						fp = fopen("duiju.txt", "w");
						fclose(fp);
						for (int i = 0; i < 15; i++) {
							for (int j = 0; j < 15; j++) {
								pan[i][j] = 0;
							}
						}
						goto here;
					}//zailaiyiba
					if (conti == IDCANCEL) {
						for (int i = 0; i < 15; i++) {
							for (int j = 0; j < 15; j++) {
								pan[i][j] = 0;
							}
						}
						chuangkou = 1;
						goto here;
					}
				}
				if (pos.player == white) {
					draw2();
					int conti = MessageBox(GetHWnd(), "白棋赢了,是否继续玩耍", "游戏结束", MB_OKCANCEL);
					if (conti == IDOK) {
						for (int i = 0; i < 15; i++) {
							for (int j = 0; j < 15; j++) {
								pan[i][j] = 0;
							}
						}
					}//zailaiyiba
					if (conti == IDCANCEL) {
						for (int i = 0; i < 15; i++) {
							for (int j = 0; j < 15; j++) {
								pan[i][j] = 0;
							}
						}
						chuangkou = 1;
					}
				}
			}
			if (pos.player == black)pos.player = white;
			else pos.player = black;
		here:;
		}
	}
}
void xianhou(ExMessage* msg2) {
	if (msg2->message == WM_MOUSEMOVE) {
		if (msg2->x >= 576 && msg2->x <= 744) {
			if (msg2->y >= 196 && msg2->y <= 284) {
				c.choose = true;
				c.shu = 1;
			}
		}
		if (msg2->x >= 576 && msg2->x <= 744) {
			if (msg2->y >= 296 && msg2->y <= 384) {
				c.choose = true;
				c.shu = 2;
			}
		}
	}
	if (msg2->message == WM_LBUTTONDOWN) {//xuanze
		if (c.shu == 1) {
			panduan = IDCANCEL;
			c.choose = false;
		}
		if (c.shu == 2) {
			panduan = IDOK;
			c.choose = false;
		}
	}
}
void pvepress(ExMessage* msg) {
	if (pos.isshow == true) {
		if (msg->message == WM_LBUTTONDOWN) {
			pos.player = pve.player;
			if (pan[pos.row][pos.col] != 0)return;
			FILE* fp;
			fp = fopen("duiju.txt", "a");
			fprintf(fp, "%d\n%d\n%d\n", pos.row, pos.col, pos.player);
			fclose(fp);
			pan[pos.row][pos.col] = pve.player;
			pve.turn = 0;
		}
	}
	if (judge(pos.row, pos.col)) {
		pos.isshow = false;
		draw2();
		int d = MessageBox(GetHWnd(), "游戏结束", "你赢了，是否再来一把", MB_OKCANCEL);
		if (d == IDOK) {
			panduan = 0;
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					pan[i][j] = 0;
				}
			}
			pve.turn = 3;
			return;
		}
		if (d == IDCANCEL) {
			panduan = 0;
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 15; j++) {
					pan[i][j] = 0;
				}
			}
			chuangkou = 1;
		}
	}
}
void ai() 
{
	pos.player = pve.AI;
	int quan[15][15] = { 0 };
	for (int i = 0; i < 15; i++) 
	{//hang
		for (int j = 0; j < 15; j++) 
		{//lie
			if (pan[i][j] != 0)continue;
			for (int m = i - 4; m < i + 5; m++) 
			{//hang-4 huanjingpanduan
				for (int n = j - 4; n < j + 5; n++) 
				{
					if (m >= 0 && n >= 0 && m <= 14 && n <= 14) 
					{
						if (pan[m][n] == 0)quan[i][j] = quan[i][j] + 2;
						else if (pan[m][n] == pve.AI)quan[i][j] = quan[i][j] + 1;
						else if (pan[m][n] == pve.player)quan[i][j] = quan[i][j] - 1;//huanjing
					}
				}

			}//huangjingshezhi
//------------------------------------------------------------------------------------------------
			pan[i][j] = pve.AI;//判断AI
			for (int m = i - 4; m <= i; m++) {
				if (m <= 10 && m >= 0) {
					if (pan[m][j] != pve.player && pan[m + 1][j] != pve.player && pan[m + 2][j] != pve.player
						&& pan[m + 3][j] != pve.player && pan[m + 4][j] != pve.player) {
						if (pan[m][j] + pan[m + 1][j] + pan[m + 2][j] + pan[m + 3][j] + pan[m + 4][j] == pve.AI * 5) {
							quan[i][j] = quan[i][j] + 10000000;
						}
					}//竖向获胜
					if (pan[m][j] != pve.player && pan[m + 1][j] != pve.player && pan[m + 2][j] != pve.player
						&& pan[m + 3][j] != pve.player && pan[m + 4][j] != pve.player) {
						if (pan[m][j] + pan[m + 1][j] + pan[m + 2][j] + pan[m + 3][j] + pan[m + 4][j] == pve.AI * 4) {
							quan[i][j] = quan[i][j] + 100000;
						}
					}//竖向四子
//--------------------------------------------------//
					if (pan[m][j] != pve.player && pan[m + 1][j] != pve.player && pan[m + 2][j] != pve.player
						&& pan[m + 3][j] != pve.player && pan[m + 4][j] != pve.player) {
						if (pan[m][j] + pan[m + 1][j] + pan[m + 2][j] + pan[m + 3][j] + pan[m + 4][j] == pve.AI * 3) {
							quan[i][j] = quan[i][j] + 3000;
						}
					}//竖向三子
					if (pan[m][j] != pve.player && pan[m + 1][j] != pve.player && pan[m + 2][j] != pve.player
						&& pan[m + 3][j] != pve.player && pan[m + 4][j] != pve.player) {
						if (pan[m][j] + pan[m + 1][j] + pan[m + 2][j] + pan[m + 3][j] + pan[m + 4][j] == pve.AI * 2) {
							quan[i][j] = quan[i][j] + 600;
						}
					}

				}
			}
			for (int m = j - 4; m <= j; m++) {
				if (m <= 10 && m >= 0) {
					if (pan[i][m] != pve.player && pan[i][m + 1] != pve.player && pan[i][m + 2] != pve.player
						&& pan[i][m + 3] != pve.player && pan[i][m + 4] != pve.player) {
						if (pan[i][m] + pan[i][m + 1] + pan[i][m + 2] + pan[i][m + 3] + pan[i][m + 4] == pve.AI * 5) {
							quan[i][j] = quan[i][j] + 10000000;
						}
					}//横向获胜
					if (pan[i][m] != pve.player && pan[i][m + 1] != pve.player && pan[i][m + 2] != pve.player
						&& pan[i][m + 3] != pve.player && pan[i][m + 4] != pve.player) {
						if (pan[i][m] + pan[i][m + 1] + pan[i][m + 2] + pan[i][m + 3] + pan[i][m + 4] == pve.AI * 4) {
							quan[i][j] = quan[i][j] + 100000;
						}
					}//zigezi
					if (pan[i][m] != pve.player && pan[i][m + 1] != pve.player && pan[i][m + 2] != pve.player
						&& pan[i][m + 3] != pve.player && pan[i][m + 4] != pve.player) {
						if (pan[i][m] + pan[i][m + 1] + pan[i][m + 2] + pan[i][m + 3] + pan[i][m + 4] == pve.AI * 3) {
							quan[i][j] = quan[i][j] + 3000;
						}
					}//sangezi
					if (pan[i][m] != pve.player && pan[i][m + 1] != pve.player && pan[i][m + 2] != pve.player
						&& pan[i][m + 3] != pve.player && pan[i][m + 4] != pve.player) {
						if (pan[i][m] + pan[i][m + 1] + pan[i][m + 2] + pan[i][m + 3] + pan[i][m + 4] == pve.AI * 2) {
							quan[i][j] = quan[i][j] + 600;
						}
					}//lianggezi
				}
			}
			for (int m = i - 4, n = j - 4; m <= i; m++, n++) {
				if (m <= 10 && m >= 0 && n <= 10 && n >= 0) {
					if (pan[m][n] != pve.player && pan[m + 1][n + 1] != pve.player && pan[m + 2][n + 2] != pve.player
						&& pan[m + 3][n + 3] != pve.player && pan[m + 4][n + 4] != pve.player) {
						if (pan[m][n] + pan[m + 1][n + 1] + pan[m + 2][n + 2] + pan[m + 3][n + 3] + pan[m + 4][n + 4] == pve.AI * 5) {
							quan[i][j] = quan[i][j] + 10000000;
						}
					}//左上方斜向
					if (pan[m][n] != pve.player && pan[m + 1][n + 1] != pve.player && pan[m + 2][n + 2] != pve.player
						&& pan[m + 3][n + 3] != pve.player && pan[m + 4][n + 4] != pve.player) {
						if (pan[m][n] + pan[m + 1][n + 1] + pan[m + 2][n + 2] + pan[m + 3][n + 3] + pan[m + 4][n + 4] == pve.AI * 4) {
							quan[i][j] = quan[i][j] + 100000;
						}
					}//左上方斜向4
					if (pan[m][n] != pve.player && pan[m + 1][n + 1] != pve.player && pan[m + 2][n + 2] != pve.player
						&& pan[m + 3][n + 3] != pve.player && pan[m + 4][n + 4] != pve.player) {
						if (pan[m][n] + pan[m + 1][n + 1] + pan[m + 2][n + 2] + pan[m + 3][n + 3] + pan[m + 4][n + 4] == pve.AI * 3) {
							quan[i][j] = quan[i][j] + 3000;
						}
					}//左上方斜向3
					if (pan[m][n] != pve.player && pan[m + 1][n + 1] != pve.player && pan[m + 2][n + 2] != pve.player
						&& pan[m + 3][n + 3] != pve.player && pan[m + 4][n + 4] != pve.player) {
						if (pan[m][n] + pan[m + 1][n + 1] + pan[m + 2][n + 2] + pan[m + 3][n + 3] + pan[m + 4][n + 4] == pve.AI * 2) {
							quan[i][j] = quan[i][j] + 600;
						}
					}//左上方斜向2



				}
			}
			for (int m = i + 4, n = j - 4; m >= i; m--, n++) {
				if (m <= 14 && m >= 4 && n <= 10 && n >= 0) {
					if (pan[m][n] != pve.player && pan[m - 1][n + 1] != pve.player && pan[m - 2][n + 2] != pve.player
						&& pan[m - 3][n + 3] != pve.player && pan[m - 4][n + 4] != pve.player) {
						if (pan[m][n] + pan[m - 1][n + 1] + pan[m - 2][n + 2] + pan[m - 3][n + 3] + pan[m - 4][n + 4] == pve.AI * 5) {
							quan[i][j] = quan[i][j] + 10000000;
						}
					}//左下方斜向
					if (pan[m][n] != pve.player && pan[m - 1][n + 1] != pve.player && pan[m - 2][n + 2] != pve.player
						&& pan[m - 3][n + 3] != pve.player && pan[m - 4][n + 4] != pve.player) {
						if (pan[m][n] + pan[m - 1][n + 1] + pan[m - 2][n + 2] + pan[m - 3][n + 3] + pan[m - 4][n + 4] == pve.AI * 4) {
							quan[i][j] = quan[i][j] + 100000;
						}
					}//左下方斜向4
					if (pan[m][n] != pve.player && pan[m - 1][n + 1] != pve.player && pan[m - 2][n + 2] != pve.player
						&& pan[m - 3][n + 3] != pve.player && pan[m - 4][n + 4] != pve.player) {
						if (pan[m][n] + pan[m - 1][n + 1] + pan[m - 2][n + 2] + pan[m - 3][n + 3] + pan[m - 4][n + 4] == pve.AI * 3) {
							quan[i][j] = quan[i][j] + 3000;
						}
					}//左下方斜向3
					if (pan[m][n] != pve.player && pan[m - 1][n + 1] != pve.player && pan[m - 2][n + 2] != pve.player
						&& pan[m - 3][n + 3] != pve.player && pan[m - 4][n + 4] != pve.player) {
						if (pan[m][n] + pan[m - 1][n + 1] + pan[m - 2][n + 2] + pan[m - 3][n + 3] + pan[m - 4][n + 4] == pve.AI * 2) {
							quan[i][j] = quan[i][j] + 600;
						}//左下方斜向2
					}

				}
			}
			//------------------------------------------------------------------------------------------------				
			pan[i][j] = pve.player;//判断player
			for (int m = i - 4; m <= i; m++) {
				if (m <= 10 && m >= 0) {
					if (pan[m][j] != pve.AI && pan[m + 1][j] != pve.AI && pan[m + 2][j] != pve.AI
						&& pan[m + 3][j] != pve.AI && pan[m + 4][j] != pve.AI) {
						if (pan[m][j] + pan[m + 1][j] + pan[m + 2][j] + pan[m + 3][j] + pan[m + 4][j] == pve.player * 5) {
							quan[i][j] = quan[i][j] + 1000000;
						}
					}//竖向获胜
					if (pan[m][j] != pve.AI && pan[m + 1][j] != pve.AI && pan[m + 2][j] != pve.AI
						&& pan[m + 3][j] != pve.AI && pan[m + 4][j] != pve.AI) {
						if (pan[m][j] + pan[m + 1][j] + pan[m + 2][j] + pan[m + 3][j] + pan[m + 4][j] == pve.player * 4) {
							quan[i][j] = quan[i][j] + 80000;
						}
					}//竖向4
					if (pan[m][j] != pve.AI && pan[m + 1][j] != pve.AI && pan[m + 2][j] != pve.AI
						&& pan[m + 3][j] != pve.AI && pan[m + 4][j] != pve.AI) {
						if (pan[m][j] + pan[m + 1][j] + pan[m + 2][j] + pan[m + 3][j] + pan[m + 4][j] == pve.player * 3) {
							quan[i][j] = quan[i][j] + 2000;
						}
					}//竖向3
					if (pan[m][j] != pve.AI && pan[m + 1][j] != pve.AI && pan[m + 2][j] != pve.AI
						&& pan[m + 3][j] != pve.AI && pan[m + 4][j] != pve.AI) {
						if (pan[m][j] + pan[m + 1][j] + pan[m + 2][j] + pan[m + 3][j] + pan[m + 4][j] == pve.player * 2) {
							quan[i][j] = quan[i][j] + 400;
						}
					}//竖向2


				}
			}
			for (int m = j - 4; m <= j; m++) {
				if (m <= 10 && m >= 0) {
					if (pan[i][m] != pve.AI && pan[i][m + 1] != pve.AI && pan[i][m + 2] != pve.AI
						&& pan[i][m + 3] != pve.AI && pan[i][m + 4] != pve.AI) {
						if (pan[i][m] + pan[i][m + 1] + pan[i][m + 2] + pan[i][m + 3] + pan[i][m + 4] == pve.player * 5) {
							quan[i][j] = quan[i][j] + 1000000;
						}
					}//横向获胜
					if (pan[i][m] != pve.AI && pan[i][m + 1] != pve.AI && pan[i][m + 2] != pve.AI
						&& pan[i][m + 3] != pve.AI && pan[i][m + 4] != pve.AI) {
						if (pan[i][m] + pan[i][m + 1] + pan[i][m + 2] + pan[i][m + 3] + pan[i][m + 4] == pve.player * 4) {
							quan[i][j] = quan[i][j] + 80000;
						}
					}//横向4
					if (pan[i][m] != pve.AI && pan[i][m + 1] != pve.AI && pan[i][m + 2] != pve.AI
						&& pan[i][m + 3] != pve.AI && pan[i][m + 4] != pve.AI) {
						if (pan[i][m] + pan[i][m + 1] + pan[i][m + 2] + pan[i][m + 3] + pan[i][m + 4] == pve.player * 3) {
							quan[i][j] = quan[i][j] + 2000;
						}
					}//横向3
					if (pan[i][m] != pve.AI && pan[i][m + 1] != pve.AI && pan[i][m + 2] != pve.AI
						&& pan[i][m + 3] != pve.AI && pan[i][m + 4] != pve.AI) {
						if (pan[i][m] + pan[i][m + 1] + pan[i][m + 2] + pan[i][m + 3] + pan[i][m + 4] == pve.player * 2) {
							quan[i][j] = quan[i][j] + 400;
						}
					}//横向2
				}
			}

			for (int m = i - 4, n = j - 4; m <= i; m++, n++) {
				if (m <= 10 && m >= 0 && n <= 10 && n >= 0) {
					if (pan[m][n] != pve.AI && pan[m + 1][n + 1] != pve.AI && pan[m + 2][n + 2] != pve.AI
						&& pan[m + 3][n + 3] != pve.AI && pan[m + 4][n + 4] != pve.AI) {
						if (pan[m][n] + pan[m + 1][n + 1] + pan[m + 2][n + 2] + pan[m + 3][n + 3] + pan[m + 4][n + 4] == pve.player * 5) {
							quan[i][j] = quan[i][j] + 1000000;
						}
					}//左上方斜向
					if (pan[m][n] != pve.AI && pan[m + 1][n + 1] != pve.AI && pan[m + 2][n + 2] != pve.AI
						&& pan[m + 3][n + 3] != pve.AI && pan[m + 4][n + 4] != pve.AI) {
						if (pan[m][n] + pan[m + 1][n + 1] + pan[m + 2][n + 2] + pan[m + 3][n + 3] + pan[m + 4][n + 4] == pve.player * 4) {
							quan[i][j] = quan[i][j] + 80000;
						}
					}//左上方4
					if (pan[m][n] != pve.AI && pan[m + 1][n + 1] != pve.AI && pan[m + 2][n + 2] != pve.AI
						&& pan[m + 3][n + 3] != pve.AI && pan[m + 4][n + 4] != pve.AI) {
						if (pan[m][n] + pan[m + 1][n + 1] + pan[m + 2][n + 2] + pan[m + 3][n + 3] + pan[m + 4][n + 4] == pve.player * 3) {
							quan[i][j] = quan[i][j] + 2000;
						}
					}//左上方3
					if (pan[m][n] != pve.AI && pan[m + 1][n + 1] != pve.AI && pan[m + 2][n + 2] != pve.AI
						&& pan[m + 3][n + 3] != pve.AI && pan[m + 4][n + 4] != pve.AI) {
						if (pan[m][n] + pan[m + 1][n + 1] + pan[m + 2][n + 2] + pan[m + 3][n + 3] + pan[m + 4][n + 4] == pve.player * 2) {
							quan[i][j] = quan[i][j] + 400;
						}
					}//左上方2

				}
			}
			for (int m = i + 4, n = j - 4; m >= i; m--, n++) {
				if (m <= 14 && m >= 4 && n <= 10 && n >= 0) {
					if (pan[m][n] != pve.AI && pan[m - 1][n + 1] != pve.AI && pan[m - 2][n + 2] != pve.AI
						&& pan[m - 3][n + 3] != pve.AI && pan[m - 4][n + 4] != pve.AI) {
						if (pan[m][n] + pan[m - 1][n + 1] + pan[m - 2][n + 2] + pan[m - 3][n + 3] + pan[m - 4][n + 4] == pve.player * 5) {
							quan[i][j] = quan[i][j] + 1000000;
						}
					}//左下方斜向
					if (pan[m][n] != pve.AI && pan[m - 1][n + 1] != pve.AI && pan[m - 2][n + 2] != pve.AI
						&& pan[m - 3][n + 3] != pve.AI && pan[m - 4][n + 4] != pve.AI) {
						if (pan[m][n] + pan[m - 1][n + 1] + pan[m - 2][n + 2] + pan[m - 3][n + 3] + pan[m - 4][n + 4] == pve.player * 4) {
							quan[i][j] = quan[i][j] + 80000;
						}
					}//左下方斜向
					if (pan[m][n] != pve.AI && pan[m - 1][n + 1] != pve.AI && pan[m - 2][n + 2] != pve.AI
						&& pan[m - 3][n + 3] != pve.AI && pan[m - 4][n + 4] != pve.AI) {
						if (pan[m][n] + pan[m - 1][n + 1] + pan[m - 2][n + 2] + pan[m - 3][n + 3] + pan[m - 4][n + 4] == pve.player * 3) {
							quan[i][j] = quan[i][j] + 2000;
						}
					}//左下方斜向
					if (pan[m][n] != pve.AI && pan[m - 1][n + 1] != pve.AI && pan[m - 2][n + 2] != pve.AI
						&& pan[m - 3][n + 3] != pve.AI && pan[m - 4][n + 4] != pve.AI) {
						if (pan[m][n] + pan[m - 1][n + 1] + pan[m - 2][n + 2] + pan[m - 3][n + 3] + pan[m - 4][n + 4] == pve.player * 2) {
							quan[i][j] = quan[i][j] + 400;
						}
					}//左下方斜向

				}
			}
			//------------------------------------------------------------------------------------------------
			pan[i][j] = 0;

		}


	}
	int a = 0, b = 0;
	for (int i = 0; i < 15; i++) 
	{
		for (int j = 0; j < 15; j++) 
		{
			if (quan[i][j] > quan[a][b]) 
			{
				a = i, b = j;
			}
		}
	}
	printf("%d\n", quan[a][b]);
	printf("%d\n", quan[a - 1][b + 2]);
	//AI计算----------------------------------------------------------------------------------------
	if (chuangkou != 4) 
	{
		for (int m = 0; m < 15; m++) 
		{
			for (int n = 0; n < 15; n++) 
			{
				if (pan[m][n] != 0)goto here;
				if (m == 14 && n == 14) 
				{
					a = 7, b = 7; 
				}
			}
		}
	}
	srand(time(NULL));
	if (chuangkou == 4) {
		for (int m = 0; m < 15; m++) {
			for (int n = 0; n < 15; n++) {
				if (pan[m][n] != 0)goto here;
				if (m == 14 && n == 14) { a = rand() % 14, b = rand() % 14; }
			}
		}
	}
here:;
	pan[a][b] = pve.AI;
	FILE* fp;
	fp = fopen("duiju.txt", "a");
	fprintf(fp, "%d\n%d\n%d\n", a, b, pos.player);
	fclose(fp);
	//XIAQI
	if (judge(a, b)) {
		pos.isshow = false;
		draw2();
		int d = 0;
		if (chuangkou == 3) 
		{
			if (heqi) 
			{
				d = MessageBox(GetHWnd(), "游戏结束", "和棋，是否再来一把", MB_OKCANCEL);
				heqi = false;
			}
			else 
			{ 
				d = MessageBox(GetHWnd(), "游戏结束", "你输了，是否再来一把", MB_OKCANCEL); 
			}
		}
		if (chuangkou == 4) 
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
			panduan = 0;
			pve.turn = 3;
			for (int i = 0; i < 15; i++) 
			{
				for (int j = 0; j < 15; j++) 
				{
					pan[i][j] = 0;
					dierbu = 2;
				}
			}
			return;
		}
		if (d == IDCANCEL) 
		{
			panduan = 0;
			for (int i = 0; i < 15; i++) 
			{
				for (int j = 0; j < 15; j++) 
				{
					pan[i][j] = 0;
					dierbu = 2;
				}
			}
			chuangkou = 1;
		}
	}
	pve.turn = 1;
	Sleep(100);
}
void fupan() 
{
	FILE* fp;
	fp = fopen("duiju.txt", "r");
	int a, b;
	while (!feof(fp)) 
	{
		fscanf(fp, "%d\n", &a);
		fscanf(fp, "%d\n", &b);
		fscanf(fp, "%d\n", &pan[a][b]);
		BeginBatchDraw();
		draw2();
		EndBatchDraw();
		Sleep(200);
	}
	fclose(fp);
}//复盘
int main() 
{
	initgraph(800, 600);
	loadresource();
	while (true) 
	{
		if (chuangkou == 1) 
		{
			BeginBatchDraw();
			draw1();
			EndBatchDraw();
			ExMessage msg1;
			if (peekmessage(&msg1, EX_MOUSE)) 
			{
				switch (msg1.message) 
				{
				case WM_MOUSEMOVE:
					buttonmove(&msg1);
					break;
				case WM_LBUTTONDOWN:
					buttondown(&msg1);
					break;
				default:
					break;
				}
			}
		}
		//主界面
		if (chuangkou == 2) 
		{
			BeginBatchDraw();
			draw2();
			EndBatchDraw();
			ExMessage msg;
			if (peekmessage(&msg, EX_MOUSE)) 
			{
				switch (msg.message) 
				{
				case WM_MOUSEMOVE:
					mousemove(&msg);
					break;
				case WM_LBUTTONDOWN:
					mousepress(&msg);
					break;
				default:
					break;
				}
			}
		}
		//pvp界面
		if (chuangkou == 3) 
		{
			BeginBatchDraw();
			draw2();
			EndBatchDraw();
			if (panduan == 0) 
			{
				pve.turn = 3;
				ExMessage msg2;
				if (peekmessage(&msg2, EX_MOUSE)) 
				{
					xianhou(&msg2);
				}
			}
			if (panduan != 0) 
			{
				if (panduan == IDOK) 
				{
					pve.AI = black;
					pve.player = white;
					pve.turn = 0;
					panduan = 3;
				}
				if (panduan == IDCANCEL)
				{
					pve.AI = white;
					pve.player = black;
					pve.turn = 1;
					panduan = 3;
				}
				if (pve.turn == 1) 
				{
					ExMessage msg;
					if (peekmessage(&msg, EX_MOUSE)) 
					{
						switch (msg.message) 
						{
						case WM_MOUSEMOVE:
							mousemove(&msg);
							break;
						case WM_LBUTTONDOWN:
							pvepress(&msg);
							break;
						default:
							break;
						}
					}
				}//renxiaqi
				else if (pve.turn == 0) 
				{
					ai();
				}
			}
		}
		//pve界面
		if (chuangkou == 4) 
		{
			dierbu = 0;
			BeginBatchDraw();
			draw2();
			EndBatchDraw();
			pve.AI = black;
			pve.player = white;
			ai();
			if (dierbu != 2) 
			{
				BeginBatchDraw();
				draw2();
				EndBatchDraw();
				pve.AI = white;
				pve.player = black;
				ai();
			}
		}
		//eve界面
		if (chuangkou == 5) 
		{
			fupan();
			int qu = MessageBox(GetHWnd(), "是否再次复盘", "复盘结束", MB_OKCANCEL);
			if (qu == IDCANCEL) 
			{
				for (int i = 0; i < 15; i++)
				{
					for (int j = 0; j < 15; j++)
					{
						pan[i][j] = 0;
					}
				}//扫干净棋盘
				chuangkou = 1;
			}
			if (qu == IDOK)
			{
				for (int i = 0; i < 15; i++) 
				{
					for (int j = 0; j < 15; j++)
					{
						pan[i][j] = 0;
					}
				}//扫干净棋盘
				chuangkou = 5;
			}
		}
		//复盘
		//四个窗口功能
	}
	getchar();
	return 0;
}