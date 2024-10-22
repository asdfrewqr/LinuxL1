#include<iostream>
#include<cstdlib>
#include<cassert>
#include<unistd.h>
#include<cstdio>
#include<vector>
#include<string>
#include<sys/wait.h>
#include<sys/types.h>
using namespace std;
#define PROCESS_NUM 5

typedef void(*func_t)();

void download()
{
    cout<<getpid()<<"下载任务"<<endl;
}
void ioload()
{
    cout<<getpid()<<"IO任务"<<endl;
}
void flushload()
{
    cout<<getpid()<<"刷新任务"<<endl;
}
void makeRand()
{
    srand((unsigned int)time(nullptr)^getpid());
}
void loadTaskFunc(vector<func_t> *out)
{
    assert(out);
    out->push_back(download);
    out->push_back(ioload);
    out->push_back(flushload);
}
class subEp
{
public:
    subEp(pid_t subId,int writeFd)
    :_subId(subId),_writeFd(writeFd)
    {
        char buffer[1024];
        snprintf(buffer,sizeof buffer,"process-%d[pid(%d)-fd(%d)]",_num++,_subId,_writeFd);
        _name=buffer;
    }
    string getname() const
    {
        return _name;
    }

    static int _num;
    string _name;
    pid_t _subId;
    int _writeFd;
    
};
int recvTask(int readfd)
{
    int code=0;
    ssize_t s=read(readfd,&code,sizeof code);
    if(s==4)
    return code;
    else if(s<=0)
    return -1;
    else
    return 0;
}
int subEp::_num=0;
 void createProcess(vector<subEp>* subs,vector<func_t>&funcmap)
 {
 for(int i=0;i<PROCESS_NUM;i++)
    {
        int fds[2];
        int n=pipe(fds);
        assert(n==0);
        (void)n;//防止release版本n失效

        pid_t id=fork();
        if(id==0)
        {

            close(fds[1]);
            while(true)
            {
                int commandN=recvTask(fds[0]);
                if(commandN>=0&&commandN<funcmap.size())
                funcmap[commandN]();
                else if(commandN==-1)
                break;
                else
                {
                    cout<<"sub recv code error"<<endl;
                }
            }
            
            exit(0);
        }
        close(fds[0]);
        subEp sub(id,fds[1]);
        (*subs).push_back(sub);
    }
 }
 void sendTask(const subEp& s,int taskN)
 {
    cout<<"taskN:"<<taskN<<" send to->"<<s.getname()<<endl;
    int n=write(s._writeFd,&taskN,sizeof(taskN));
    assert(n==sizeof(int));
    (void)n;//防止release版本n失效

 }
 void loadBlanceControl(const vector<func_t>&funcmap,const vector<subEp>& subs,int count)
 {
    int cnt=subs.size();
    int taskn=funcmap.size();
    bool quit=false;
    
    while(count--)
    {
        //选择一个子进程
        int sub_idx=rand()%cnt;
    
        //选择一个任务
        int task_idx=rand()%taskn;
        //任务发送给选择的进程
        sendTask(subs[sub_idx],task_idx);

        sleep(1);

    }
    for(int i=0;i<subs.size();i++)
    {
        close(subs[i]._writeFd);
    }
 }
 void waitprocess(vector<subEp> proc)
 {
    for(int i=0;i<proc.size();i++)
    {
        waitpid(proc[i]._subId,nullptr,0);
        cout<<"wait sub process successful"<<proc[i]._subId<<endl;
    }
 }

 
int main()
{
    //建立子进程及和子进程通信的信道
    makeRand();
    vector<func_t> funcmap;
    loadTaskFunc(&funcmap);
    vector<subEp> subs;
    createProcess(&subs,funcmap);
    //父进程控制子进程
    int taskcount=10;
    loadBlanceControl(funcmap,subs,taskcount);
    //回收子进程信息
    waitprocess(subs);
}