// snake
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#define N 21
#include<iostream>
using namespace std;

void position(int x,int y)  //λ�ú������ѹ��λ�ý�����׼�� (windows.h)
{
	COORD a;
	a.X=2*x;
	a.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
}
void window(int food[2])   //���ڳ�ʼ���� 
{
	int i,j;
	int wall[N+2][N+2]={{0}};
	for(int i=1;i<=N;i++)    //ǽ�ڣ���һ�к����һ�У���һ�к����һ�С� (0��N+1)
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
			else cout<<"��" ;
		}
		cout<<endl;   //����Ҫ 
	}
	
	position(N+3,1);
	cout<<"�� W S A D �ƶ�����"<<endl;
	position(N+3,2);
	cout<<"��q����ͣ,���������"<<endl;
	position(N+3,3);
	cout<<"����:"<<endl;

	
	food[0]=rand()%N+1; // rand() 0~���� +1->1��N 
	food[1]=rand()%N+1; 
	position(food[0],food[1]);
	cout<<"��"<<endl; 
}



int main()
{
	int i=0,j=0;
	int **snake=NULL;
	int score=0;
	int food[2];
	char direction='f'; //���������ߵ�ǰ������ 
	int tail[2];
	int len=3;
	char q='o';
	int *xy;
	srand((unsigned)time(NULL));   //time.h
	window(food);

	snake=(int**)realloc(snake,sizeof(int*)*len); //�޸��ѷ�����ڴ档 
	for(i=0;i<len;i++)
	{
	snake[i]=(int*)malloc(sizeof(int)*2);//���������ڴ�   (�Ӷ��ڷ����ڴ棬������Ƕ�̬�ڴ�,�µ��ڴ档)
	}
	for(int i=0;i<len;i++)
	{
		snake[i][0]=N/2;
		snake[i][1]=N/2+i;             //���ŷŵĳ�ʼ�ߡ� 
		position(snake[i][0],snake[i][1]);
		cout<<"��"<<endl;
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
			cout<<"��"<<endl;
			
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
					case 'w': if(direction!='s')snake[0][1]--;break;  //�����ǵݼ����ꡣ 
					case 's': if(direction!='w')snake[0][1]++;break;
					case 'd': if(direction!='a')snake[0][0]++;break;
					case 'a': if(direction!='d')snake[0][0]--;break;
					default:break;
				}
				
		position(snake[0][0],snake[0][1]);
		cout<<"��"<<endl;
		Sleep(abs(200-0.5*score));
	
		
		if(snake[0][0]==food[0]&&snake[0][1]==food[1])
		{
			len++;
			score++;
			snake=(int**)realloc(snake,sizeof(int*)*len);
			snake[len-1]=(int*)malloc(sizeof(int)*2);
		
			food[0]=rand()%N+1; // rand() 0~���� +1->1��N 
			food[1]=rand()%N+1; 
			position(food[0],food[1]);
			cout<<"��"<<endl;
		
			position(N+5,3);
			cout<<score<<endl;
		}
		if(snake[0][0]==0||snake[0][0]==N||snake[0][1]==0||snake[0][1]==N)
		{
			position(N/2,N/2);
			cout<<"failure:�ո����¿�ʼ"<<endl;
			for(int i=0;i<len;i++)
			free(snake[i]); //�ͷ��ڴ�,������Ϸ 			
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
				cout<<"failure:�ո����¿�ʼ"<<endl;
				for(int i=0;i<len;i++)
				free(snake[i]); //�ͷ��ڴ�,������Ϸ 
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
	
	
	
