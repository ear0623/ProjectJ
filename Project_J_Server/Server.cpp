#include <WinSock2.h>
#include <windows.h>
#include <process.h>

#pragma comment(lib,"ws2_32")



int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = AF_INET;
	ListenSockAddr.sin_addr.s_addr = INADDR_ANY;//老窜
	ListenSockAddr.sin_port = htons(15689);

	bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));

	listen(ListenSocket, 5);
	// 罐绰 家南
	
	SOCKADDR_IN ClientSocketAddr;
	memset(&ClientSocketAddr, 0, sizeof(ClientSocketAddr));
	int ClientSockAddrSize = sizeof(ListenSockAddr);
	SOCKET ClientSocket = accept(ListenSocket,(SOCKADDR*)&ClientSocketAddr,&ClientSockAddrSize);
	//accept 家南

	//HANDLE ThreadHandle = (HANDLE)_beginthreadex(0,)


	closesocket(ListenSocket);
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}