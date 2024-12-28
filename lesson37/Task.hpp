#pragma once;
#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<queue>
using namespace std;
#include<functional>
using namespace std;
const string oper="+-*/";
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
        break;
        default:
        break;
    }
    return result;
}
class Cal
{
public:
    using func=function<int(int,int,char)>;
    Cal()
    {

    }
    Cal(int x,int y,char op,func f)
    :_x(x)
    ,_y(y)
    ,_op(op)
    ,_f(f)
    {

    }
    string operator()()

    {   
        int result=_f(_x,_y,_op);
        char buffer[64];
        snprintf(buffer,sizeof(buffer),"%d %c %d = %d\n",_x,_op,_y,result);
        cout<<buffer<<endl;
        return buffer;
    }
private:
    int _x;
    int _y;
    char _op;
    func _f;
   
};
void Save(const string&message)
{
    const string target="./target.txt";
    FILE* fp=fopen(target.c_str(),"a+");
    if(!fp)
    {
        cout<<"fopen error"<<endl;
        return;
    }
    fputs(message.c_str(),fp);
    fclose(fp);
}
class Saver
{
public:
    using func=function<void (string)>;
    Saver()
    {
        
    }
    Saver(string str,func f)
    :_str(str)
    ,_f(f)
    {}
    void operator()()
    {
        _f(_str);

    }
private:
    string _str;

    func _f;
};