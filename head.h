#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define maxsize 100//栈长度

//数据类型转换及顺序表构建
typedef struct{
	int value[3][3];
	int index[3][3];
	int F;//估价函数f(x)的值
	int D;//d(x)为节点的深度
	int H;//h(x)为表示节点x的格局与目标节点格局不相同的个数
}datatype;

//顺序栈定义
typedef struct{ 
	datatype data[maxsize+1];//栈数组
	int top; 				 //栈顶指针
}Seqstack;

//全局变量
int depth=0;//记录搜索树的深度
datatype data_start;//初始状态节点
datatype data_end;//最终状态节点
datatype data;//临时数据存放器
datatype data_back[maxsize+1];//找到解后向上回溯至根节点
datatype data_temp[maxsize+1];//根据估价函数的值对扩展的节点进行排序，结果存放于此
int length;//data_temp的计数器
datatype reserve;//单个节点扩展后用于还原此前状态
int temp;//扩展阶段

Seqstack *Open_head;//open表
Seqstack *Closed_head;//closed表

/*********************函数声明*********************/
Seqstack *InitStack();//置空栈
void Stackempty(Seqstack *S);//判断栈是否为空
void Push(Seqstack *S,datatype x);//入栈
void Pop(Seqstack *S,datatype &x);//出栈
void Show(Seqstack *S);//输出栈内元素
/*********************函数声明*********************/
/***********************************************附属函数构建***********************************************/
//输出栈内元素
void Show_table(datatype value){
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			printf("%d ",value.value[j][i]);
		}
		printf("\n");
	}
	printf("\n\n");
}

//小菜单函数构建
bool select(){
	char select;
	char ch;//吸收干扰字符
	printf("Continue or not?(y:yes n:no),please intput your choice:\n");
	ch=getchar();
	scanf("%c",&select);
	if(select=='y'||select=='y'){
		return true;
	}
	else return false;
}
/***********************************************附属函数构建***********************************************/

/***********************************************基本函数构建***********************************************/
//置空栈
Seqstack *InitStack(){
	Seqstack *S;
    S=(Seqstack *)malloc(sizeof(Seqstack));
    S->top=0;
    return(S); 
}

//判断栈是否为空
void Stackempty(Seqstack *S){
    if(S->top==0){
		printf("该栈为空！\n");
	}
	else{
		printf("该栈非空！\n");
	}
}

//入栈
void Push(Seqstack *S,datatype x){ 
	int i,j,p;//循环变量
	//插入数据前判断Open表中是否已有相等元素
	for(j=1;j<=S->top;j++){
		for(i=0;i<3;i++){
			for(p=0;p<3;p++){
				if(S->data[j].value[i][p]!=x.value[i][p]){
					break;
				}
			}			
			if(p<3){
				break;
			}
		}
		if(i==3){//Open表中已有相等元素
			break;
		}
	}
	if(j==S->top+1){//当前Open表中无相等元素
		for(j=1;j<=Closed_head->top;j++){
			for(i=0;i<3;i++){
				for(p=0;p<3;p++){
					if(Closed_head->data[j].value[i][p]!=x.value[i][p]){
						break;
					}
				}				
				if(p<3){
					break;
				}
			}
			if(i==3){//之前Open表中已有相等元素
				break;
			}
		}
		if(j==Closed_head->top+1){//之前Open表中无相等元素
			if (S->top==maxsize){
				printf("对不起，Open表已满，新扩展的节点无法进表，该八数码问题的求解被迫终止！\n");
				exit(0);
			}
			S->top++; 		
			S->data[S->top]=x;
		}	
	}		
}

//出栈
void Pop(Seqstack *S,datatype &x){
	if(S->top==0){
		printf("不好意思，Open表已空，该八数码问题的局部优先搜索无解!\n");
		exit(0);
	}
	x=S->data[S->top];
	S->top--;
}

//检查输入是否正确
void Check_input(int value){
	if(value<1||value>3){
		printf("Warning:your input is wrong!(1 or 2 or 3)\n");
		exit(0);
	}
}
//冒泡排序
void MpSort(datatype array[],int N){  
	datatype p;
	for(int i=0;i<=N-1;i++)
	{
		for(int j=0;j<N-1;j++)
		{

			if(array[j].F>array[j+1].F)
			{
				p=array[j];
				array[j]=array[j+1];
				array[j+1]=p;
			}
		}
	}
}
//八数码问题的初值输入
void Input_Eightcodes(){
	int i,j;//循环变量
	printf("请输入您的八数码的初始状态(三维数组,用0代表空格):\n");
	printf("For example:\n");
	printf("2 8 3\n1 0 4\n7 6 5\n");
	printf("************************************************\nNow your inputs:\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			scanf("%d",&data_start.value[i][j]);
			data_start.index[i][j]=data_start.value[i][j];
		}
	}
}
/***********************************************基本函数构建***********************************************/

/***********************************************主要函数构建***********************************************/
//复制函数
void Copy(datatype &data1,datatype &data2){
	data1=data2;
}

//计算节点x的格局与目标节点格局不相同的个数
void Caculate_num_of_differences(datatype &data){
	int i,j;//循环变量
	data.H=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(data.value[i][j]!=data_end.value[i][j]){
				data.H++;
			}
		}
	}
}

