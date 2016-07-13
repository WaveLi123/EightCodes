/*===================================================
任务：利用局部择优搜索解决八数码问题
作者：李伟康_1240069_12级计算机二班
时间：2014年6月2日
版本：v1.0
===================================================*/
#include "head.h"
int main()
{
	//八数码问题的终态输入
	data_end.value[0][0]=1;data_end.value[0][1]=2;data_end.value[0][2]=3;
	data_end.value[1][0]=8;data_end.value[1][1]=0;data_end.value[1][2]=4;
	data_end.value[2][0]=7;data_end.value[2][1]=6;data_end.value[2][2]=5;
	//八数码问题的初值输入
	Input_Eightcodes();
	//八数码问题的具体求解
	Caculate_Eightcodes();
	if(select()){
		system("cls");	
		main();
	}
	else return 0;
	return 0;
}