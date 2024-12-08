#include<iostream>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <cstdlib>
#include <sys/wait.h> 
using namespace std;
void handler(int signo)
{
    cout<<signo<<"信号正在被捕捉"<<endl;
}
void Count(int n)
{

    while(n)
    {
        cout<<n<<endl;
        n--;
        sleep(1);
    }
}
int main()
{
    signal(SIGCHLD,handler);
    pid_t id=fork();
    if(id==0)
    {
        cout<<"我是子进程,我的pid:"<<getpid()<<"我的父进程id:"<<getppid()<<endl;
        Count(3);
        exit(1);
    }
   
    else if (id > 0)  // 父进程
    {
        // 父进程等待子进程退出
        wait(NULL);  // 触发SIGCHLD信号
    }

    return 0;
}