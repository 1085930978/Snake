#include<WINSOCK2.H>
#include<STDIO.H>
#include<iostream>
#include<string>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#define N 21
#include<iostream>
using namespace std;

#pragma comment(lib, "ws2_32.lib")


SOCKET sclient;
int a;
int b;
const char * sendData = "hello \n";

int Setconnect()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
		sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sclient == INVALID_SOCKET)
		{
			printf("invalid socket!");
			return 0;
		}

		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(8888);
		serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{  //连接失败 
			printf("connect error !");
			closesocket(sclient);
			return 0;
		}

	return 1;
	
}

void position(int x, int y)  //位置函数，把光标位置进行瞄准。 (windows.h)
{
	COORD a;
	a.X = 2 * x;
	a.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
void window(char foodx[],char foody[], int food[])   //窗口初始化。 
{
	int i, j;
	int wall[N + 2][N + 2] = { { 0 } };
	for (int i = 1; i <= N; i++)    //墙壁：第一行和最后一行，第一列和最后一列。 (0和N+1)
	{
		for (int j = 1; j <= N; j++)
		{
			wall[i][j] = 1;
		}
	}

	for (int i = 0; i<N + 2; i++)
	{
		for (int j = 0; j<N + 2; j++)
		{
			if (wall[i][j])
			{
				cout << "  ";
			}
			else cout << "□";
		}
		cout << endl;   //很重要 
	}

	position(N + 3, 1);
	cout << "按 W S A D 移动方向" << endl;
	position(N + 3, 2);
	cout << "按q键暂停,方向键继续" << endl;
	position(N + 3, 3);
	cout << "分数:" << endl;


	send(sclient, sendData, strlen(sendData), 0);


	
	recv(sclient, foodx, 4, 0);
	recv(sclient, foody, 4, 0);


	memcpy(&a, foodx, 4);
	memcpy(&b, foody, 4);

	food[0] = a;
	food[1] = b;
	position(food[0], food[1]);
	cout << "●" << endl;
}

int Game(char foodx[], char foody[])
{
	int i = 0, j = 0;
	int **snake = NULL;
	int score = 0;
	char direction = 'f'; //保存现在蛇的前进方向 
	int tail[2];
	int len = 3;
	char q = 'o';
	int *xy;
	int food[2];
	window(foodx,foody,food);
	int tempx;
	int tempy;
	snake = (int**)realloc(snake, sizeof(int*)*len); //修改已分配的内存。 
	for (i = 0; i<len; i++)
	{
		snake[i] = (int*)malloc(sizeof(int) * 2);//分配连续内存   (从堆内分配内存，分配的是动态内存,新的内存。)
	}
	for (int i = 0; i<len; i++)
	{
		snake[i][0] = N / 2;
		snake[i][1] = N / 2 + i;             //竖着放的初始蛇。 
		position(snake[i][0], snake[i][1]);
		cout << "★" << endl;
	}
	while (1)
	{
		tail[0] = snake[len - 1][0];
		tail[1] = snake[len - 1][1];
		position(tail[0], tail[1]);
		cout << "  " << endl;

		for (int i = len - 1; i>0; i--)
		{
			snake[i][0] = snake[i - 1][0];
			snake[i][1] = snake[i - 1][1];
			position(snake[i][0], snake[i][1]);
			cout << "★" << endl;

		}
		if (kbhit())
		{
			position(0, N + 2);
			q = getche();  //conio.h

		}

		switch (q)
		{
		case 'w': if (direction != 's')direction = 'w'; break;
		case 's': if (direction != 'w')direction = 's'; break;
		case 'd': if (direction != 'a')direction = 'd'; break;
		case 'a': if (direction != 'd')direction = 'a'; break;
		default:break;
		}

		switch (direction)
		{
		case 'w': if (direction != 's')snake[0][1]--; break;  //往上是递减坐标。 
		case 's': if (direction != 'w')snake[0][1]++; break;
		case 'd': if (direction != 'a')snake[0][0]++; break;
		case 'a': if (direction != 'd')snake[0][0]--; break;
		default:break;
		}

		position(snake[0][0], snake[0][1]);
		cout << "★" << endl;
		Sleep(100);


		if (snake[0][0] == food[0] && snake[0][1] == food[1])
		{
			len++;
			score++;
			snake = (int**)realloc(snake, sizeof(int*)*len);
			snake[len - 1] = (int*)malloc(sizeof(int) * 2);
			
			send(sclient, sendData, strlen(sendData), 0);

			recv(sclient, foodx, 4, 0);
			recv(sclient, foody, 4, 0);

			memcpy(&a, foodx, 4);
			memcpy(&b, foody, 4);

			food[0] = a;
			food[1] = b;
			position(food[0], food[1]);
			cout << "●" << endl;

			position(N + 5, 3);
			cout << score << endl;
		}
		if (snake[0][0] == 0 || snake[0][0] == N || snake[0][1] == 0 || snake[0][1] == N)
		{
			position(N / 2, N / 2);
			cout << "failure:空格重新开始,q键退出。" << endl;
			for (int i = 0; i<len; i++)
				free(snake[i]); //释放内存,结束游戏 		
			while (1)
			{

				q = getche();
				if (q == ' ')
				{
					system("Cls");
					return 1;
				}
				else if (q == 'q')
				{
					return 0;
				}
				else continue;
			}

		}

		if (direction != 'f')
			for (int i = 1; i<len; i++)
			{
				xy = snake[i];
				if (snake[0][0] == xy[0] && snake[0][1] == xy[1])
				{
					position(N / 2, N / 2);
					cout << "failure:空格重新开始,q键退出。" << endl;
					for (int i = 0; i<len; i++)
						free(snake[i]); //释放内存,结束游戏 

					while (1)
					{
						q = getche();
						if (q == ' ')
						{
							system("Cls");
							return 1;
						}
						else if (q == 'q')
						{
							return 0;
						}
						else continue;
					}

				}
				else continue;
			}
	}
}
int main()
{
	if (Setconnect() == 0)
	{
		printf("connect error !");
		closesocket(sclient);
		return 0;
	}
	char foodx[4];
	char foody[4];
	while (1)
	{
		int temp=Game(foodx,foody);
		if (temp == 0)
		{
			closesocket(sclient);
			WSACleanup();
			exit(0);
		}
		else continue;
	}

	return 0;
}

