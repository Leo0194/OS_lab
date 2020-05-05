#include <stdio.h>
#include <stdlib.h>
/*采用时间片轮转法进行CPU调度*/
#include <stdio.h>
#include <conio.h>
#define N 5

using namespace std ;

/*进程控制块的定义*/
typedef struct pcb{
	char pname[N];   //进程名
	int runtime;	//运行时间
	int arrivetime;		//到达时间
	char state;			//进程状态
	struct pcb* next;	//下一个进程的进程控制块地址（链接地址）
}PCB;
unsigned long current;
PCB head_input;
PCB head_run;
PCB* pcb_input;
FILE *f;
static char R='r',C='c';

//		建立进程
void intputprocess(){
	PCB *p1,*p2;
	int 	num;    //要建立的进程数
	unsigned long max=0;
	printf(" How many process do you want to run: ");
	fprintf(f,"How many process do you want to run:");
	scanf("%d",&num);
	fprintf(f,"%d\n",&num);
	p1=&head_input;
	p2=p1;
	p1->next=new PCB;
	p1=p1->next;

	for(int i=0;i<num;i++){


        printf("No.  %3d process input pname: ",i+1);
        fprintf(f,"No.  %3d process input pname: ",i+1);
        scanf("%s",p1->pname);
        fprintf(f,"%s",p1->pname);
        printf("           runtime:");
        fprintf(f,"           runtime:");
        scanf("%d",&(p1->runtime));
        fprintf(f,"%d",p1->runtime);
        printf("           arrivetime");
        fprintf(f,"           arrivetime");
        scanf("%d",&(p1->arrivetime));
        fprintf(f,"%d",&(p1->arrivetime));

        p1->runtime=(p1->runtime)*1000;
        p1->arrivetime=(p1->arrivetime)*1000;
        p1->state=R;

        if((unsigned long)(p1->arrivetime)>max){
            max=p1->arrivetime;
        }

        p1->next=new PCB;
        p2=p1;
        p1=p1->next;

	}
	delete p1;
	p1=NULL;
	p2->next=NULL;

}
int readydata();
int runprocess();
//   建立就绪队列函数


int readyprocess(){
    while (1){
        if(readydata()==0)
            return 1;
        else
            runprocess();

    }
}

//      判断就绪队列是否有进程函数
int readydata(){


    //判断有没有进程
    if((head_input.next)==NULL){
        if(head_run.next==NULL){

            return 0;   //就绪队列里没有进程
        }
        else
            return 1;   //就绪队列里还有进程
    }
    PCB *p1,*p2,*p3;
    p1=head_run.next;
    p2=&head_run;

    while(p1!=NULL){
    	p2=p1;
    	p1=head_run.next;
	}   //队列中靠近处理机一端   循环结束时p1=NULL,p2指向最后一个
	p1=p2;  //避免p1=null,将p2地址赋值给p1

	p3=head_input.next;
	p2=&head_input;    //按先p2 后p3格式循环

	while(p3!=NULL){
		if((unsigned long)((p3->arrivetime)<=current)&&(p3->state==R)){
			printf("Time slice is %d(time %4d);Process %s start!\n",current,(current+500)/1000,p3->pname);
			fprintf(f,"Time slice is %d(time %4d);Process %s start!\n",current,(current+500)/1000,p3->pname);

			p2->next=p3->next;
			p3->next=p1->next;
			p1->next=p3;
			p3=p2;

		}
		p2=p3;
		p3=p3->next;
	}
	return 1;
}

//       运行进程函数
int runprocess(){
	PCB *p1,*p2;
	if(head_run.next==NULL){
		current++;
		return 1;
	}

	else{
		p1=head_run.next;
		p2=&head_run;
		while(p1!=NULL){
			p1->arrivetime--;
			current++;
			if(p1->runtime<=0){
				printf("Time slice is %8d time %4d;Process %s end.\n",current,(current+500)/1000,p1->pname);
				fprintf(f,"Time slice is %8d time %4d;Process %s end.\n",current,(current+500)/1000,p1->pname);
				p1->state=C;
				p2->next=p1->next;
				delete p1;
				p1=NULL;

			}else{
				p2=p1;
				p1=p2->next;
			}
			return 1;
		}
	}


}
/*void inputprocess(){
    PCB *p1,*p2;
    int num;        //要建立的进程数
    unsigned long max=0;
    printf("How many processes do you want to run?");
    fprintf(f,"How many processes do you want to run?");
    scanf("%d",&num);
    fprintf(f,"%d",&num);
    p1=&head_input;
    p2=p1;
    p1->next=new PCB;
    p1=p1->next;
    for(int i=0;i<num;i++){
            printf("No. %3d process input name",i+1);
                fprintf(f,"No. %3d process input name",i+1);
            scanf("%s",p1->pname);
                fprintf(f,"%s",p1->pname);
            printf("          runtime");
                fprintf(f,"         runtime");
            scanf("%d",&(p1->arrivetime));
                fprintf(f,"%d",&(p1->arrivetime));
            printf("           arrivement");
                fprintf(f,"           arrivement");
            scanf("%d",&(p1->runtime));
            fprintf(f,"%d",&(p1->runtime));

            p1->runtime=p1->runtime*1000;
            p1->arrivetime=p1->arrivetime*1000;
            p1->state=R;
            if((unsigned long)(p1->arrivetime)>max){
                max=p1->arrivetime;

            }
            p1->next=new PCB;
            p2=p1;
            p1=p1->next;
    }
    delete p1;
    p1=NULL;
    p2->next=NULL;

}*/




int main(){
	f=fopen("result.txt","w");  //以打开方式建立一个文件，w表示写入操作  返回值为结构体
	printf("\n Time1 =1000 time slice! \n");
	fprintf(f,"\n Time1 =1000 time slice! \n"); //将 Time1 =1000 time slice!写入f结构体中
	unsigned long current;
	current =0;
	intputprocess(); //建立进程的函数，来创建进程
	readyprocess();
	getch();
	fclose(f);

	return 0;
}




