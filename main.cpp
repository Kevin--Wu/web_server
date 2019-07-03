#include <iostream>
using namespace std;

#include <sys/socket.h>

int main()
{
	int nNetFd = socket(AF_INET, SOCK_STREAM, 0);
	cout<<nNetFd<<endl;
	
	return 0;
}
