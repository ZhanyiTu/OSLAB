//#include<stdio.h>
//#include<stdlib.h>
//#include<signal.h>
//void my_func(int sig_no) {
//    if(sig_no == SIGUSR1)
//        printf("Receive SIGUSR1.\n");
//    if(sig_no == SIGUSR2)
//        printf("Receive SIGUSR2.\n");
//    if(sig_no == SIGINT) {
//        printf("Receive SIGINT.\n");
//        exit(0);
//    }
//}
//int main(void) {
//
//if(signal(SIGUSR1, my_func) == SIG_ERR)//my_func是函数 SIGUSR1应该是定义的常量吧 singal()第一个参数是信号值 第二个是指向函数的指针 将这个信号设定功能 返回值是func的返回值
//    printf("can't catch SIGUSR1.\n'");
//if(signal(SIGUSR2, my_func) == SIG_ERR)//只是绑定 不执行
//    printf("can't catch SIGUSR2.\n'");
//if(signal(SIGINT, my_func) == SIG_ERR)
//    printf("can't catch SIGINT.\n'");
//    kill(getpid(),SIGINT);//只有kill才会发信号 功能是自己定义的函数
//    while(1);
//return 0;
//}
