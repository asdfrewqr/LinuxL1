#pragma once;
#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<queue>
using namespace std;
#include<functional>
using namespace std;


template<class T>
class BlockQueue
{
public:
    static const int gmaxcap=5;
public:
    
    BlockQueue(const int& max=gmaxcap)
    :_max(max)
    {
        pthread_mutex_init(&_lock,nullptr);
        pthread_cond_init(&_prod,nullptr);
        pthread_cond_init(&_cons,nullptr);

    }
    void push(const T& in)
    {
        pthread_mutex_lock(&_lock);
        while(is_full())
        {
            pthread_cond_wait(&_prod,&_lock);
        }
        _data.push(in);
        pthread_cond_signal(&_cons);
        pthread_mutex_unlock(&_lock);

    }
    void pop(T* out)
    {
        pthread_mutex_lock(&_lock);
        while(is_empty())
        {
            pthread_cond_wait(&_cons,&_lock);
        }
        *out=_data.front();
        _data.pop();
        pthread_cond_signal(&_prod);
        pthread_mutex_unlock(&_lock);
    }
    ~BlockQueue()
    {
        pthread_mutex_destroy(&_lock);
        pthread_cond_destroy(&_prod);
        pthread_cond_destroy(&_cons);
    }
    bool is_empty()
    {
        return _data.empty();
    }
    bool is_full()
    {
        return _data.size()-_max==0;
    }
private:
    
    queue<T> _data;
    int _max;
    pthread_mutex_t _lock;
    pthread_cond_t _prod;
    pthread_cond_t _cons;

};