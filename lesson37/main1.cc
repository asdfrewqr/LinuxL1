#include"Thread.hpp"
#include"ThreadPool.hpp"
#include"Task.hpp"
void* run(void*args)
{   
    char* t=static_cast<char*>(args);

    while(1)
    {
        cout<<t<<endl;
        sleep(1);
    }
}


void task(ThreadPool<Cal>* tp)
{
    const string oper="+-*/";
    int n=5;
    while(1)
    {
        int x1=rand()%50;
        int y1=rand()%50;
        int n=rand()%oper.size();
       
        Cal s(x1,y1,oper[n],mymath);
        tp->Push(s);
        sleep(1);
        cout<<"生产数据: "<<x1<<oper[n]<<y1<<endl;
        sleep(1);
        
    }

}
int main()
{

    ThreadPool<Cal>* tp=new ThreadPool<Cal>(5);
    tp->run();
    task(tp);
    // tp->join();

    // tp->join();
    
 }