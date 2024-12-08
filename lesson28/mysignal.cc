#include<iostream>
#include<signal.h>
#include<unistd.h>
#include<vector>
using namespace std;

#define BLOCK_SIGNAL 2
#define MAX_SIGNUM 31

static vector<int> sigarr={2,4};
static void show_pending(const sigset_t &pending)
{
    for(int signo=1;signo<=MAX_SIGNUM;signo++)
    {
        if(sigismember(&pending,signo))
        {
            cout<<"1";
        }
        else cout<<"0";
        
    }
    cout<<endl;
} 
void myhandler(int signo)
{
    cout<<signo<<"号信号已经被抵达"<<endl;
}
int main()
{

    sigset_t block,oblock,pending;
    //初始化
    sigemptyset(&block);
    sigemptyset(&oblock);
    sigemptyset(&pending);
    //添加要屏蔽的信号
    sigaddset(&block,BLOCK_SIGNAL);
    //开始屏蔽，设置进内核
    for(const auto& sig:sigarr )
    {   
        signal(sig,myhandler);
        sigaddset(&block,sig);
    }
    
    sigprocmask(SIG_SETMASK,&block,&oblock);

    int cnt=15;
    //遍历打印pending信号集
    while(true)
    {
        //初始化
        sigemptyset(&pending);
        //获取
        sigpending(&pending);
        //打印
        show_pending(pending);
        cout<<"pid:"<<getpid()<<endl;
        sleep(1);
        if(cnt--<=0)
        {
            sigprocmask(SIG_SETMASK,&oblock,&block);
            cout<<"恢复对信号的屏蔽，不屏蔽任何信号"<<endl;
        }
    }
}