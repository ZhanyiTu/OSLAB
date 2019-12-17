#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
int id1;
int a = 0;
int sum = 0;
//void P(int semid, int index)//信号灯定义
//void V(int semid, int index)
//int semid; pthread_t p1. p2;//信号灯、线程句柄定义
//void *subp1(); void *subp2();//线程执行函数定义
/**
 * 主函数：main()
	{
	创建信号灯；
	信号灯赋初值；
	创建两个线程subp1、subp2;
	等待两个线程运行结束；
	删除信号灯；
	}
 void *subp1()
{
	for (......)  {
			P(…….);
			打印;
			V(…..);
	}
	return;
}
subp2负责计算，如何定义？
 *
 */
union semun{
    short val;
    struct semid_ds* buf;
    unsigned short* array;

}arg;
void P(int semid,int index)
{	   struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0; //操作标记：0或IPC_NOWAIT等
    semop(semid,&sem,1);	//1:表示执行命令的个数
}
void V(int semid,int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op =  1;
    sem.sem_flg = 0;
    semop(semid,&sem,1);
}
void* thread_fun1(){
    for(int i = 1; i <= 100; i++) {

        P(id1, 0);
        a++;
        V(id1, 1);
    }

}

void* thread_fun2(){
    for(int i = 1; i<= 100; i++){
        P(id1, 1);
        sum = sum + a;
        printf("%d\t", sum);
        V(id1, 0);
    }

}

int main() {
    id1 = semget(IPC_PRIVATE, 2, IPC_CREAT|0666 );//信号灯创建，3个参数 问题就出在这个参数上，参数写错了所以都错了
    arg.val = 1;
    semctl(id1, 0, SETVAL, arg);
    arg.val = 0;
    semctl(id1, 1, SETVAL, arg);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_fun1, NULL);
    pthread_create(&t2, NULL, thread_fun2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    semctl(id1, 0, IPC_RMID, 1);


    return 0;
}
