#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sched.h>
#include <semaphore.h>

int lock_1=0;
int lock_2=0;
int lock_3=0;
int lock_4=0;
int lock_5=0;

int b1=0;
int b2=0;

int thrA=0;
int thrB=0;
int thrC=0;
int thrD=0;
int thrE=0;

sem_t mutex;
sem_t bowl1;
sem_t bowl2;
sem_t locks[5];

void launchThreads_1();
void* Thr_A_1(void* in);
void* Thr_B_1(void* in);
void* Thr_C_1(void* in);
void* Thr_D_1(void* in);
void* Thr_E_1(void* in);

void launchThreads_2();
void* Thr_A_2(void* in);
void* Thr_B_2(void* in);
void* Thr_C_2(void* in);
void* Thr_D_2(void* in);
void* Thr_E_2(void* in);

void launchThreads_3();
void* Thr_A_3(void* in);
void* Thr_B_3(void* in);
void* Thr_C_3(void* in);
void* Thr_D_3(void* in);
void* Thr_E_3(void* in);

void launchThreads_4();
void* Thr_A_4(void* in);
void* Thr_B_4(void* in);
void* Thr_C_4(void* in);
void* Thr_D_4(void* in);
void* Thr_E_4(void* in);


int main(int argc, char const *argv[])
{
	// launchThreads_1();
	printf("Enter Option:\n");
	printf("1. launchThreads_1(Simulate the Problem)\n");
	printf("2. launchThreads_2(Avoid deadlock using Serialization)\n");
	printf("3. launchThreads_3(Avoid deadlock using Semaphores)\n");
	printf("4. launchThreads_4(Two sauce Bowls.. Avoid deadlock using Semaphores)\n");
	int op;
	scanf("%d",&op);
	switch(op){
	case 1:
		launchThreads_1();
		break;
	case 2:
		launchThreads_2();
		break;	
	case 3:
		launchThreads_3();
		break;
	case 4:
		launchThreads_4();	
		break;
	}
	return 0;
}


