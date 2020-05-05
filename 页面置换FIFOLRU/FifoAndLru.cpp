
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MaxNumber=100;

int PageOrder[MaxNumber];              //页面序列
int PageNum,LackNum,MinBlockNum;        
int PageDisCount[MaxNumber];            //当前内存距离下一次出现的距离
int LRUtime[MaxNumber];                 //最近使用情况

double  LackPageRate;   
int LackPageNum;   
int VirtualQueue[MaxNumber];            //虚拟队列

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

	cout<<"读取数据结果如下："<<endl;
	cout<<"最小物理块数 = "<<MinBlockNum<<endl;
	cout<<"页面个数 = "<<PageNum<<endl;
	cout<<"页面序列如下:"<<endl;
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
		PageDisCount[i] = 0;            //初始化距离都为0
		VirtualQueue[i] = -1;           //初始化队列的值都为负数
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
		if (!isInQueue2)                 //当有新的进程进入到队列时，便计算其对应的距离
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
			LRUtime[i] = 0;               //重新更新为0，表示最近刚刚使用
		}
		
	}
}




void FIFO()
{
	cout<<"********* 你选择了FIFO算法：********* "<<endl;
	cout<<"页面置换情况如下:"<<endl;
	initial();
	bool isInQueue;
	int point = 0;            //指向最老的页面
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
		
		
		
		//如果当前页面不在队列中，则进行相应的处理
		{
			LackPageNum++;  //缺页数加1

			VirtualQueue[point] = PageOrder[i];
			display();
			point++;
			if (point == MinBlockNum) 
			{
				point = 0;  //当point指向队尾后一位的时候，将point重新指向队首
			}
		}
	}

	LackPageRate = (LackPageNum * 1.0)/PageNum;
	cout<<"缺页数LackPageNum = "<<LackPageNum<<endl;
	cout<<"缺页率LackPageRate = "<<LackPageRate<<endl;
	
}



void LRU()
{
	cout<<"********* 你选择了LRU算法：********* "<<endl;
	cout<<"页面置换情况如下:"<<endl;

	initial();
	bool isInQueue;
	int point,k;  //指向最长时间未被访问的下标
	
	for(int i = MinBlockNum;i<PageNum;i++)
	{
		isInQueue = false;	
		for (k = 0;k<MinBlockNum;k++)
		{
			if (VirtualQueue[k] == PageOrder[i])   //如果当前页面在队列中
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

			for (int s = 0;s<MinBlockNum;s++)//其余页面对应的时间要+1
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
		else   //负责更新当前对应页面的时间
		{
			for (int s = 0;s<MinBlockNum;s++)//其余页面对应的时间要+1
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
	cout<<"缺页数LackPageNum = "<<LackPageNum<<endl;
	cout<<"缺页率LackPageRate = "<<LackPageRate<<endl;
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
		cout<<"------- 请选择算法    --------"<<endl;
		cout<<"------- 1代表FIFO算法 --------"<<endl;
		cout<<"------- 2代表LRU算法  --------"<<endl;
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
			cout<<"请输入正确的序号进行选择："<<endl;break;
		}
		cout<<"********** 是否继续选择算法?              **********"<<endl;
		cout<<"********** 输入1代表继续，输入0代表退出！ **********"<<endl;
		cin>>isContinue;
	}

	cout<<"***************************结束***************************"<<endl;
	return 0;
}

