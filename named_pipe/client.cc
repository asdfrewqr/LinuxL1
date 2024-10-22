#include"comm.hpp"

int main()
{

   
    int rfd=open(NAMED_PIPE,O_WRONLY);
    if(rfd<0)
    exit(1);

    char buffer[1024];
    while(true)
    {
        cout<<"Please say"<<endl;
        fgets(buffer,sizeof(buffer),stdin);
        int n=write(rfd,buffer,strlen(buffer));
        assert(n==strlen(buffer));
        (void)n;
    }
    close(rfd);
    
    return 0;
}