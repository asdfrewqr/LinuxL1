#include<iostream>
#include<pthread.h>
#include <unistd.h>
#include<stdio.h>
#include <vector>
using namespace std;
int test_v=0;
string func()
{
   
    return "我是一个独立的方法";
}
class ThreadData
{
    public:
    pthread_t tid;
    char namebuffer[64];
};
class ThreadRunner
{
    public :
    int exit;
    int code;
};
//新线程
void* thread_routine(void* arg)
{
    string t_arg=static_cast<const char*>(arg);
    int n=5;
    while(n--)
    {
        cout<<"我是新线程"<<t_arg<<"我正在运行，"<<func()<<" test_v:"<<test_v++<<endl;
        //
        sleep(1);
    }
    ThreadRunner* tr=new ThreadRunner();
    tr->code=106;
    tr->exit=1;
    // pthread_exit(0);
    return (void*)tr;
}


int main()
{

    pthread_t tid;
    int n=10;
    vector<ThreadData*> tids;
    for(int i=0;i<10;i++)
    {
        ThreadData* td=new ThreadData;
        snprintf(td->namebuffer,sizeof(td->namebuffer),"%s:%d","thread",i);
        pthread_create(&td->tid,NULL,thread_routine,td->namebuffer);  
        tids.push_back(td);
    }
    int m=5;
    //主线程
    while(m--)
    {
        cout<<"我是主线程，我正在运行 ";
        char buffer[1024];
        snprintf(buffer,sizeof(buffer),"0x%x",tid);
        cout<<buffer<<" test_v:";
        cout<<test_v++<<" ";
        cout<<"我的tid是:"<<tid<<endl;
        sleep(1);
    }
    for(auto& iter:tids)
    {   ThreadRunner *ret=nullptr;
        pthread_join(iter->tid,(void**)&ret);
        cout<<iter->namebuffer<<"join success"<<"ret: "<<ret<<"ret->exit: "<<ret->exit<<"ret->code"<<ret->code<<endl;
    }
}
