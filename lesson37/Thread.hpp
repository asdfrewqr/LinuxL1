#pragma once;
#include<iostream>
#include<string>
#include<cassert>
#include<memory>
#include<functional>
#include<pthread.h>
#include <unistd.h>
using namespace std;
namespace ThreadNs{
using func_t=function<void*(void*)>;
const int num=1024;
class Thread;
class Context
{
    public:
    Thread* _this;
    void *_args;
    Context()
    :_this(nullptr)
    ,_args(nullptr)
    {}
    ~Context()
    {

    }
};
class Thread
{
public:
   
    Thread()
   
    {
        char buffer[1024];
        snprintf(buffer,sizeof(buffer),"thread->%d",threadnum++);
        _name=buffer;
    }
    static void* start_routine(void * args)//类内成员，定义为缺省参数，减少默认this参数
    {
        Thread* _this=static_cast<Thread*>(args);
        void* ret=_this->run(_this->_args);
        delete _this;
        return ret;
        //静态方法不能调用成员方法和变量
        
    }
    void start(func_t fun,void* args=nullptr)
    {
        _func=fun;
        _args=args;
        int n=pthread_create(&_tid,nullptr,start_routine,this);
        assert(n==0);
        (void)n;
    }
    void join()
    {
        int n=pthread_join(_tid,nullptr);
        assert(n==0);
        (void)n;
    }
    void *run(void* args)
    {
       return  _func(args);
    }
    string threadname()
    {
        return _name;
    }
    ~Thread()
    {}
private:
 string _name;
 pthread_t _tid;
 func_t _func;
 void* _args;
 static int threadnum;
};
int Thread::threadnum=1;
}
// class Context
// {
// public:
//     Thread* _this;
//     void *_args;
//     Context()
//     :_this(nullptr)
//     ,_args(nullptr)
//     {}
//     ~Context()
//     {

//     }
// };



