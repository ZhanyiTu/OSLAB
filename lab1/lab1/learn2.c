//#include <stdio.h>
//#include <stdlib.h>
//#include<signal.h>
//int main(void){
//pid_t p1;
//pid_t t1;
//int status;
//p1 = fork();
//if(p1 == 0){//子进程pid = 0
//puts("sub1 created\n");//puts 向屏幕输出字符串
//}
//else//父进程pid=1
//{
//t1 = waitpid(p1, &status, 0);//暂停目前进程的执行， 直到有信号来或者子进程结束 pid 是要等待的进程
//}
//}
////
//
