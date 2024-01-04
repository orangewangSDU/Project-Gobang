#pragma once

extern struct Order
{
	bool ischoose;
	int order;    //先手为1（xian），后手为0（hou）
}orders;

extern struct Level
{
	bool ischoose;
	int level;   //easy简单，medium中等，hard困难
}levels;

extern struct Button
{
	int x;     //第几个按钮
	bool flag; //是否标红
}button;

extern struct play  //pve和eve复用一个结构体
{
	int AI;    //AI或ai1
	int player;//玩家或ai2
	int turn;  //1:到你了;0:不到你;3:结束（因为取消为2所以不能用2了）
}pve;

extern struct Pos
{
	int row;
	int col;
	bool isshow;//是否显示落子位置
	int player;
}pos ;//显示行列与判断