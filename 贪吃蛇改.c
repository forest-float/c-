#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>
#include <conio.h> /*键盘输入获取*/
#define STOP   0
#define LEFT   1
#define RIGHT  2
#define UP     3
#define DOWN   4

int masterx[25] = {0},mastery[50] = {0};
int master_len = 3;
int weight = 25,height = 50;
int targetx,targety;
int Dir = UP;
int lastx,lasty;
int socres = 0;
int gameOver;

void menu(void);
void draw(void);
void master_init(void);
int logic(void);
void input_cmd(void);
void run(void);

int main(void)
{
	int chance = 1;
	while(1)
	{
		menu();
		printf("请选择：");
		scanf("%d",&chance);
		printf("你的选择是：%d\n",chance);
		getchar();
		system("cls");
		sleep(1);
		master_init();
		draw();
		//sleep(10);
		while(1)
		{
			run();
			if(!logic()) break;
			input_cmd();
			if(gameOver) return;
			system("cls");
			printf("得分：%d\n",socres);
			draw();			
			sleep(1);
		}
	}
	return 0;
}

void menu(void)
{
	system("cls");
	printf("----------------------------------------\n");
	printf("----------------1、开始-----------------\n");
	printf("----------------2、退出-----------------\n");
	printf("----------------------------------------\n");
}
void master_init(void)
{
	int i = 0;
	memset(masterx,0,sizeof(masterx));
	memset(mastery,0,sizeof(mastery));
	srand(time(NULL));
	targetx = rand()%weight;//随机生成一个目标地址
	targety = rand()%height;	
	for(i = 0; i < 3; i++)//给蛇定义一个初始化的位置
	{
		masterx[i] = weight/2 + i;
		mastery[i] = height/2 ;
		while(1)//防止出现蛇和食物在同一个位置
		{
			if(masterx[i] == targetx && mastery[i] == targety)
			{
				targetx = rand()%weight;//随机生成一个目标地址
				targety = rand()%height;	
			}
			else break;				
		}
	}	
}
void draw(void)
{
	int i= 0,j = 0,k = 0,flag = 0;		
	for(i = 0; i < 27; i++)//行
	{
		for(j = 0; j < 52; j++)//列
		{
			if(i == 0 || i == 26) printf("-");
			else if(j == 0 || j == 51) printf("|");
			else
			{
				flag = 0;
				for(k = 0; k < master_len;k++)
				{
					if(masterx[k] == i && mastery[k] == j) 
					{
						flag = 1;
						break;
					}
				}
				if(flag) printf("*");//蛇的身体
				else if(targetx == i && targety == j) printf("0");//食物
				else printf(" ");//空白
			}
		}
		printf("\n");
	}	
}
void input_cmd(void)
{
	int hit;
	if(_kbhit())
    {
        /*获取键盘的输入字符*/
        switch(_getch())
        {
            case '4':
            case 75:/*左键*/
                Dir = LEFT;                
                break;
            case '8':
            case 72:/*上键*/
                Dir = UP;               
                break;
            case '6':
            case 77:/*右键*/
                Dir = RIGHT;                
                break;
            case '2':
            case 80:/*向下键盘键 */
                Dir = DOWN;                
                break;
            case 'x':
            case 27:/*ESE*/
                gameOver = true;
                break;           
        }
    }
}
void run(void)
{
	int i = 0;
	lastx = masterx[master_len - 1];
	lasty = mastery[master_len - 1];
	for(i = master_len - 1; i > 0; i--)
	{
		masterx[i] = masterx[i-1];
		mastery[i] = mastery[i-1];
	}
	switch(Dir)
	{
		case LEFT: 			
			masterx[0] = masterx[1];
			mastery[0] = mastery[1]-1;
			break;
		case RIGHT:
			masterx[0] = masterx[1];
			mastery[0] = mastery[1]+1;
			break;
		case UP: 
			masterx[0] = masterx[1]-1;
			mastery[0] = mastery[1];
			break;
		case DOWN: 
			masterx[0] = masterx[1]+1;
			mastery[0] = mastery[1];
			break;
	}	
}
int logic(void)
{
	if(masterx[0] == 0 || masterx[0] == 26 || mastery[0] == 0 || mastery[0] == 51)
	{
		return 0;//游戏结束
	}
	if(masterx[0] == targetx && mastery[0] == targety)//吃到食物
	{
		master_len += 1;
		masterx[master_len - 1] = lastx ;//保留的上一次的最后一个位置，因为吃到食物要增加一个长度的元素
		mastery[master_len - 1] = lasty;
		socres++;
		return 1;
	}
	return 2;
}

