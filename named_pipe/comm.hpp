#pragma once

#include<iostream>
#include<cerrno>
#include<string>
#include<cstring>
#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>


#define NAMED_PIPE "/tmp/mypipe.106"
using namespace std;

bool createFifo(const string& path)
{
    umask(0);
    int n=mkfifo(path.c_str(),0600);
    if(n==0)
    return true;
    else
    {
        cout<<"errno:"<<errno<<"err string"<<strerror(errno)<<endl;
        return false;
    }
}
void removeFifo(const string&path)
{
    int n=unlink(path.c_str());
    assert(n==0);
    (void)n;
}