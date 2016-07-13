#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define maxsize 100//ջ����

//��������ת����˳�����
typedef struct{
	int value[3][3];
	int index[3][3];
	int F;//���ۺ���f(x)��ֵ
	int D;//d(x)Ϊ�ڵ�����
	int H;//h(x)Ϊ��ʾ�ڵ�x�ĸ����Ŀ��ڵ��ֲ���ͬ�ĸ���
}datatype;

//˳��ջ����
typedef struct{ 
	datatype data[maxsize+1];//ջ����
	int top; 				 //ջ��ָ��
}Seqstack;

//ȫ�ֱ���
int depth=0;//��¼�����������
datatype data_start;//��ʼ״̬�ڵ�
datatype data_end;//����״̬�ڵ�
datatype data;//��ʱ���ݴ����
datatype data_back[maxsize+1];//�ҵ�������ϻ��������ڵ�
datatype data_temp[maxsize+1];//���ݹ��ۺ�����ֵ����չ�Ľڵ�������򣬽������ڴ�
int length;//data_temp�ļ�����
datatype reserve;//�����ڵ���չ�����ڻ�ԭ��ǰ״̬
int temp;//��չ�׶�

Seqstack *Open_head;//open��
Seqstack *Closed_head;//closed��

/*********************��������*********************/
Seqstack *InitStack();//�ÿ�ջ
void Stackempty(Seqstack *S);//�ж�ջ�Ƿ�Ϊ��
void Push(Seqstack *S,datatype x);//��ջ
void Pop(Seqstack *S,datatype &x);//��ջ
void Show(Seqstack *S);//���ջ��Ԫ��
/*********************��������*********************/
/***********************************************������������***********************************************/
//���ջ��Ԫ��
void Show_table(datatype value){
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			printf("%d ",value.value[j][i]);
		}
		printf("\n");
	}
	printf("\n\n");
}

//С�˵���������
bool select(){
	char select;
	char ch;//���ո����ַ�
	printf("Continue or not?(y:yes n:no),please intput your choice:\n");
	ch=getchar();
	scanf("%c",&select);
	if(select=='y'||select=='y'){
		return true;
	}
	else return false;
}
/***********************************************������������***********************************************/

/***********************************************������������***********************************************/
//�ÿ�ջ
Seqstack *InitStack(){
	Seqstack *S;
    S=(Seqstack *)malloc(sizeof(Seqstack));
    S->top=0;
    return(S); 
}

//�ж�ջ�Ƿ�Ϊ��
void Stackempty(Seqstack *S){
    if(S->top==0){
		printf("��ջΪ�գ�\n");
	}
	else{
		printf("��ջ�ǿգ�\n");
	}
}

//��ջ
void Push(Seqstack *S,datatype x){ 
	int i,j,p;//ѭ������
	//��������ǰ�ж�Open�����Ƿ��������Ԫ��
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
		if(i==3){//Open�����������Ԫ��
			break;
		}
	}
	if(j==S->top+1){//��ǰOpen���������Ԫ��
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
			if(i==3){//֮ǰOpen�����������Ԫ��
				break;
			}
		}
		if(j==Closed_head->top+1){//֮ǰOpen���������Ԫ��
			if (S->top==maxsize){
				printf("�Բ���Open������������չ�Ľڵ��޷������ð������������ⱻ����ֹ��\n");
				exit(0);
			}
			S->top++; 		
			S->data[S->top]=x;
		}	
	}		
}

//��ջ
void Pop(Seqstack *S,datatype &x){
	if(S->top==0){
		printf("������˼��Open���ѿգ��ð���������ľֲ����������޽�!\n");
		exit(0);
	}
	x=S->data[S->top];
	S->top--;
}

//��������Ƿ���ȷ
void Check_input(int value){
	if(value<1||value>3){
		printf("Warning:your input is wrong!(1 or 2 or 3)\n");
		exit(0);
	}
}
//ð������
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
//����������ĳ�ֵ����
void Input_Eightcodes(){
	int i,j;//ѭ������
	printf("���������İ�����ĳ�ʼ״̬(��ά����,��0����ո�):\n");
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
/***********************************************������������***********************************************/

/***********************************************��Ҫ��������***********************************************/
//���ƺ���
void Copy(datatype &data1,datatype &data2){
	data1=data2;
}

//����ڵ�x�ĸ����Ŀ��ڵ��ֲ���ͬ�ĸ���
void Caculate_num_of_differences(datatype &data){
	int i,j;//ѭ������
	data.H=0;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(data.value[i][j]!=data_end.value[i][j]){
				data.H++;
			}
		}
	}
}

