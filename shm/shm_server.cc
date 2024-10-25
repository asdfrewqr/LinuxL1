#include"comm.hpp"


int main()
{
    printf("testt\n");
    
    key_t k=getkey();
    printf("0x%x\n",k);
    
    int shmid=createShm(k);
    printf("shmid:%d\n",shmid);
    sleep(5);
    char* mem=(char*)attachShm(shmid);
    cout<<"attach success address start:"<<mem<<endl;
    sleep(5);
    int cnt=20;
    while(cnt--)
    {
        printf("client say:%s\n",mem);
        struct shmid_ds ds;
        shmctl(shmid,IPC_STAT,&ds);
        printf("获取属性:size:%d,pid:%d,myself:%d,key:0x%x\n",ds.shm_segsz,ds.shm_cpid,getpid(),ds.shm_perm.__key);
        sleep(1);
    }
    //去关联
    detachShm(mem);
    //删除共享内存
    delShm(shmid);
    

    return 0;
}