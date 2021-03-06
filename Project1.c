#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <stdlib.h>
struct process{
	int priority;
	int burst_time;
	int pid;
	int waiting_time;
	int turnaround_time;
	int remaining_time;
	int arrival_time;
};
void getInput();
void calcWaitingTime(struct process *q,int);
void calcTurnAroundTime(struct process *q,int);
void printQueue(struct process *q,int size);
void RoundRobin1();
void RoundRobin2();
void PrioSorting();
void FCFS();
void printQueueI(struct process);
void printQueue(struct process *,int);
int q1_n=0,q2_n=0,q3_n=0,n=0;
struct process *q1,*q2,*q3;
int time_quantum1 = 8;
int time_quantum2 = 16;
void getInput(){
	printf("\n Total Number of Process:\t");
	scanf("%d",&n);
	//Allocatig Memory
	q1 = (struct process *)malloc(n*sizeof(struct process));
	q2 = (struct process *)malloc(n*sizeof(struct process));
	q3 = (struct process *)malloc(n*sizeof(struct process));
	for(int i=0;i<n;i++){
		struct process p;
		printf("\n\t\tProcess %d\n=============================================\n\n",i+1);
		p.arrival_time = (rand())%(n+1);				
		printf("PId:\t");
		scanf("%d",&p.pid);
		printf("Priority (1-9):\t");
		scanf("%d",&p.priority);
		printf("\nBurst Time: %d\t",p.burst_time);
		scanf("%d",&p.burst_time);
		p.remaining_time = p.burst_time;
		if(p.priority>0 && p.priority<=3){
			q1[q1_n++]  = p;
		}else if(p.priority>3 && p.priority<=6){
			q2[q2_n++] = p;
		}else{
			q3[q3_n++] = p;
		}		
	}
}
void printQueue(struct process *q,int size){	
	calcWaitingTime(q,size);
	calcTurnAroundTime(q,size);
	printf("\nPId\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time\t\tArrival");
	printf("\n========================================================================================================================================\n");
	for(int i=0;i<size;i++){
		printQueueI(q[i]);
	}
	printf("\n\n");
}
void printQueueI(struct process p){
	printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",p.pid,p.priority,p.burst_time,p.waiting_time,p.turnaround_time,p.arrival_time);
}
void calcWaitingTime(struct process *q,int size){
	q[0].waiting_time = 0;
	for(int i=1;i<size;i++){
		q[i].waiting_time = q[i-1].waiting_time + q[i-1].burst_time;
	}
}
void calcTurnAroundTime(struct process *q,int size){
	q[0].waiting_time = 0;
	for(int i=0;i<size;i++){
		q[i].turnaround_time = q[i].waiting_time + q[i].burst_time;
	}
}
void RoundRobinAlgo1(struct process *q,int size){
	int time=0,i=0,remain=size,flag=0,wait_time=0,tat_time=0,total_times=0;
	for(time=0,i=0;remain!=0;){
		struct process p = q[i];
		if(p.remaining_time<=time_quantum1 && p.remaining_time>0){
			time += p.remaining_time;
			p.remaining_time = 0;
			flag = 1;
		}else if(p.remaining_time>time_quantum1){
			p.remaining_time -= time_quantum1;
			time += time_quantum1;
		}
		if(p.remaining_time==0 && flag==1){
			remain--;
			printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",p.pid,p.priority,p.burst_time,p.waiting_time,p.turnaround_time);
			wait_time += time -p.arrival_time - p.burst_time;
			tat_time += time -p.arrival_time;
			flag = 0;
		}
		
		if(i==remain-1){
			i=0;
		}else if(q[i+1].arrival_time<time){
			i++;
		}else{
			i=0;
		}

		q[i] = p;
	}
	printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
	printf("Avg Turnaround Time = %f\n",tat_time*1.0/n); 	
}
void RoundRobin1(){
	printf("\n\n===========================================================================");
	printf("\n\t\tRound Robin with quantum 16\t");
	printf("\n===========================================================================\n\n");

	printf("\nPId\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time");
	printf("\n======================================================================================================\n");
	calcWaitingTime(q3,q3_n);
	calcTurnAroundTime(q3,q3_n);

	RoundRobinAlgo1(q3,q3_n);
}
void RoundRobinAlgo2(struct process *q,int size){
	int time=0,i=0,remain=size,flag=0,wait_time=0,tat_time=0,total_times=0;
	for(time=0,i=0;remain!=0;){
		struct process p = q[i];
		if(p.remaining_time<=time_quantum2 && p.remaining_time>0){
			time += p.remaining_time;
			p.remaining_time = 0;
			flag = 1;
		}else if(p.remaining_time>time_quantum2){
			p.remaining_time -= time_quantum2;
			time += time_quantum2;
		}
		if(p.remaining_time==0 && flag==1){
			remain--;
			printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",p.pid,p.priority,p.burst_time,p.waiting_time,p.turnaround_time);
			wait_time += time -p.arrival_time - p.burst_time;
			tat_time += time -p.arrival_time;
			flag = 0;
		}
		
		if(i==remain-1){
			i=0;
		}else if(q[i+1].arrival_time<time){
			i++;
		}else{
			i=0;
		}

		q[i] = p;
	}
	printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
	printf("Avg Turnaround Time = %f\n",tat_time*1.0/n); 	
}
void RoundRobin2(){
	printf("\n\n===========================================================================");
	printf("\n\t\tRound Robin with quantum 8\t");
	printf("\n===========================================================================\n\n");

	printf("\nPId\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time");
	printf("\n=========================================================================================================\n");
	calcWaitingTime(q2,q2_n);
	calcTurnAroundTime(q2,q2_n);

	RoundRobinAlgo2(q2,q2_n);
}
void FCFSAlgorithm(struct process *q,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(q[j].arrival_time>q[i].arrival_time){
				struct process t = q[i];
				q[i] = q[j];
				q[j] = t;
			}
		}
	}
}
void FCFS(){
	printf("\n\n===========================================================================");
	printf("\n\t\tFirst Come First Serve\t");
	printf("\n===========================================================================\n\n");
	FCFSAlgorithm(q1,q1_n);
	printQueue(q1,q1_n);
}
int main(){
	getInput();
	int i=1;
	while(n>0){
		switch(i){
                        case 1:
				FCFS();
			case 2:
				RoundRobin2();
                        
			case 3:
				RoundRobin1();
                                exit(1);
                                
		i++;
		sleep(3);
	}
	printf("\n\n");
}
}
