#pragma once

extern struct Order
{
	bool ischoose;
	int order;    //����Ϊ1��xian��������Ϊ0��hou��
}orders;

extern struct Level
{
	bool ischoose;
	int level;   //easy�򵥣�medium�еȣ�hard����
}levels;

extern struct Button
{
	int x;     //�ڼ�����ť
	bool flag; //�Ƿ���
}button;

extern struct play  //pve��eve����һ���ṹ��
{
	int AI;    //AI��ai1
	int player;//��һ�ai2
	int turn;  //1:������;0:������;3:��������Ϊȡ��Ϊ2���Բ�����2�ˣ�
}pve;

extern struct Pos
{
	int row;
	int col;
	bool isshow;//�Ƿ���ʾ����λ��
	int player;
}pos ;//��ʾ�������ж