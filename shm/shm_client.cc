#include"comm.hpp"

int main()
{

    key_t k=getkey();
    printf("0x%x\n",k);
    int shmid=getShm(k);
    printf("shmid:%d\n",shmid);
    
    char* mem=(char*)attachShm(shmid);
    cout<<"attach success address start:"<<mem<<endl;
    
    const char* message="hello server ,我是另一个进程，正在和你通信";
    pid_t id=getpid();
    int cnt=10;
    
    // char buffer[1024];
    while(cnt--)
    {
        snprintf(mem,MAX_SIZE,"%s[pid:%d][编号:%d]",message,id,cnt);
        sleep(1);
        
    }
    //去关联
    detachShm(mem);
    return 0;
}