//1
void launchThreads_1(){
	pthread_t tid_a,tid_b,tid_c,tid_d,tid_e;
	int a = pthread_create(&tid_a,NULL,&Thr_A_1,NULL);
	int b = pthread_create(&tid_b,NULL,&Thr_B_1,NULL);
	int c = pthread_create(&tid_c,NULL,&Thr_C_1,NULL);
	int d = pthread_create(&tid_d,NULL,&Thr_D_1,NULL);
	int e = pthread_create(&tid_e,NULL,&Thr_E_1,NULL);

	pthread_join(tid_a,NULL);
	pthread_join(tid_b,NULL);
	pthread_join(tid_c,NULL);
	pthread_join(tid_d,NULL);
	pthread_join(tid_e,NULL);
}
void* Thr_A_1(void* in){
	thrA=1;
	printf("Syncing A\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}


	printf("Started Thread A\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=1;
			printf("Acquired Lock 1 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else if(lock_2==0){
			lock_2=1;
			printf("Acquired Lock 2 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else if(lock_5==0){
			lock_5=1;
			printf("Acquired Lock 5 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			// break;
		}
	}
	if(flag==1){
		printf("A could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("A has eaten.. Releasing locks\n");
		if(lock_1==1)lock_1=0;
		if(lock_2==1)lock_2=0;
		if(lock_3==1)lock_3=0;
		if(lock_4==1)lock_4=0;
		if(lock_5==1)lock_5=0;
		printf("Released Locks of A\n");
	}
 
}
void* Thr_B_1(void* in){
	thrB=1;
	printf("Syncing B\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}

	printf("Started Thread B\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=2;
			printf("Acquired Lock 1 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else if(lock_2==0){
			lock_2=2;
			printf("Acquired Lock 2 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else if(lock_3==0){
			lock_3=2;
			printf("Acquired Lock 3 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			// break;
		}
	}
	if(flag==1){
		printf("B could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("B has eaten.. Releasing locks\n");
		if(lock_1==2)lock_1=0;
		if(lock_2==2)lock_2=0;
		if(lock_3==2)lock_3=0;
		if(lock_4==2)lock_4=0;
		if(lock_5==2)lock_5=0;
		printf("Released Locks of B\n");
	}

}
void* Thr_C_1(void* in){
	thrC=1;
	printf("Syncing C\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}

	printf("Started Thread C\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_2==0){
			lock_2=3;
			printf("Acquired Lock 2 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else if(lock_3==0){
			lock_3=3;
			printf("Acquired Lock 3 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else if(lock_4==0){
			lock_4=3;
			printf("Acquired Lock 4 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			// break;
		}
	}
	if(flag==1){
		printf("C could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("C has eaten.. Releasing locks\n");
		if(lock_1==3)lock_1=0;
		if(lock_2==3)lock_2=0;
		if(lock_3==3)lock_3=0;
		if(lock_4==3)lock_4=0;
		if(lock_5==3)lock_5=0;
		printf("Released Locks of C\n");
	}

}
void* Thr_D_1(void* in){
	thrD=1;
	printf("Syncing D\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	printf("Started Thread D\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_3==0){
			lock_3=4;
			printf("Acquired Lock 3 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else if(lock_4==0){
			lock_4=4;
			printf("Acquired Lock 4 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else if(lock_5==0){
			lock_5=4;
			printf("Acquired Lock 5 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			// break;
		}
	}
	if(flag==1){
		printf("D could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("D has eaten.. Releasing locks\n");
		if(lock_1==4)lock_1=0;
		if(lock_2==4)lock_2=0;
		if(lock_3==4)lock_3=0;
		if(lock_4==4)lock_4=0;
		if(lock_5==4)lock_5=0;
		printf("Released Locks of D\n");
	}

}
void* Thr_E_1(void* in){
	thrE=1;
	printf("Syncing E\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	printf("Started Thread E\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=5;
			printf("Acquired Lock 1 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else if(lock_4==0){
			lock_4=5;
			printf("Acquired Lock 4 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else if(lock_5==0){
			lock_5=5;
			printf("Acquired Lock 5 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			sleep(1);
			// break;
		}
	}
	if(flag==1){
		printf("E could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("E has eaten.. Releasing locks\n");
		if(lock_1==5)lock_1=0;
		if(lock_2==5)lock_2=0;
		if(lock_3==5)lock_3=0;
		if(lock_4==5)lock_4=0;
		if(lock_5==5)lock_5=0;
		printf("Released Locks of E\n");
	}

}

//2
void launchThreads_2(){
	pthread_t tid_a,tid_b,tid_c,tid_d,tid_e;
	int a = pthread_create(&tid_a,NULL,&Thr_A_2,NULL);
	int b = pthread_create(&tid_b,NULL,&Thr_B_2,NULL);
	int c = pthread_create(&tid_c,NULL,&Thr_C_2,NULL);
	int d = pthread_create(&tid_d,NULL,&Thr_D_2,NULL);
	int e = pthread_create(&tid_e,NULL,&Thr_E_2,NULL);

	pthread_join(tid_a,NULL);
	pthread_join(tid_b,NULL);
	pthread_join(tid_c,NULL);
	pthread_join(tid_d,NULL);
	pthread_join(tid_e,NULL);
}
void* Thr_A_2(void* in){
	thrA=1;
	printf("Syncing A\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}


	printf("Started Thread A\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=1;
			printf("Acquired Lock 1 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else if(lock_2==0){
			lock_2=1;
			printf("Acquired Lock 2 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else if(lock_5==0){
			lock_5=1;
			printf("Acquired Lock 5 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			// break;
		}
	}
	if(flag==1){
		printf("A could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("A has eaten.. Releasing locks\n");
		if(lock_1==1)lock_1=0;
		if(lock_2==1)lock_2=0;
		if(lock_3==1)lock_3=0;
		if(lock_4==1)lock_4=0;
		if(lock_5==1)lock_5=0;
		printf("Released Locks of A\n");
	}
 
}
void* Thr_B_2(void* in){
	thrB=1;
	printf("Syncing B\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}

	printf("Started Thread B\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=2;
			printf("Acquired Lock 1 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else if(lock_2==0){
			lock_2=2;
			printf("Acquired Lock 2 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else if(lock_3==0){
			lock_3=2;
			printf("Acquired Lock 3 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			// break;
		}
	}
	if(flag==1){
		printf("B could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("B has eaten.. Releasing locks\n");
		if(lock_1==2)lock_1=0;
		if(lock_2==2)lock_2=0;
		if(lock_3==2)lock_3=0;
		if(lock_4==2)lock_4=0;
		if(lock_5==2)lock_5=0;
		printf("Released Locks of B\n");
	}

}
void* Thr_C_2(void* in){
	thrC=1;
	printf("Syncing C\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}

	printf("Started Thread C\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_2==0){
			lock_2=3;
			printf("Acquired Lock 2 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else if(lock_3==0){
			lock_3=3;
			printf("Acquired Lock 3 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else if(lock_4==0){
			lock_4=3;
			printf("Acquired Lock 4 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else{
			printf("C Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			// break;
		}
	}
	if(flag==1){
		printf("C could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("C has eaten.. Releasing locks\n");
		if(lock_1==3)lock_1=0;
		if(lock_2==3)lock_2=0;
		if(lock_3==3)lock_3=0;
		if(lock_4==3)lock_4=0;
		if(lock_5==3)lock_5=0;
		printf("Released Locks of C\n");
	}

}
void* Thr_D_2(void* in){
	thrD=1;
	printf("Syncing D\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	printf("Started Thread D\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_3==0){
			lock_3=4;
			printf("Acquired Lock 3 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else if(lock_4==0){
			lock_4=4;
			printf("Acquired Lock 4 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else if(lock_5==0){
			lock_5=4;
			printf("Acquired Lock 5 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			// break;
		}
	}
	if(flag==1){
		printf("D could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("D has eaten.. Releasing locks\n");
		if(lock_1==4)lock_1=0;
		if(lock_2==4)lock_2=0;
		if(lock_3==4)lock_3=0;
		if(lock_4==4)lock_4=0;
		if(lock_5==4)lock_5=0;
		printf("Released Locks of D\n");
	}

}
void* Thr_E_2(void* in){
	thrE=1;
	printf("Syncing E\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	printf("Started Thread E\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=5;
			printf("Acquired Lock 1 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else if(lock_4==0){
			lock_4=5;
			printf("Acquired Lock 4 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else if(lock_5==0){
			lock_5=5;
			printf("Acquired Lock 5 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			// break;
		}
	}
	if(flag==1){
		printf("E could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("E has eaten.. Releasing locks\n");
		if(lock_1==5)lock_1=0;
		if(lock_2==5)lock_2=0;
		if(lock_3==5)lock_3=0;
		if(lock_4==5)lock_4=0;
		if(lock_5==5)lock_5=0;
		printf("Released Locks of E\n");
	}

}

//3

void launchThreads_3(){
	sem_init(&mutex,0,1);
	for(int i=0;i<5;i++){
		sem_init(&locks[i],0,0);
	}

	pthread_t tid_a,tid_b,tid_c,tid_d,tid_e;
	int a = pthread_create(&tid_a,NULL,&Thr_A_3,NULL);
	int b = pthread_create(&tid_b,NULL,&Thr_B_3,NULL);
	int c = pthread_create(&tid_c,NULL,&Thr_C_3,NULL);
	int d = pthread_create(&tid_d,NULL,&Thr_D_3,NULL);
	int e = pthread_create(&tid_e,NULL,&Thr_E_3,NULL);

	pthread_join(tid_a,NULL);
	pthread_join(tid_b,NULL);
	pthread_join(tid_c,NULL);
	pthread_join(tid_d,NULL);
	pthread_join(tid_e,NULL);
}
void* Thr_A_3(void* in){
	thrA=1;
	printf("Syncing A\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}

	sem_wait(&mutex);
	printf("Started Thread A\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=1;
			// sem_wait(&locks[0]);
			printf("Acquired Lock 1 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[0]);
			cnt--;
		}else if(lock_2==0){
			lock_2=1;
			// sem_wait(&locks[1]);
			printf("Acquired Lock 2 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[1]);
			cnt--;
		}else if(lock_5==0){
			lock_5=1;
			// sem_wait(&locks[4]);
			printf("Acquired Lock 5 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[4]);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			flag=1;
			break;
		}
	}
	if(flag==1){
		printf("A could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("A has eaten.. Releasing locks\n");
		if(lock_1==1)lock_1=0;
		if(lock_2==1)lock_2=0;
		if(lock_3==1)lock_3=0;
		if(lock_4==1)lock_4=0;
		if(lock_5==1)lock_5=0;
		printf("Released Locks of A\n");
		// printf("%d %d %d %d %d \n",locks[0],locks[1],locks[2],locks[3],locks[4]);
	}
	sem_post(&mutex);
}
void* Thr_B_3(void* in){
	thrB=1;
	printf("Syncing B\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	sem_wait(&mutex);
	printf("Started Thread B\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=2;
			// sem_wait(&locks[0]);
			printf("Acquired Lock 1 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[0]);
			cnt--;
		}else if(lock_2==0){
			lock_2=2;
			// sem_wait(&locks[1]);
			printf("Acquired Lock 2 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[1]);
			cnt--;
		}else if(lock_3==0){
			lock_3=2;
			// sem_wait(&locks[2]);
			printf("Acquired Lock 3 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[2]);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			break;
		}
	}
	if(flag==1){
		printf("B could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("B has eaten.. Releasing locks\n");
		if(lock_1==2)lock_1=0;
		if(lock_2==2)lock_2=0;
		if(lock_3==2)lock_3=0;
		if(lock_4==2)lock_4=0;
		if(lock_5==2)lock_5=0;
		printf("Released Locks of B\n");
		// printf("%d %d %d %d %d \n",locks[0],locks[1],locks[2],locks[3],locks[4]);
	}
	sem_post(&mutex);

}
void* Thr_C_3(void* in){
	thrC=1;
	printf("Syncing C\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	sem_wait(&mutex);
	printf("Started Thread C\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_2==0){
			lock_2=3;
			// sem_wait(&locks[1]);
			printf("Acquired Lock 2 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[1]);
			cnt--;
		}else if(lock_3==0){
			lock_3=3;
			// sem_wait(&locks[2]);
			printf("Acquired Lock 3 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[2]);
			cnt--;
		}else if(lock_4==0){
			lock_4=3;
			// sem_wait(&locks[3]);
			printf("Acquired Lock 4 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[3]);
			cnt--;
		}else{
			printf("C Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			break;
		}
	}
	if(flag==1){
		printf("C could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("C has eaten.. Releasing locks\n");
		if(lock_1==3)lock_1=0;
		if(lock_2==3)lock_2=0;
		if(lock_3==3)lock_3=0;
		if(lock_4==3)lock_4=0;
		if(lock_5==3)lock_5=0;
		printf("Released Locks of C\n");
		// printf("%d %d %d %d %d \n",locks[0],locks[1],locks[2],locks[3],locks[4]);
	}
	sem_post(&mutex);

}
void* Thr_D_3(void* in){
	thrD=1;
	printf("Syncing D\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	sem_wait(&mutex);
	printf("Started Thread D\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_3==0){
			lock_3=4;
			// sem_wait(&locks[2]);
			printf("Acquired Lock 3 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[2]);
			cnt--;
		}else if(lock_4==0){
			lock_4=4;
			// sem_wait(&locks[3]);
			printf("Acquired Lock 4 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[3]);
			cnt--;
		}else if(lock_5==0){
			lock_5=4;
			// sem_wait(&locks[4]);
			printf("Acquired Lock 5 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[4]);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			break;
		}
	}
	if(flag==1){
		printf("D could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("D has eaten.. Releasing locks\n");
		if(lock_1==4)lock_1=0;
		if(lock_2==4)lock_2=0;
		if(lock_3==4)lock_3=0;
		if(lock_4==4)lock_4=0;
		if(lock_5==4)lock_5=0;
		printf("Released Locks of D\n");
		// printf("%d %d %d %d %d \n",locks[0],locks[1],locks[2],locks[3],locks[4]);
	}
	sem_post(&mutex);
}
void* Thr_E_3(void* in){
	thrE=1;
	printf("Syncing E\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	sem_wait(&mutex);
	printf("Started Thread E\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=5;
			// sem_wait(&locks[0]);
			printf("Acquired Lock 1 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[0]);
			cnt--;
		}else if(lock_4==0){
			lock_4=5;
			// sem_wait(&locks[3]);
			printf("Acquired Lock 4 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[3]);
			cnt--;
		}else if(lock_5==0){
			lock_5=5;
			// sem_wait(&locks[4]);
			printf("Acquired Lock 5 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[4]);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			break;
		}
	}
	if(flag==1){
		printf("E could not eat\n");
	}else if(flag==0 && cnt==0){
		printf("E has eaten.. Releasing locks\n");
		if(lock_1==5)lock_1=0;
		if(lock_2==5)lock_2=0;
		if(lock_3==5)lock_3=0;
		if(lock_4==5)lock_4=0;
		if(lock_5==5)lock_5=0;
		printf("Released Locks of E\n");
		// printf("%d %d %d %d %d \n",locks[0],locks[1],locks[2],locks[3],locks[4]);
	}
	sem_post(&mutex);

}

//ADD NOTE OF RACE condiiton in wrtiting to stdout in Ques 1

//4
void launchThreads_4(){
	sem_init(&mutex,0,1);
	for(int i=0;i<5;i++){
		sem_init(&locks[i],0,0);
	}
	sem_init(&bowl1,0,1);
	sem_init(&bowl2,0,1);
	pthread_t tid_a,tid_b,tid_c,tid_d,tid_e;
	int a = pthread_create(&tid_a,NULL,&Thr_A_4,NULL);
	int b = pthread_create(&tid_b,NULL,&Thr_B_4,NULL);
	int c = pthread_create(&tid_c,NULL,&Thr_C_4,NULL);
	int d = pthread_create(&tid_d,NULL,&Thr_D_4,NULL);
	int e = pthread_create(&tid_e,NULL,&Thr_E_4,NULL);

	pthread_join(tid_a,NULL);
	pthread_join(tid_b,NULL);
	pthread_join(tid_c,NULL);
	pthread_join(tid_d,NULL);
	pthread_join(tid_e,NULL);
}
void* Thr_A_4(void* in){
	thrA=1;
	printf("Syncing A\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}

	sem_wait(&mutex);
	printf("Started Thread A\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=1;
			// sem_wait(&locks[0]);
			printf("Acquired Lock 1 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[0]);
			cnt--;
		}else if(lock_2==0){
			lock_2=1;
			// sem_wait(&locks[1]);
			printf("Acquired Lock 2 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[1]);
			cnt--;
		}else if(lock_5==0){
			lock_5=1;
			// sem_wait(&locks[4]);
			printf("Acquired Lock 5 by A:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[4]);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			flag=1;
			break;
		}
	}
	if(flag==1){
		printf("A could not eat\n");
	}else if(flag==0 && cnt==0){
		if(b1==0){
			b1=1;
			sem_wait(&bowl1);
		}else if(b2==0){
			b2=1;
			sem_wait(&bowl2);
		}
		
		printf("A is eating from bowl\n");
		if(b1==1){
			sem_post(&bowl1);
			b1=0;
		}else if(b2==1){
			sem_post(&bowl2);
			b2=0;
		}
		printf("A has eaten.. Releasing locks\n");
		if(lock_1==1)lock_1=0;
		if(lock_2==1)lock_2=0;
		if(lock_3==1)lock_3=0;
		if(lock_4==1)lock_4=0;
		if(lock_5==1)lock_5=0;
		printf("Released Locks of A\n");
		// printf("%d %d %d %d %d \n",locks[0],locks[1],locks[2],locks[3],locks[4]);
	}
	sem_post(&mutex);
}
void* Thr_B_4(void* in){
	thrB=1;
	printf("Syncing B\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	sem_wait(&mutex);
	printf("Started Thread B\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=2;
			// sem_wait(&locks[0]);
			printf("Acquired Lock 1 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[0]);
			cnt--;
		}else if(lock_2==0){
			lock_2=2;
			// sem_wait(&locks[1]);
			printf("Acquired Lock 2 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[1]);
			cnt--;
		}else if(lock_3==0){
			lock_3=2;
			// sem_wait(&locks[2]);
			printf("Acquired Lock 3 by B:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[2]);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			break;
		}
	}
	if(flag==1){
		printf("B could not eat\n");
	}else if(flag==0 && cnt==0){
		if(b1==0){
			b1=1;
			sem_wait(&bowl1);
		}else if(b2==0){
			b2=1;
			sem_wait(&bowl2);
		}
		
		printf("B is eating from bowl\n");
		if(b1==1){
			sem_post(&bowl1);
			b1=0;
		}else if(b2==1){
			sem_post(&bowl2);
			b2=0;
		}
		printf("B has eaten.. Releasing locks\n");
		if(lock_1==2)lock_1=0;
		if(lock_2==2)lock_2=0;
		if(lock_3==2)lock_3=0;
		if(lock_4==2)lock_4=0;
		if(lock_5==2)lock_5=0;
		printf("Released Locks of B\n");
		// printf("%d %d %d %d %d \n",locks[0],locks[1],locks[2],locks[3],locks[4]);
	}
	sem_post(&mutex);

}
void* Thr_C_4(void* in){
	thrC=1;
	printf("Syncing C\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	sem_wait(&mutex);
	printf("Started Thread C\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_2==0){
			lock_2=3;
			// sem_wait(&locks[1]);
			printf("Acquired Lock 2 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[1]);
			cnt--;
		}else if(lock_3==0){
			lock_3=3;
			// sem_wait(&locks[2]);
			printf("Acquired Lock 3 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[2]);
			cnt--;
		}else if(lock_4==0){
			lock_4=3;
			// sem_wait(&locks[3]);
			printf("Acquired Lock 4 by C:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[3]);
			cnt--;
		}else{
			printf("C Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			break;
		}
	}
	if(flag==1){
		printf("C could not eat\n");
	}else if(flag==0 && cnt==0){
		if(b1==0){
			b1=1;
			sem_wait(&bowl1);
		}else if(b2==0){
			b2=1;
			sem_wait(&bowl2);
		}
		
		printf("C is eating from bowl\n");
		if(b1==1){
			sem_post(&bowl1);
			b1=0;
		}else if(b2==1){
			sem_post(&bowl2);
			b2=0;
		}
		printf("C has eaten.. Releasing locks\n");
		if(lock_1==3)lock_1=0;
		if(lock_2==3)lock_2=0;
		if(lock_3==3)lock_3=0;
		if(lock_4==3)lock_4=0;
		if(lock_5==3)lock_5=0;
		printf("Released Locks of C\n");
		// printf("%d %d %d %d %d \n",locks[0],locks[1],locks[2],locks[3],locks[4]);
	}
	sem_post(&mutex);

}
void* Thr_D_4(void* in){
	thrD=1;
	printf("Syncing D\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	sem_wait(&mutex);
	printf("Started Thread D\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_3==0){
			lock_3=4;
			// sem_wait(&locks[2]);
			printf("Acquired Lock 3 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[2]);
			cnt--;
		}else if(lock_4==0){
			lock_4=4;
			// sem_wait(&locks[3]);
			printf("Acquired Lock 4 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[3]);
			cnt--;
		}else if(lock_5==0){
			lock_5=4;
			// sem_wait(&locks[4]);
			printf("Acquired Lock 5 by D:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[4]);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			break;
		}
	}
	if(flag==1){
		printf("D could not eat\n");
	}else if(flag==0 && cnt==0){
		if(b1==0){
			b1=1;
			sem_wait(&bowl1);
		}else if(b2==0){
			b2=1;
			sem_wait(&bowl2);
		}
		
		printf("D is eating from bowl\n");
		if(b1==1){
			sem_post(&bowl1);
			b1=0;
		}else if(b2==1){
			sem_post(&bowl2);
			b2=0;
		}
		printf("D has eaten.. Releasing locks\n");
		if(lock_1==4)lock_1=0;
		if(lock_2==4)lock_2=0;
		if(lock_3==4)lock_3=0;
		if(lock_4==4)lock_4=0;
		if(lock_5==4)lock_5=0;
		printf("Released Locks of D\n");
		// printf("%d %d %d %d %d \n",locks[0],locks[1],locks[2],locks[3],locks[4]);
	}
	sem_post(&mutex);
}
void* Thr_E_4(void* in){
	thrE=1;
	printf("Syncing E\n");
	while(1){
		if(thrA!=0 && thrB!=0 && thrC!=0 && thrD!=0 && thrE!=0){
			printf("Synced\n");
			break;
		}
	}
	sem_wait(&mutex);
	printf("Started Thread E\n");
	int cnt=2;
	int flag=0;
	while(cnt>0){
		if(lock_1==0){
			lock_1=5;
			// sem_wait(&locks[0]);
			printf("Acquired Lock 1 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[0]);
			cnt--;
		}else if(lock_4==0){
			lock_4=5;
			// sem_wait(&locks[3]);
			printf("Acquired Lock 4 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[3]);
			cnt--;
		}else if(lock_5==0){
			lock_5=5;
			// sem_wait(&locks[4]);
			printf("Acquired Lock 5 by E:Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			// sem_post(&locks[4]);
			cnt--;
		}else{
			printf("Could not Acquire any lock.. Waiting :Status :%d %d %d %d %d\n",lock_1,lock_2,lock_3,lock_4,lock_5);
			
			break;
		}
	}
	if(flag==1){
		printf("E could not eat\n");
	}else if(flag==0 && cnt==0){
		if(b1==0){
			b1=1;
			sem_wait(&bowl1);
		}else if(b2==0){
			b2=1;
			sem_wait(&bowl2);
		}
		
		printf("E is eating from bowl\n");
		if(b1==1){
			sem_post(&bowl1);
			b1=0;
		}else if(b2==1){
			sem_post(&bowl2);
			b2=0;
		}
		printf("E has eaten.. Releasing locks\n");
		if(lock_1==5)lock_1=0;
		if(lock_2==5)lock_2=0;
		if(lock_3==5)lock_3=0;
		if(lock_4==5)lock_4=0;
		if(lock_5==5)lock_5=0;
		printf("Released Locks of E\n");
		// printf("%d %d %d %d %d \n",locks[0],locks[1],locks[2],locks[3],locks[4]);
	}
	sem_post(&mutex);

}