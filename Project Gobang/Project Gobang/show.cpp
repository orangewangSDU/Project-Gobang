#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<graphics.h>
#include"show.h"
#include"play.h"
#include"fupan.h"
#include"Mystruct.h"

void open_welcome_interface()    //������Ϸ����
{
	initgraph(800, 800);
	loadimage(&background, "background.jpg", 800, 800);
	putimage(0, 0, &background);
}

void init_chessboard()   //��ʼ������
{
	setbkcolor(YELLOW);//���ñ�����ɫΪ��ɫ
	cleardevice();
	for (int i = 0; i < 15; i++)
	{
		setlinestyle(PS_SOLID, 2);//����Ϊʵ�ߣ����Ϊ2
		setlinecolor(BLACK);//�ߵ���ɫ����Ϊ��ɫ
		line(90, 90 + i * INTERVAL, 90 + 14 * INTERVAL, 90 + i * INTERVAL);//����
		line(90 + i * INTERVAL, 90, 90 + i * INTERVAL, 90 + 14 * INTERVAL);//����
	}
	setlinestyle(PS_SOLID, 4);
	setlinecolor(BLACK);
	rectangle(90, 90, 90 + 14 * INTERVAL, 90 + 14 * INTERVAL);//�߿��ʵ��Ӵ�
	setfillcolor(BLACK);
	//���������������Ҫ�ص��ǣ�������������
	solidcircle(90 + 7 * INTERVAL, 90 + 7 * INTERVAL, 5);
	solidcircle(90 + 3 * INTERVAL, 90 + 3 * INTERVAL, 5);
	solidcircle(90 + 11 * INTERVAL, 90 + 11 * INTERVAL, 5);
	solidcircle(90 + 3 * INTERVAL, 90 + 11 * INTERVAL, 5);
	solidcircle(90 + 11 * INTERVAL, 90 + 3 * INTERVAL, 5);
}

void set_button_on_mode()//����ģʽѡ��ҳ���������Ӧ�İ�ť
{
	setbkmode(TRANSPARENT);
	settextstyle(70, 40, _T("����"));//�������ֵĸ߶ȣ���ȣ�����
	settextcolor(WHITE);
	outtextxy(155, 30, "������ Gobang");//��Ϸ˵��
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
	outtextxy(270, 362, "����");//disige
	settextstyle(30, 15, _T("Times New Roman"));
	settextcolor(WHITE);
	setlinecolor(WHITE);
	rectangle(450, 720, 780, 770);
	setfillcolor(BLACK);
	fillrectangle(450, 720, 790, 780);
	outtextxy(450, 720, "Made by Orange Wang");//��Ȩ����
	outtextxy(450, 750, "���ȳ� 202200460093");
}

void PVE_level_button()//����PVE��ѡ���Ѷȵİ�ť
{
	settextstyle(50, 20, 0);
	settextcolor(BLACK);
	outtextxy(520, 100, "��ѡ���Ѷȣ�");
	settextstyle(70, 30, 0);
	settextcolor(BLACK);
	outtextxy(570, 200, "��");
	outtextxy(570, 300, "�е�");
	outtextxy(570, 400, "����");
}

void draw0()   //���ƿ�ʼ����
{
	putimage(0, 0, &background);
	set_button_on_mode();
	if (button.flag) //�������ָ��ѡ��Ӻ��
	{
		setlinestyle(PS_SOLID, 4);
		setlinecolor(RED);
		rectangle(240, 120 + button.x * 80, 480, 200 + button.x * 80);
	}
}

void draw_PVP()         //����PVP����
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
			outtextxy(580, 250, "�ú�����");
		}
		if (pos.player == white)
		{
			settextstyle(40, 18, 0);
			settextcolor(BLACK);
			outtextxy(580, 250, "�ð�����");
		}
	}
	for (int i = 0; i < ROWS; i++) //�������ϻ�������
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
	if (pos.isshow) //����λ����ʾ
	{
		setlinestyle(PS_SOLID, 3);
		setlinecolor(BLUE);
		rectangle(pos.col * INTERVAL + 78, pos.row * INTERVAL + 78, pos.col * INTERVAL + 102, pos.row * INTERVAL + 102);
	}
}

void PVE_order_button()//����PVEѡ���Ⱥ��ֵİ�ť
{
	settextstyle(70, 30, 0);
	settextcolor(BLACK);
	outtextxy(550, 100, "��ѡ��");
	settextstyle(70, 30, 0);
	settextcolor(BLACK);
	outtextxy(570, 200, "����");
	outtextxy(570, 300, "����");
}

void draw_PVE()   //����PVE����
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
		if (pve.turn == 1 && pve.player == black) //��ʾ��
		{
			settextstyle(40, 18, 0);
			settextcolor(BLACK);
			outtextxy(580, 250, "�ú�����");
		}
		if (pve.turn == 1 && pve.player == white)
		{
			settextstyle(40, 18, 0);
			settextcolor(BLACK);
			outtextxy(580, 250, "�ð�����");
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

	for (int i = 0; i < ROWS; i++) //�������ϻ�������
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
	if (pos.isshow) //��������λ����ʾ
	{
		setlinestyle(PS_SOLID, 3);
		setlinecolor(BLUE);
		rectangle(pos.col * INTERVAL + 78, pos.row * INTERVAL + 78, pos.col * INTERVAL + 102, pos.row * INTERVAL + 102);
	}
}

void draw_EVE()    //����EVE����
{
	putimage(0, 0, &background);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);

	init_chessboard();
	for (int i = 0; i < ROWS; i++) //�������ϻ�������
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
	if (pos.isshow) //����λ����ʾ
	{
		setlinestyle(PS_SOLID, 3);
		setlinecolor(BLUE);
		rectangle(pos.col * INTERVAL + 78, pos.row * INTERVAL + 78, pos.col * INTERVAL + 102, pos.row * INTERVAL + 102);
	}
}

void button_move(ExMessage* msg)//��������ָλ�ô��İ�ť
{
	for (int i = 0; i < 4; i++) //һ���ĸ���ť
	{
		if (msg->x >= 239 && msg->x <= 481) //x����ķ�Χ
		{
			if (msg->y >= 119 + i * 80 && msg->y <= 201 + i * 80) //y����ķ�Χ
			{
				button.flag = true;
				button.x = i;
			}
		}
	}
}

void button_down(ExMessage* msg)//ѡ��ģʽ��������ť
{
	mode = button.x + 1;
	if (mode != 4)
	{
		FILE* fp;
		fp = fopen("duiju.txt", "r");
		if (fp == NULL)//r:�ļ�������ڣ�ֻ�����
		{
			int e = MessageBox(GetHWnd(), "�洢�Ծ���Ϣ���ļ������ڻ��ʧ�ܣ�����Ϊ��������", "����", MB_OK);
			fp = fopen("duiju.txt", "w");
			fclose(fp);
		}
		else
		{
			fp = fopen("duiju.txt", "w");//�ļ����ڵĻ��Ȱ�Ȩ�޸�Ϊw,��"w"�򿪵��ļ�ֻ������ļ�д�롣���򿪵��ļ������ڣ�����ָ�����ļ����������ļ������򿪵��ļ��Ѿ����ڣ��򽫸��ļ�ɾȥ���ؽ�һ�����ļ���
			fclose(fp);
		}
	}
}