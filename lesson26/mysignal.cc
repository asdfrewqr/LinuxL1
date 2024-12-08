#include<iostream>
#include<unistd.h>
#include<signal.h>
using namespace std;

void handler(int signo)
{
    cout<<"进程捕捉到一个信号，该信号是:"<<signo<<endl;
}
int main()
{
    signal(2,handler);
    while(true)
    {
        cout<<"我是一个进程"<<getpid()<<endl;
        sleep(2);
    }
}