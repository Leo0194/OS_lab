#include <stdio.h>
#include <stdlib.h>
/*����ʱ��Ƭ��ת������CPU����*/
#include <stdio.h>
#include <conio.h>
#define N 5

using namespace std ;

/*���̿��ƿ�Ķ���*/
typedef struct pcb{
	char pname[N];   //������
	int runtime;	//����ʱ��
	int arrivetime;		//����ʱ��
	char state;			//����״̬
	struct pcb* next;	//��һ�����̵Ľ��̿��ƿ��ַ�����ӵ�ַ��
}PCB;
unsigned long current;
PCB head_input;
PCB head_run;
PCB* pcb_input;
FILE *f;
static char R='r',C='c';

//		��������
void intputprocess(){
	PCB *p1,*p2;
	int 	num;    //Ҫ�����Ľ�����
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
//   �����������к���


int readyprocess(){
    while (1){
        if(readydata()==0)
            return 1;
        else
            runprocess();

    }
}

//      �жϾ��������Ƿ��н��̺���
int readydata(){


    //�ж���û�н���
    if((head_input.next)==NULL){
        if(head_run.next==NULL){

            return 0;   //����������û�н���
        }
        else
            return 1;   //���������ﻹ�н���
    }
    PCB *p1,*p2,*p3;
    p1=head_run.next;
    p2=&head_run;

    while(p1!=NULL){
    	p2=p1;
    	p1=head_run.next;
	}   //�����п��������һ��   ѭ������ʱp1=NULL,p2ָ�����һ��
	p1=p2;  //����p1=null,��p2��ַ��ֵ��p1

	p3=head_input.next;
	p2=&head_input;    //����p2 ��p3��ʽѭ��

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

//       ���н��̺���
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
    int num;        //Ҫ�����Ľ�����
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
	f=fopen("result.txt","w");  //�Դ򿪷�ʽ����һ���ļ���w��ʾд�����  ����ֵΪ�ṹ��
	printf("\n Time1 =1000 time slice! \n");
	fprintf(f,"\n Time1 =1000 time slice! \n"); //�� Time1 =1000 time slice!д��f�ṹ����
	unsigned long current;
	current =0;
	intputprocess(); //�������̵ĺ���������������
	readyprocess();
	getch();
	fclose(f);

	return 0;
}




