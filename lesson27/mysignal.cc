#include<iostream>
#include<signal.h>
#include<unistd.h>
using namespace std;
int cnt=0;
void catchSig(int signo)
{

    cout<<"捕捉到一个异常，编号是:"<<signo<<endl;
}
int main(int argc,char* argv[])
{
    
    for(int i=1;i<=31;i++)
    {
        signal(i,catchSig);
    }

   while(1)
   {
    cout<<"这是一个进程，pid:"<<getpid()<<endl;
    sleep(1);
   }
    
    // signal(SIGALRM,catchSig);
    // alarm(1);
    // while(true)
    // {
    //     // cout<<"cnt:"<<cnt++<<endl;
    //     cnt++;
    // }   
}