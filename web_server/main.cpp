#include <iostream>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ClientReactor.h"

using namespace std;

int main()
{
    int nConFd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in stAddr;
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = inet_addr("192.168.1.111");
    stAddr.sin_port = htons(12300);

    int nRetSts = 0;
    bind(nConFd, (sockaddr *)&stAddr, sizeof(stAddr));
    nRetSts = listen(nConFd, 3);
    if (nRetSts != 0)
        return -1;

    // Wait for connect
    sockaddr_in stNewClientAddr;
    socklen_t nNewAddrLen;

    int nNewCon = 0;
    while( (nNewCon = accept(nConFd, (sockaddr *)&stNewClientAddr, &nNewAddrLen)) != -1)
    {

        ClientReactor objClReactor(nNewCon);
        objClReactor.BeginRoutine();
    }

    return 0;
}
