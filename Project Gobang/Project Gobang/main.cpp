//***********************************
//*  ��Ŀ��Project Gobang
//*  ����main.cpp                                       *
//*  ���ܣ�ʵ�ּ򵥵�������С��Ϸ                         *
//*        �����򵥵�PVP��PVE��EVEģʽ�����ܹ����и���    *
//*  ���ߣ����ȳΣ�����޸�ʱ�䣺2023��12��13��           *  
//*  ѧ�ţ�202200460093
//************************************

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<graphics.h>
#include<time.h>
#include"show.h"
#include"play.h"
#include"fupan.h"

#define ROWS 15         //���������ʱ�׼����15x15
#define COLUMNS 15      //���������ʱ�׼����15x15
#define INTERVAL 30     //���̼��
#define black 1         //����
#define white 2         //����
#define xian 1          //����
#define hou 0           //����
#define easy 100        //��ģʽ
#define medium 10       //�е�ģʽ
#define hard 1          //����ģʽ

int chessboard[ROWS][COLUMNS];//��������
IMAGE background;//����ͼƬ
int mode = 0;//0�����ʼ��1��2��3��4Ϊ�ĸ�����
bool heqi = 0;//�ж��Ƿ����
int result = 0;//�жϵ����ȷ����ȡ��,0��δ����
int dierbu = 0;//0������һ����2��IDCANCEL��ֹ
int level1 = 0;//�����Ѷȣ�easy�򵥣�medium�еȣ�hard����(�к궨��)
int panduan = 0;//�ж��Ƿ��������Ѷ�

struct Order
{
	bool ischoose;
	int order;    //����Ϊ1��xian��������Ϊ0��hou��
}orders;

struct Level
{
	bool ischoose;
	int level;   //easy�򵥣�medium�еȣ�hard����
}levels;

struct Button
{
	int x;     //�ڼ�����ť
	bool flag; //�Ƿ���
}button = { -1,false };

struct play  //pve��eve����һ���ṹ��
{
	int AI;    //AI��ai1
	int player;//��һ�ai2
	int turn;  //1:������;0:������;3:��������Ϊȡ��Ϊ2���Բ�����2�ˣ�
}pve;

struct Pos
{
	int row;
	int col;
	bool isshow;//�Ƿ���ʾ����λ��
	int player;
}pos = { -1,-1,false,1 };//��ʾ�������ж�

int main()
{
	open_welcome_interface();
	set_button_on_mode();
	ExMessage msg;//�洢�����Ϣ�ı���
	while (true)
	{
		if (mode == 0)//������
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
		if (mode == 1)//PVP����
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
		if (mode == 2)//PVE����
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
			level1 = levels.level;//����ai�㷨�Ѷ�
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
				}//�������
				else if (pve.turn == 0) //��������
				{
					ai(level1);
				}
			}
		}
		if (mode == 3)//EVE����
		{
			dierbu = 0;
			BeginBatchDraw();
			draw_EVE();
			EndBatchDraw();
			pve.AI = black;
			pve.player = white;
			ai(hard);//ֱ��������ģʽ
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
		if (mode == 4)//����
		{
			fupan();
			int qu = MessageBox(GetHWnd(), "�Ƿ��ٴθ���", "���̽���", MB_OKCANCEL);
			if (qu == IDCANCEL) 
			{
				for (int i = 0; i < 15; i++) 
				{
					for (int j = 0; j < 15; j++) 
					{
						chessboard[i][j] = 0;
					}
				}//ɨ�ɾ�����
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
				}//ɨ�ɾ�����
				mode = 4;
			}
		}		
	}
	getchar();//�ӳ��˳����ڵ���
	return 0;
}