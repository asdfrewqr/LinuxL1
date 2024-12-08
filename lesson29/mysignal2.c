// #include<iostream>
#include<signal.h>
#include<stdio.h>

#include<unistd.h>


int quit=0;
void handler(int signo)
{
    printf("信号:%d，正在被捕捉\n",signo);
    
    printf("quit:%d",quit);
    quit=1;
    printf("->%d ",quit);
}
int main()
{
    signal(2,handler);

    while(!quit)
    sleep(1);
    printf("我是正常退出的\n");
    return 0;
}