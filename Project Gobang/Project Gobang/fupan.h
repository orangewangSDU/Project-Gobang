#pragma once

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

extern IMAGE background;//����ͼƬ
extern int mode;//0�����ʼ��1��2��3��4Ϊ�ĸ�����
extern int chessboard[ROWS][COLUMNS];//��������
extern bool heqi;//�ж��Ƿ����
extern int result;//�жϵ����ȷ����ȡ��,0��δ����
extern int dierbu;//0������һ����2��IDCANCEL��ֹ
extern int level1;//�����Ѷȣ�easy�򵥣�medium�еȣ�hard����(�к궨��)
extern int panduan;//�ж��Ƿ��������Ѷ�


void draw_fupan();//��ʾ���̽���
void fupan();//���̲���