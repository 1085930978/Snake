// snake
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#define N 21
#include<iostream>
using namespace std;

void position(int x,int y)  //位置函数，把光标位置进行瞄准。 (windows.h)
{
	COORD a;
	a.X=2*x;
	a.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void window(int food[2])   //窗口初始化。 
{
	int i,j;
	int wall[N+2][N+2]={{0}};
	for(int i=1;i<=N;i++)    //墙壁：第一行和最后一行，第一列和最后一列。 (0和N+1)
	{
		for(int j=1;j<=N;j++)
		{
			wall[i][j]=1;
		}
	}
	
	for(int i=0;i<N+2;i++)
	{
		for(int j=0;j<N+2;j++)
		{
			if(wall[i][j])
			{
				cout<<"  ";
			}
			else cout<<"□" ;
		}
		cout<<endl;   //很重要 
	}
	
	position(N+3,1);
	cout<<"按 W S A D 移动方向"<<endl;
	position(N+3,2);
	cout<<"按q键暂停,方向键继续"<<endl;
	position(N+3,3);
	cout<<"分数:"<<endl;

	
	food[0]=rand()%N+1; // rand() 0~无穷 +1->1到N 
	food[1]=rand()%N+1; 
	position(food[0],food[1]);
	cout<<"●"<<endl; 
}



int main()
{
	int i=0,j=0;
	int **snake=NULL;
	int score=0;
	int food[2];
	char direction='f'; //保存现在蛇的前进方向 
	int tail[2];
	int len=3;
	char q='o';
	int *xy;
	srand((unsigned)time(NULL));   //time.h
	window(food);

	snake=(int**)realloc(snake,sizeof(int*)*len); //修改已分配的内存。 
	for(i=0;i<len;i++)
	{
	snake[i]=(int*)malloc(sizeof(int)*2);//分配连续内存   (从堆内分配内存，分配的是动态内存,新的内存。)
	}
	for(int i=0;i<len;i++)
	{
		snake[i][0]=N/2;
		snake[i][1]=N/2+i;             //竖着放的初始蛇。 
		position(snake[i][0],snake[i][1]);
		cout<<"★"<<endl;
	}
	while(1)
	{
		tail[0]=snake[len-1][0];
		tail[1]=snake[len-1][1];
		position(tail[0],tail[1]);
		cout<<"  "<<endl;
		
		for(int i=len-1;i>0;i--)
		{
			snake[i][0]=snake[i-1][0];
			snake[i][1]=snake[i-1][1];
			position(snake[i][0],snake[i][1]);
			cout<<"★"<<endl;
			
		}
		if(kbhit())
		{
			position(0,N+2);
			q=getche();  //conio.h
			
		}
				
		switch(q)
				{
					case 'w': if(direction!='s')direction='w';break;  
					case 's': if(direction!='w')direction='s';break;
					case 'd': if(direction!='a')direction='d';break;
					case 'a': if(direction!='d')direction='a';break;
					default:break;
				}
				
	    switch(direction)
				{
					case 'w': if(direction!='s')snake[0][1]--;break;  //往上是递减坐标。 
					case 's': if(direction!='w')snake[0][1]++;break;
					case 'd': if(direction!='a')snake[0][0]++;break;
					case 'a': if(direction!='d')snake[0][0]--;break;
					default:break;
				}
				
		position(snake[0][0],snake[0][1]);
		cout<<"★"<<endl;
		Sleep(abs(200-0.5*score));
	
		
		if(snake[0][0]==food[0]&&snake[0][1]==food[1])
		{
			len++;
			score++;
			snake=(int**)realloc(snake,sizeof(int*)*len);
			snake[len-1]=(int*)malloc(sizeof(int)*2);
		
			food[0]=rand()%N+1; // rand() 0~无穷 +1->1到N 
			food[1]=rand()%N+1; 
			position(food[0],food[1]);
			cout<<"●"<<endl;
		
			position(N+5,3);
			cout<<score<<endl;
		}
		if(snake[0][0]==0||snake[0][0]==N||snake[0][1]==0||snake[0][1]==N)
		{
			position(N/2,N/2);
			cout<<"failure:空格重新开始"<<endl;
			for(int i=0;i<len;i++)
			free(snake[i]); //释放内存,结束游戏 			
			q=getche();
			if(q == ' ') 
			{
				system("Cls");
				main();
			}
			else 
			{			 
			  exit(0);
		    }
		}
	if(direction!='f')
		for(int i=1;i<len;i++)
		{
			xy=snake[i];
			if(snake[0][0]==xy[0]&&snake[0][1]==xy[1])
			{
				position(N/2,N/2);
				cout<<"failure:空格重新开始"<<endl;
				for(int i=0;i<len;i++)
				free(snake[i]); //释放内存,结束游戏 
				Sleep(30);			
				q=getche();
				if(q == ' ') 
				{
				system("Cls");
				main();
				}
				else 
				{			 
			       exit(0);
			    }
			}
			else continue;
		}
		
	}
	return 0;
}
	
	
	
