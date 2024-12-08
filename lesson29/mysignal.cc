#include<iostream>
#include<signal.h>
#include<unistd.h>
#include<vector>
using namespace std;

void handler(int signo)
{
    cout<<"get a signo"<<signo<<"正在处理"<<"pid:"<<getpid()<<endl;
    sleep(15);
}
int main()
{
    struct sigaction act,oact;
    act.sa_handler=handler;
    act.sa_flags=0;

    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,3);//当处理某个 信号期间，也想屏蔽其他信号，就可以添加到这个sa_mask中
    sigaction(SIGINT,&act,&oact);

    while(true)
    sleep(1);
    return 0;
}