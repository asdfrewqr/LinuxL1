#include<iostream>
#include<pthread.h>
#include<string>
#include<cstdio>
#include<unistd.h>
#include<string.h>
#include"Thread.hpp"
using namespace std;
string changeId(pthread_t id)
{
    char tid[128];
    snprintf(tid,sizeof(tid),"0x%x",id);
    return tid;
}
void* start_routine(void* arg) {
    // Cast argument to const char* and convert to string
    string threadname = static_cast<const char*>(arg);
    
    int n=5;
    // Run an infinite loop to simulate continuous work in the thread
    while (n) {
        // Print the thread name
        char tid[128];
        snprintf(tid,sizeof(tid),"0x%x",pthread_self());
        cout << "Thread name: " << threadname <<"tid:"<<tid<< endl;
        // Sleep for 1 second to simulate some work
        sleep(1);
        n--;
    }

    // Return null pointer (standard practice for thread functions)
    return nullptr;
}
// int main()

// {
//     pthread_t tid;
//     pthread_create(&tid,nullptr,start_routine,(void*)"thread1");

//     string main_id=changeId(pthread_self());
//     cout<<"main id: "<<main_id<<" new id: "<<changeId(tid)<<endl;
//     pthread_detach(tid);
//     int n=pthread_join(tid,nullptr);
//     cout<<"result: "<<n<<" "<<" "<<strerror(n)<<endl;
// }
pthread_mutex_t  lock=PTHREAD_MUTEX_INITIALIZER;
int ticket=10000;
void* thread_run1(void* args)
{
    int n=5;
    string str=static_cast<const char*>(args);
    
    while(1)
    {
        // pthread_mutex_lock(&lock);
        if(ticket>0)
        {
        cout<<"用户"<<str<<"在抢票:"<<ticket<<endl;
        ticket--;
        // pthread_mutex_unlock(&lock);
        }
        else
        {
            // pthread_mutex_unlock(&lock);
            break;
            
        }
        usleep(1000);
        // sleep(1);
    }
}
void* thread_run2(void* args)
{
    int n=5;
    string str=static_cast<const char*>(args);
    
    while(1)
    {
        // pthread_mutex_lock(&lock);
        if(ticket>0)
        {
        cout<<"用户"<<str<<"在抢票:"<<ticket<<endl;
        ticket--;
        // pthread_mutex_unlock(&lock);
        }
        else
        {
            // pthread_mutex_unlock(&lock);
            break;
            
        }
        usleep(1000);
        // sleep(1);
    }
}
int main()
{

    Thread* t1=new Thread(thread_run1,(void*)"hello1",1);
    Thread* t2=new Thread(thread_run1,(void*)"hello2",2);
    Thread* t3=new Thread(thread_run2,(void*)"hello3",3);
    t1->start();
    t2->start();
    t3->start();

    t1->join();
    t2->join();
    t3->join();

}