//节点的扩展
void extend(int temp){
	for(int m=0;m<3;m++){
		for(int n=0;n<3;n++){
			data.index[m][n]=data.value[m][n];
		}
	}
	int h;//行号
	int h_n;//试探的行号
	int l;//列号
	int l_n;//试探的列号
	//定位
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(data.value[i][j]==temp){
				h=i;
				l=j;
			}
		}
	}
//检查能否移动
	//向下探
	h_n=h+1;
	if(h_n>=0&&h_n<=2){
		if(data.value[h_n][l]==0&&data.value[h][l]!=reserve.index[h_n][l]){
			data.value[h_n][l]=data.value[h][l];
			data.value[h][l]=0;
			Caculate_num_of_differences(data);
			data.D=depth;
			data.F=data.D+data.H;
			//push(Open_head,data);//新状态进入OPEN表
			length++;
			data_temp[length]=data;
			Copy(data,reserve);//状态还原为扩展前的状态
		}
	}
	//向上探
	h_n=h-1;
	if(h_n>=0&&h_n<=2){
		if(data.value[h_n][l]==0&&data.value[h][l]!=reserve.index[h_n][l]){
			data.value[h_n][l]=data.value[h][l];
			data.value[h][l]=0;
			Caculate_num_of_differences(data);
			data.D=depth;
			data.F=data.D+data.H;
			//push(Open_head,data);//新状态进入OPEN表
			length++;
			data_temp[length]=data;//找到解后向上回溯至根节点
			Copy(data,reserve);//状态还原为扩展前的状态
		}
	}
	//向右探
	l_n=l+1;
	if(l_n>=0&&l_n<=2){
		if(data.value[h][l_n]==0&&data.value[h][l]!=reserve.index[h][l_n]){
			data.value[h][l_n]=data.value[h][l];
			data.value[h][l]=0;
			Caculate_num_of_differences(data);
			data.D=depth;
			data.F=data.D+data.H;
			//push(Open_head,data);//新状态进入OPEN表
			length++;
			data_temp[length]=data;//找到解后向上回溯至根节点
			Copy(data,reserve);//状态还原为扩展前的状态
		}
	}
	//向左探
	l_n=l-1;
	if(l_n>=0&&l_n<=2){
		if(data.value[h][l_n]==0&&data.value[h][l]!=reserve.index[h][l_n]){
			data.value[h][l_n]=data.value[h][l];
			data.value[h][l]=0;
			Caculate_num_of_differences(data);
			data.D=depth;
			data.F=data.D+data.H;
			//push(Open_head,data);//新状态进入OPEN表
			length++;
			data_temp[length]=data;//找到解后向上回溯至根节点
			Copy(data,reserve);//状态还原为扩展前的状态
		}
	}
}

//找到结果后向上回溯至根节点
void Get_way(datatype data){
	int n=1;//循环变量
	data_back[1]=data;
	for(int i=1;i<=Closed_head->top;i++){
		for(int j=0;j<3;j++){
			for(int m=0;m<3;m++){
				if(data_back[n].index[j][m]!=Closed_head->data[i].value[j][m]){
					break;
				}	
			}			
			if(m<3){
				break;
			}
		}
		if(j==3){
			n++;
			data_back[n]=Closed_head->data[i];
			for(int p=0;p<3;p++){
				for(int q=0;q<3;q++){
					if(data_back[n].value[p][q]!=data_start.value[p][q]){
						break;
					}	
				}				
				if(q<3){
					break;
				}
			}
			if(p==3){
				break;
			}
			else{
				i=0;
			}
		}
	}
	for(int s=n;n>=1;n--){
		for(int l=0;l<3;l++){
			for(int z=0;z<3;z++){
				printf(" %d",data_back[n].value[l][z]);	
			}			
			printf("\n");
		}
		printf("\n\n");
	}
}

//检测搜索是否成功
bool Test(){
	Pop(Open_head,data);
	Push(Closed_head,data);
	int i,j;//循环变量	
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(data.value[i][j]!=data_end.value[i][j]){
				break;
			}
		}
		if(j<3){
			break;
		}
	}

	if(i<3){
		Show_table(data);
		return false;
	}
	else{
		Show_table(data);
		system("cls");		
		printf("解的路径如下:\n");
		Get_way(data);
		printf("您的汉诺塔问题已成功求解!\n");
		return true;
	}
}

//八数码问题的具体求解
void Caculate_Eightcodes(){
	int i,j;//循环变量
	//Open表和closed表的初始化
	Open_head=InitStack();
	Closed_head=InitStack();
	Push(Open_head,data_start);
	printf("求解中间过程如下:\n");
	//八数码问题的具体操作
	while(!Test()){
		reserve=data;//存储扩展前的当前状态
		//根据当前状态扩展新的节点
		depth++;
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				extend(data.value[i][j]);
			}
		}
		MpSort(data_temp,length);
		for(i=length;i>0;i--){
			Push(Open_head,data_temp[i]);
		}
		length=0;
	}
}
/***********************************************主要函数构建***********************************************/
