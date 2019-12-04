#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include <unistd.h>
#include <wait.h>

int pipefd[2];

void my_func(int sig_no) {
    if(sig_no == SIGUSR1){
    printf("Receive SIGUSR1.\n");
    close(pipefd[1]);
    }

    if(sig_no == SIGUSR2){
    printf("Receive SIGUSR2.\n");
    close(pipefd[0]);
    }
    if(sig_no == SIGINT) {
        printf("Receive SIGINT.\n");
        exit(0);
    }
}
int main(void){
if(signal(SIGINT, my_func) == SIG_ERR)
    printf("can't catch SIGINT.\n'");
pid_t p1;//创建子进程1 2
pid_t p2;
pid_t t1;
    pipe(pipefd); //创建无名管道 pipe[0]只能读 pipe[1]只能写
int status1, status2;
p1 = fork();
if(p1 == 0){//子进程pid = 0
puts("sub1 created\n");//puts 向屏幕输出字符串
if(signal(SIGUSR1, my_func) == SIG_ERR)//my_func是函数 SIGUSR1应该是定义的常量吧 singal()第一个参数是信号值 第二个是指向函数的指针 将这个信号设定功能 返回值是func的返回值
    printf("can't catch SIGUSR1.\n'");
if(signal(SIGINT, my_func) == SIG_ERR)
    printf("can't catch SIGINT.\n'");
int x = 0;
while(1){
char buf1[50];
sprintf(buf1, "I send you %d times\n", x);
x++;
write(pipefd[1], buf1, 49);
sleep(1);
}
}
else//父进程pid=1
{
p2 = fork();

if(p2 == 0){//子进程pid = 0
puts("sub2 created\n");//puts 向屏幕输出字符串
if(signal(SIGUSR2, my_func) == SIG_ERR)//my_func是函数 SIGUSR1应该是定义的常量吧 singal()第一个参数是信号值 第二个是指向函数的指针 将这个信号设定功能 返回值是func的返回值
    printf("can't catch SIGUSR2.\n'");
if(signal(SIGINT, my_func) == SIG_ERR)
    printf("can't catch SIGINT.\n'");
while(1){
char buf2[50];
read(pipefd[0], buf2, 49);
printf("%s", buf2);
}}
else//父进程pid=1
{
t1 = waitpid(p1, &status1, 0);//暂停目前进程的执行， 直到有信号来或者子进程结束 pid 是要等待的进程
t1 = waitpid(p2, &status2, 0);//暂停目前进程的执行， 直到有信号来或者子进程结束 pid 是要等待的进程
}

}



    kill(p1,SIGUSR1);//只有kill才会发信号 功能是自己定义的函数
    kill(p2,SIGUSR2);
    return 0;
}
