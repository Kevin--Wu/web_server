#include <iostream>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main()
{
    int nConFd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in stAddr;
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = inet_addr("192.168.1.111");
    stAddr.sin_port = htons(12300);

    int nRetSts = connect(nConFd, (sockaddr *)&stAddr, sizeof(stAddr));
    if(nRetSts == -1)
        return -1;

    int nMaxRecvLen = 1024;
    char szRecv[nMaxRecvLen];
    int nRecvLen = 0;
    while(true)
    {
        nRecvLen = recv(nConFd, szRecv, nMaxRecvLen, 0);
        cout<<szRecv<<" "<<nRecvLen<<endl;
        sleep(5);
    }

    return 0;
}
