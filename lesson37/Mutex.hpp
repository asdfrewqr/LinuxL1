#pragma once

#include<iostream>
#include<pthread.h>

class Mutex
{
public:
    Mutex(pthread_mutex_t *lock=nullptr)
        :_lock(lock)
    {

    }
    void lock()
    {
        pthread_mutex_lock(_lock);
    }
    void unlock()
    {
        pthread_mutex_unlock(_lock);
    }
    private:
        pthread_mutex_t *_lock;

};
class LockGuard
{
    public:
    LockGuard(pthread_mutex_t* mutex)
    :_mutex(mutex)
    {
        _mutex.lock();
    }
    ~LockGuard()
    {
        _mutex.unlock();
    }
    private:
    Mutex _mutex;
};