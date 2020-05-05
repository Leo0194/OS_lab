
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MaxNumber=100;

int PageOrder[MaxNumber];              //ҳ������
int PageNum,LackNum,MinBlockNum;        
int PageDisCount[MaxNumber];            //��ǰ�ڴ������һ�γ��ֵľ���
int LRUtime[MaxNumber];                 //���ʹ�����

double  LackPageRate;   
int LackPageNum;   
int VirtualQueue[MaxNumber];            //�������

void input();
void initial();
void FIFO();    
void LRU();    
void display();

void input()
{
	ifstream readData;
	readData.open("data.txt");
	readData>>MinBlockNum;
	readData>>PageNum;
	
	
	
	for (int i=0;i<PageNum;i++)
	{
		readData>>PageOrder[i];
	}

	cout<<"��ȡ���ݽ�����£�"<<endl;
	cout<<"��С������� = "<<MinBlockNum<<endl;
	cout<<"ҳ����� = "<<PageNum<<endl;
	cout<<"ҳ����������:"<<endl;
	for (int i = 0;i<PageNum;i++)
	{
		cout<<PageOrder[i]<<" ";
	}
	cout<<endl;
}

void initial()
{
	LackPageNum = MinBlockNum;
	LackPageRate = 0.0;

	for(int i = 0;i<PageNum;i++)
	{
		PageDisCount[i] = 0;            //��ʼ�����붼Ϊ0
		VirtualQueue[i] = -1;           //��ʼ�����е�ֵ��Ϊ����
	}

	for (int i = 0;i<MinBlockNum;i++)
	{
		bool isInQueue2 = false;
		int dis = 0;
		LRUtime[i] = 0;
		for (int j = 0;j<MinBlockNum;j++)
		{
			if (VirtualQueue[j] == PageOrder[i])
			{
				isInQueue2 = true;
			}
		}
		if (!isInQueue2)                 //�����µĽ��̽��뵽����ʱ����������Ӧ�ľ���
		{
			VirtualQueue[i] = PageOrder[i];
			for (int k = 0;k<i;k++)
			{ 
				LRUtime[k]++;             
			}
			display();
		}
		else
		{
			LRUtime[i] = 0;               //���¸���Ϊ0����ʾ����ո�ʹ��
		}
		
	}
}




void FIFO()
{
	cout<<"********* ��ѡ����FIFO�㷨��********* "<<endl;
	cout<<"ҳ���û��������:"<<endl;
	initial();
	bool isInQueue;
	int point = 0;            //ָ�����ϵ�ҳ��
	for (int i = MinBlockNum;i<PageNum;i++)
	{
		isInQueue = false;
		for (int k = 0;k<MinBlockNum;k++)
		{
			if (VirtualQueue[k] == PageOrder[i])   
			{
				isInQueue = true;
			}
		}

		if (!isInQueue)         
		
		
		
		//�����ǰҳ�治�ڶ����У��������Ӧ�Ĵ���
		{
			LackPageNum++;  //ȱҳ����1

			VirtualQueue[point] = PageOrder[i];
			display();
			point++;
			if (point == MinBlockNum) 
			{
				point = 0;  //��pointָ���β��һλ��ʱ�򣬽�point����ָ�����
			}
		}
	}

	LackPageRate = (LackPageNum * 1.0)/PageNum;
	cout<<"ȱҳ��LackPageNum = "<<LackPageNum<<endl;
	cout<<"ȱҳ��LackPageRate = "<<LackPageRate<<endl;
	
}



void LRU()
{
	cout<<"********* ��ѡ����LRU�㷨��********* "<<endl;
	cout<<"ҳ���û��������:"<<endl;

	initial();
	bool isInQueue;
	int point,k;  //ָ���ʱ��δ�����ʵ��±�
	
	for(int i = MinBlockNum;i<PageNum;i++)
	{
		isInQueue = false;	
		for (k = 0;k<MinBlockNum;k++)
		{
			if (VirtualQueue[k] == PageOrder[i])   //�����ǰҳ���ڶ�����
			{
				isInQueue = true;
			}
		}

		if (!isInQueue)
		{
			LackPageNum++;
			point = 0;
			for (int j = 1;j<MinBlockNum;j++)
			{
				if (LRUtime[point]<LRUtime[j])
				{
					point = j;
				}
			}

			for (int s = 0;s<MinBlockNum;s++)//����ҳ���Ӧ��ʱ��Ҫ+1
			{
				if (VirtualQueue[s] != VirtualQueue[point])
				{
					LRUtime[s]++;
				}
			}

			VirtualQueue[point] = PageOrder[i];
			LRUtime[point] = 0;

			display();
		}//if
		else   //������µ�ǰ��Ӧҳ���ʱ��
		{
			for (int s = 0;s<MinBlockNum;s++)//����ҳ���Ӧ��ʱ��Ҫ+1
			{
				if (VirtualQueue[s] != PageOrder[i])
				{
					LRUtime[s]++;
				}
				else
					LRUtime[s] = 0;
			}
		}
	}//for

	LackPageRate = (LackPageNum*1.0)/PageNum;
	cout<<"ȱҳ��LackPageNum = "<<LackPageNum<<endl;
	cout<<"ȱҳ��LackPageRate = "<<LackPageRate<<endl;
}

void display()
{
	for (int i = 0;i<MinBlockNum && VirtualQueue[i]>=0;i++)
	{
		cout<<VirtualQueue[i]<<" ";
	}
	cout<<endl;
}

int main()
{
	input();

	int isContinue = 1;
	int chooseAlgorithm;

	while(isContinue)
	{
		cout<<"------------------------------------------"<<endl;
		cout<<"------- ��ѡ���㷨    --------"<<endl;
		cout<<"------- 1����FIFO�㷨 --------"<<endl;
		cout<<"------- 2����LRU�㷨  --------"<<endl;
		cin>>chooseAlgorithm;
		switch(chooseAlgorithm)
		{
		case 1:
			FIFO();
			break;
		
		case 2:
			LRU();
			break;
		default:
			cout<<"��������ȷ����Ž���ѡ��"<<endl;break;
		}
		cout<<"********** �Ƿ����ѡ���㷨?              **********"<<endl;
		cout<<"********** ����1�������������0�����˳��� **********"<<endl;
		cin>>isContinue;
	}

	cout<<"***************************����***************************"<<endl;
	return 0;
}

