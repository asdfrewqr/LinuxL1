#include"comm.hpp"

int main()
{

    bool r=createFifo(NAMED_PIPE);
    assert(r);
    (void)r;
    int rfd=open(NAMED_PIPE,O_RDONLY);
    if(rfd<0)
    exit(1);

    char buffer[1024];

    while(true)
    {
        ssize_t s=read(rfd,buffer,sizeof(buffer)-1);
        if(s>0)
        {
            buffer[s]=0;
            cout<<"client->server#"<<buffer<<endl;
        }
        else if(s==0)
        {
            cout<<"client quit me too"<<endl;
            break;
        }
        else
        {
            cout<<"error "<<strerror(errno)<<endl;
            break;
        }
    }
    close(rfd);
    removeFifo(NAMED_PIPE);
    return 0;
}