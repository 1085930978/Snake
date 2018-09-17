#include <stdio.h>  
#include <winsock2.h>  
#include<iostream>
#include<string>
#include<time.h>
#include <sstream>
using namespace std;

int main(int argc, char* argv[])
{
	//初始化WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//创建套接字  
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//绑定IP和端口  
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		cout<<"bind error !";
	}

	//开始监听  
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		cout<<"listen error !";
		return 0;
	}

	//循环接收数据  
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);



	char revData[255];
	int x;
	int y;
	srand((unsigned)time(NULL));   //time.h

	while (true)
	{
		cout<<"等待连接...";
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if (sClient == INVALID_SOCKET)
		{
			cout<<"accept error !";
			continue;
		}
		else
		{
			while (1)
			{
				cout << "接受到一个连接:" << inet_ntoa(remoteAddr.sin_addr) << '\n';
				//接收数据  
				int ret = recv(sClient, revData, 255, 0);
				if (ret > 0)
				{
					x = rand() % 21 + 1;
					y = rand() % 21 + 1;


					char xh[4];
					memcpy(xh, &x, 4);
					if (send(sClient, xh, 4, 0) > 0)  // 如果不是4，会传输一些多余的东西，干扰数据的传输。这个4指代对面的字节数。
					{
						cout << x<< '\n';
					}

					char yh[4];
					memcpy(yh, &y, 4);
					if (send(sClient, yh, 4, 0) > 0)
					{
						cout << y << '\n';
					}
				}
				else
				{
					cout << "连接中断.";
					break;
				}
			}
		}
	}
	closesocket(sClient);
	closesocket(slisten);
	WSACleanup();
	return 0;
}
