#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <linux/sem.h>
#include <sys/sem.h>
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
int main() {
    int id1 = semget(IPC_PRIVATE, 1, IPC_CREAT|0666 );//信号灯创建，3个参数
    semctl(id1, 0, SETVAL, 1);

    return 0;
}
