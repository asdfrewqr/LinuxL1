#include"BlockQueue.hpp"
#include"Task.hpp"


class Sum{
public:
using func=function<int(int,int,char)>;
Sum()
{}
Sum(int x,int y,char op,func f)
    :_x(x)
    ,_y(y)
    ,_op(op)
    ,_fun(f)
{
   
}
int operator()()
{
    return _fun(_x,_y,_op);
}

private:
    int _x;
    int _y;
    char _op;
    func _fun;
};
template<class C,class T>
class BlockQueues
{
public:
    BlockQueue<C> *q1;
    BlockQueue<T> *q2;


};
void* processor(void* args)
{
    BlockQueue<Cal>* bq=static_cast<BlockQueues<Cal,Saver>*>(args)->q1;
    
    while(1)
    {
        int x1=rand()%50;
        int y1=rand()%50;
        int n=rand()%oper.size();
        cout<<"size"<<sizeof(oper)<<endl;
        Cal s(x1,y1,oper[n],mymath);
        bq->push(s);
        cout<<"生产数据: "<<x1<<oper[n]<<y1<<endl;
        // sleep(1);
        
    }
    return nullptr;

}

void* customer(void* args)
{
    BlockQueue<Cal>* bq1=static_cast<BlockQueues<Cal,Saver>*>(args)->q1;
    BlockQueue<Saver>* bq2=static_cast<BlockQueues<Cal,Saver>*>(args)->q2;
    while(1)
    {
        Cal data;
        bq1->pop(&data);
        string str=data();
        cout<<"消费数据: "<<str<<endl;
        Saver saver(str,Save);
        bq2->push(saver);
        cout<<"存储"<<endl;
        sleep(1);
    }
    return nullptr;
}

void* saver(void* args)
{
    BlockQueue<Saver>* bq=static_cast<BlockQueues<Cal,Saver>*>(args)->q2;
    while(1)
    {
        Saver s;
        bq->pop(&s);
        s();
        cout<<"存储成功"<<endl;

        // sleep(1);
    }
    return nullptr;
}
int main()
{
    srand((unsigned int)time(0));

    BlockQueues<Cal,Saver> bqs;
    bqs.q1=new BlockQueue<Cal>(5);
    bqs.q2=new BlockQueue<Saver>(5);
    pthread_t c,p,s;
    pthread_create(&p,nullptr,processor,&bqs);
    pthread_create(&c,nullptr,customer,&bqs);
    pthread_create(&s,nullptr,saver,&bqs);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);
    pthread_join(s,nullptr);

    return 0;
}