/*===================================================
�������þֲ����������������������
���ߣ���ΰ��_1240069_12�����������
ʱ�䣺2014��6��2��
�汾��v1.0
===================================================*/
#include "head.h"
int main()
{
	//�������������̬����
	data_end.value[0][0]=1;data_end.value[0][1]=2;data_end.value[0][2]=3;
	data_end.value[1][0]=8;data_end.value[1][1]=0;data_end.value[1][2]=4;
	data_end.value[2][0]=7;data_end.value[2][1]=6;data_end.value[2][2]=5;
	//����������ĳ�ֵ����
	Input_Eightcodes();
	//����������ľ������
	Caculate_Eightcodes();
	if(select()){
		system("cls");	
		main();
	}
	else return 0;
	return 0;
}