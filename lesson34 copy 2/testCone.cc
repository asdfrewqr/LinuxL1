#include"BlockQueue.hpp"

const char* oper="+-*/";
int mymath(int x,int y,char op)
{
    int result=0;
    switch(op)
    {
        case '+':
        result=x+y;
        break;
        case '-':
        result=x-y; 
        break;
        case '*':
        result=x*y;
        break;
        case '/':
        if(y==0)
        {
            cout<<"div zero error"<<endl;
            result=-1;
        }
        else
        {
            result=x/y;
        }
        default:
        break;
    }
    return result;
}

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
void* processor(void* args)
{
    BlockQueue<Sum>* bq=static_cast<BlockQueue<Sum>*>(args);
    
    while(1)
    {
        int x1=rand()%50;
        int y1=rand()%50;
        int n=rand()%sizeof(oper);
        Sum s(x1,y1,oper[n],mymath);
        bq->push(s);
        cout<<"生产数据: "<<x1<<oper[n]<<y1<<endl;
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
        // sleep(1);
    }
    return nullptr;
}

int main()
{
    srand((unsigned int)time(0));
    BlockQueue<Sum> *bq=new BlockQueue<Sum>(5);
    pthread_t c,p;
    pthread_create(&p,nullptr,processor,bq);
    pthread_create(&c,nullptr,customer,bq);

    pthread_join(c,nullptr);
    pthread_join(p,nullptr);

    return 0;
}