//�ڵ����չ
void extend(int temp){
	for(int m=0;m<3;m++){
		for(int n=0;n<3;n++){
			data.index[m][n]=data.value[m][n];
		}
	}
	int h;//�к�
	int h_n;//��̽���к�
	int l;//�к�
	int l_n;//��̽���к�
	//��λ
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(data.value[i][j]==temp){
				h=i;
				l=j;
			}
		}
	}
//����ܷ��ƶ�
	//����̽
	h_n=h+1;
	if(h_n>=0&&h_n<=2){
		if(data.value[h_n][l]==0&&data.value[h][l]!=reserve.index[h_n][l]){
			data.value[h_n][l]=data.value[h][l];
			data.value[h][l]=0;
			Caculate_num_of_differences(data);
			data.D=depth;
			data.F=data.D+data.H;
			//push(Open_head,data);//��״̬����OPEN��
			length++;
			data_temp[length]=data;
			Copy(data,reserve);//״̬��ԭΪ��չǰ��״̬
		}
	}
	//����̽
	h_n=h-1;
	if(h_n>=0&&h_n<=2){
		if(data.value[h_n][l]==0&&data.value[h][l]!=reserve.index[h_n][l]){
			data.value[h_n][l]=data.value[h][l];
			data.value[h][l]=0;
			Caculate_num_of_differences(data);
			data.D=depth;
			data.F=data.D+data.H;
			//push(Open_head,data);//��״̬����OPEN��
			length++;
			data_temp[length]=data;//�ҵ�������ϻ��������ڵ�
			Copy(data,reserve);//״̬��ԭΪ��չǰ��״̬
		}
	}
	//����̽
	l_n=l+1;
	if(l_n>=0&&l_n<=2){
		if(data.value[h][l_n]==0&&data.value[h][l]!=reserve.index[h][l_n]){
			data.value[h][l_n]=data.value[h][l];
			data.value[h][l]=0;
			Caculate_num_of_differences(data);
			data.D=depth;
			data.F=data.D+data.H;
			//push(Open_head,data);//��״̬����OPEN��
			length++;
			data_temp[length]=data;//�ҵ�������ϻ��������ڵ�
			Copy(data,reserve);//״̬��ԭΪ��չǰ��״̬
		}
	}
	//����̽
	l_n=l-1;
	if(l_n>=0&&l_n<=2){
		if(data.value[h][l_n]==0&&data.value[h][l]!=reserve.index[h][l_n]){
			data.value[h][l_n]=data.value[h][l];
			data.value[h][l]=0;
			Caculate_num_of_differences(data);
			data.D=depth;
			data.F=data.D+data.H;
			//push(Open_head,data);//��״̬����OPEN��
			length++;
			data_temp[length]=data;//�ҵ�������ϻ��������ڵ�
			Copy(data,reserve);//״̬��ԭΪ��չǰ��״̬
		}
	}
}

//�ҵ���������ϻ��������ڵ�
void Get_way(datatype data){
	int n=1;//ѭ������
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

//��������Ƿ�ɹ�
bool Test(){
	Pop(Open_head,data);
	Push(Closed_head,data);
	int i,j;//ѭ������	
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
		printf("���·������:\n");
		Get_way(data);
		printf("���ĺ�ŵ�������ѳɹ����!\n");
		return true;
	}
}

//����������ľ������
void Caculate_Eightcodes(){
	int i,j;//ѭ������
	//Open���closed��ĳ�ʼ��
	Open_head=InitStack();
	Closed_head=InitStack();
	Push(Open_head,data_start);
	printf("����м��������:\n");
	//����������ľ������
	while(!Test()){
		reserve=data;//�洢��չǰ�ĵ�ǰ״̬
		//���ݵ�ǰ״̬��չ�µĽڵ�
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
/***********************************************��Ҫ��������***********************************************/
