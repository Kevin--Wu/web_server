#include <iostream>
using namespace std;

#include <pthread.h>
#include <sys/socket.h>

#include "ClientReactor.h"
#include "EventLoop.h"

ClientReactor::ClientReactor(int nClientFd)
{
    //ctor
    m_nClientFd = nClientFd;
}

ClientReactor::~ClientReactor()
{
    //dtor
}

void ClientReactor::BeginRoutine()
{
    pthread_t nTid;
    pthread_create(&nTid, NULL, Routine, (void *)this);
}
