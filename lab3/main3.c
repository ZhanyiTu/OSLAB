//
// Created by tzy on 2019/12/17.
//
/*
readbuf负责读、writebuf负责写，如何定义？
 主程序框架
main()
{	创建KEY的共享内存组；
    创建KEY的信号灯；
    信号灯赋初值；
    创建两个子进程readbuf、writebuf;
    等待两个子进程运行结束；
    删除信号灯；
    删除共享内存组；
}

writebuf
main() {
    获取KEY的共享内存组；
    建立数组形式环形缓冲；
    获取KEY的信号灯；
    创建目标文件；
    while (1) {
        信号灯P操作；
        取缓冲区数据；
        写入文件； *//*有效数据或结束*//*
        移动环形缓冲区指针；
        信号灯V操作；
        if  (数据结束)  break;
    } }
readbuf
main() {
    获取KEY的共享内存组；
    建立数组形式环形缓冲；
    获取KEY的信号灯；
    打开原文件；
    while (1) {
        信号灯P操作；
        读文件数据；
        放入数据； *//*有效数据或结束*//*
        移动环形缓冲区指针；
        信号灯V操作；
        if  (文件结束)  break;
    }}
    */
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#define  SHMKEY  75
#include <unistd.h>
#include <wait.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#define N 5 //把缓冲区分成5块
pid_t p1;//创建子进程1 2
pid_t p2;
union semun{
    short val;
    struct semid_ds* buf;
    unsigned short* array;

}arg;
char *buf[N];//N = 5
int i;// = (i + 1)mod N?
int shmid;
//int  shmid,i;
int  *addr;
int id1;
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
int main(){
    pid_t t1;
    int status1, status2;
    shmid=shmget(SHMKEY,1024,0666|IPC_CREAT);
//创建共享存储区
    addr=shmat(shmid,0,0);
//获取首地址
    id1 = semget(IPC_PRIVATE, 2, IPC_CREAT|0666 );//信号灯创建，3个参数 问题就出在这个参数上，参数写错了所以都错了

    arg.val = 1;//信号灯赋初值
    semctl(id1, 0, SETVAL, arg);
    arg.val = 0;
    semctl(id1, 1, SETVAL, arg);
    p1 = fork();
    if( p1 == 0){
        //子进程1 readbuf
        addr=shmat(shmid,0,0);//获取分享的空间
        P(id1, 0);
        V(id1, 1);
    }
    else{
        p2 = fork();
        if(p2 == 0){
            //子进程2
        }
        else{
            //主进程
            t1 = waitpid(p1, &status1, 0);//暂停目前进程的执行， 直到有信号来或者子进程结束 pid 是要等待的进程
            t1 = waitpid(p2, &status2, 0);//暂停目前进程的执行， 直到有信号来或者子进程结束 pid 是要等待的进程
            semctl(id1, 0, IPC_RMID, 1);
            shmctl(shmid,IPC_RMID,0);
        }
    }
}


/*
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#define  SHMKEY  75
#include <unistd.h>
#include <wait.h>
int  shmid,i;   int  *addr;
void  server( )
{
    shmid=shmget(SHMKEY,1024,0666|IPC_CREAT);
//创建共享存储区

    addr=shmat(shmid,0,0);
//获取首地址

    do
    {
        *addr=-1;
        while (*addr==-1);
        printf("(server) received\n");
    }while (*addr);
    shmctl(shmid,IPC_RMID,0);
//撤消共  享存储区，归还资源

    exit(0);
}


void  client( ){
    shmid=shmget(SHMKEY,1024,0666);
    addr=shmat(shmid,0,0);//获取分享的空间
    for (i=9;i>=0;i--)
    {  while (*addr!=-1);
        printf("(client) sent\n");
        *addr=i;
    }
    exit(0);
}
main( ){
    while ((i=fork( ))==-1);
    if (!i) server( );
    system("ipcs  -m");
    while ((i=fork( ))==-1);
    if (!i) client( );
    wait(0);
    wait(0);
}
*/
