#pragma once;
#include<iostream>
#include<string>
#include<cassert>
#include<memory>
#include<functional>
#include<pthread.h>
#include <unistd.h>
using namespace std;
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
    using func_t=function<void*(void*)>;
    const int num=1024;
    Thread(func_t fun,void* args,int num)
    :_func(fun)
    ,_args(args)
    {
        char buffer[1024];
        snprintf(buffer,sizeof(buffer),"thread->%d",num);
        _name=buffer;
    }
    static void* start_routine(void * args)//类内成员，定义为缺省参数，减少默认this参数
    {
        Context* ctx=static_cast<Context*>(args);
        void* ret=ctx->_this->run(ctx->_args);
        delete ctx;
        return ret;
        //静态方法不能调用成员方法和变量
        
    }
    void start()
    {
        Context* ctx=new Context();
        ctx->_args=_args;
        ctx->_this=this;
        int n=pthread_create(&_tid,nullptr,start_routine,ctx);
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
    ~Thread()
    {}
private:
 string _name;
 pthread_t _tid;
 func_t _func;
 void* _args;
};
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



