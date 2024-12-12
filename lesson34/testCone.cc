#include"BlockQueue.hpp"

class Sum{
public:
Sum()
{}
Sum(int x,int y)
    :_x(x)
    ,_y(y)
{
   
}
int operator()()
{
    return _x+_y;
}
private:
    int _x;
    int _y;
};
void* processor(void* args)
{
    BlockQueue<Sum>* bq=static_cast<BlockQueue<Sum>*>(args);
    
    while(1)
    {
        int x1=rand()%50;
        int y1=rand()%50;
        Sum s(x1,y1);
        bq->push(s);
        cout<<"生产数据: "<<x1<<" "<<y1<<endl;
        sleep(1);
    }
    return nullptr;

}

void* customer(void* args)
{
    BlockQueue<Sum>* bq=static_cast<BlockQueue<Sum>*>(args);
    while(1)
    {
        Sum data;
        bq->pop(&data);
        cout<<"消费数据: "<<data()<<endl;
    }
    return nullptr;
}

int main()
{
    srand((unsigned int)time(0));
    BlockQueue<int> *bq=new BlockQueue<int>(5);
    pthread_t c,p;
    pthread_create(&p,nullptr,processor,bq);
    pthread_create(&c,nullptr,customer,bq);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);

    return 0;
}