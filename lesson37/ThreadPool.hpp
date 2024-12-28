#pragma once;
#include"Thread.hpp"
#include"Mutex.hpp"
#include<iostream>
#include<string>
#include<cassert>
#include<memory>
#include<functional>
#include<pthread.h>
#include<vector>
#include<queue>
#include <unistd.h>
using namespace ThreadNs;

const int gnum=5;
template<class T>
class ThreadPool;
template<class T>
class ThreadDate
{
    public:
    ThreadDate(string name,ThreadPool<T>* threadpool)
    :name(name)
    ,threadpool(threadpool)
    {}
    string name;
    ThreadPool<T>* threadpool;
};
template<class T>
class ThreadPool
{
    private:
     static void* handlertask(void* args)
    {
        ThreadDate<T>* td=static_cast<ThreadDate<T>*>(args);
        while(1)
        {
            // cout<<"hand1"<<endl;
            sleep(1);
            td->threadpool->lockqueue();
            while(td->threadpool->_queue.empty())
            {
                pthread_cond_wait(&(td->threadpool->_cond),&(td->threadpool->_mutex));
            } 
            T t=td->threadpool->_queue.front(); 
            td->threadpool->_queue.pop();
             td->threadpool->unlockqueue();

            t();

            cout<<"线程:"<<td->name<<"处理了任务"<<endl;

        }
        return nullptr;

    }
    public:
    void lockqueue()
    {
        pthread_mutex_lock(&_mutex);
    }
    void unlockqueue()
    {
        pthread_mutex_unlock(&_mutex);
    }
    const static int gnum=5;
    ThreadPool(const int& num=gnum)
    :_num(num)
    {
        pthread_mutex_init(&_mutex,nullptr);
        pthread_cond_init(&_cond,nullptr);
        for(int i=0;i<_num;i++)
        {
            _threads.push_back(new ThreadNs::Thread());

        }
    }
    void run()
    {
        for(auto& t:_threads)
        {
            ThreadDate<T> *td=new ThreadDate<T>(t->threadname(),this);
            t->start(handlertask,td);
            cout<<t->threadname()<<endl;
            
        }
    }
    void join()
    {
            for(auto& t:_threads)
        {
            cout<<"join"<<endl;
            t->join();
            
        }
    }
    void Push(const T& in)
    {
        LockGuard lockguard(&_mutex);
        _queue.push(in);
        pthread_cond_signal(&_cond);

    }
    ~ThreadPool()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
        for(auto&t:_threads)
        {
            delete t;
        }
    }
private:
    int _num;
    vector<Thread*>  _threads;
    queue<T> _queue;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
};