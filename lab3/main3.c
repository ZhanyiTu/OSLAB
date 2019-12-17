//
// Created by tzy on 2019/12/17.
//
/*主程序框架
main()
{	创建KEY的共享内存组；
    创建KEY的信号灯；
    信号灯赋初值；
    创建两个子进程readbuf、writebuf;
    等待两个子进程运行结束；
    删除信号灯；
    删除共享内存组；
}
readbuf负责读、writebuf负责写，如何定义？
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
    } }*/
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#define  SHMKEY  75
#include <unistd.h>
#include <wait.h>

int main(){
    printf("hello\n");
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
    shmid=shmget(SHMKEY,1024,0666|IPC_CREAT); */
/*创建共享存储区*//*

    addr=shmat(shmid,0,0);        */
/*获取首地址*//*

    do
    {
        *addr=-1;
        while (*addr==-1);
        printf("(server) received\n");
    }while (*addr);
    shmctl(shmid,IPC_RMID,0);     */
/*撤消共  享存储区，归还资源*//*

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
}*/
