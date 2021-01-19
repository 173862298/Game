/*
	使用工具：https://www.cnblogs.com/jiaoyu121/p/6965075.html    绘图工具EasyX的下载与介绍
	游戏：2048
	1、窗口  每行4个格子  宽度100  间隔15    不变的数据用什么表示？1宏定义2常量
*/
#include <stdio.h>
#include <conio.h>
#include <graphics.h>//包含图形库头文件
#define MAX_GRID 4 //每行格子数
#define GRID_WIDTH 100//格子宽度
#define INTERVAL 15//间隔
enum Color
{
	zero = RGB(205,193,180),//0的颜色
	twoTo1 = RGB(238,228,218),//2
	twoTo2 = RGB(237,224,200),//4
	twoTo3 = RGB(242,177,121),//8
	twoTo4 = RGB(245,149,99),//16
	twoTo5 = RGB(246,124,95),//32
	twoTo6 = RGB(246,94,59),//64
	twoTo7 = RGB(242,177,121),//128
	twoTo8 = RGB(237,204,97),//256
	twoTo9 = RGB(255,0,128),//512
	twoTo10 = RGB(145,0,72),//1024
	twoTo11 = RGB(242,17,158),//2048
	back=RGB(187,173,160)//背景颜色
};
Color arr[13] = { zero,twoTo1,twoTo2,twoTo3,twoTo4,twoTo5,twoTo6,twoTo7,twoTo8,twoTo9,twoTo10,twoTo11,back };
int num[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int map[MAX_GRID][MAX_GRID];//全局变量自动初始化为0
POINT pos[MAX_GRID][MAX_GRID];//保存每个格子左上角坐标
bool flag = false;

//定义函数，随机返回2或4
int TwoOrFour()
{
	if (rand() % 10 == 1)//十分之一的概率产生一个4
	{
		return 4;
	}
	else
	{
		return 2;
	}
}
//在数组的随机位置产生，把数字放到数组中
void CreateNumber()
{
	while (1)
	{
		int x = rand() % MAX_GRID;
		int y = rand() % MAX_GRID;
		if (map[x][y] == 0)
		{
			map[x][y] = TwoOrFour();
			break;
		}
		
	}
}
void GameInit()
{
	//设置随机数种子
	srand(GetTickCount());
	//计算格子坐标
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			pos[i][k].x = k*GRID_WIDTH + (k + 1)*INTERVAL;
			pos[i][k].y = i*GRID_WIDTH + (i + 1)*INTERVAL;
		}
	}
	//初始，随机生成两个
	CreateNumber();
	CreateNumber();	
}
void GameDraw()
{
	setbkcolor(back);//背景颜色
	cleardevice();//清除图形屏幕
		
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			for (int q = 0; q < 12; q++)
			{
				if (map[i][k] == num[q])
				{
					setfillcolor(arr[q]);
					solidrectangle(pos[i][k].x, pos[i][k].y, pos[i][k].x + GRID_WIDTH, pos[i][k].y + GRID_WIDTH);//无白边
					if (map[i][k] != 0)
					{
						char number[5] = "";
						settextcolor(RGB(119, 110, 101));
						settextstyle(50, 0, "楷体");
						setbkmode(TRANSPARENT);//设置背景颜色透明
						sprintf(number, "%d", num[q]);
						//用格子的一半减去字符串宽度的一半,设置居中
						int tempX = GRID_WIDTH / 2 - textwidth(number) / 2;//textwidth字符的宽度
						int tempY = GRID_WIDTH / 2 - textheight(number) / 2;						
						outtextxy(pos[i][k].x + tempX, pos[i][k].y + tempY, number);
					}
				}
			}
			
		}
	}
}
/*
1、开始两个变量，上： 移动，再相加
*/
void moveup()
{
	printf("up\n");
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_GRID; begin++)
		{
			if (map[begin][i] != 0)//一列一列的判断，不等于零时 移动
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
				}
				else
				{
					map[temp+1][i] = map[begin][i];
					if (temp + 1 != begin)
					{
						map[begin][i] = 0;
					}
				}
				temp++;
				flag = true;
			}
		}
	}
}
void GameJude()
{
	if (flag)
	{
		CreateNumber();
		flag = false;
	}
}

void movedown()
{
	printf("down\n");
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = MAX_GRID-1;
		for (int begin = MAX_GRID-2; begin >=0; begin--)
		{
			if (map[begin][i] != 0)//一列一列的判断，不等于零时 移动
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
				}
				else
				{
					map[temp - 1][i] = map[begin][i];
					if (temp - 1 != begin)
					{
						map[begin][i] = 0;
					}
				}
				temp-- ;
				flag = true;
			}
		}
	}
}
void moveleft()
{
	printf("left\n");
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_GRID; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
				}
				else
				{
					map[i][temp + 1] = map[i][begin];
					if (temp + 1 != begin)
					{
						map[i][begin] = 0;
					}
				}
				temp++;
				flag = true;
			}
		}
	}
}
void moveright()
{
	printf("right/n");
}
//键盘控制数字移动
void GameControl()
{
	//获取键盘输入，_getch()
	char key = _getch();
	switch (key)//上下左右
	{
	case 'w':		
	case 'W':		
	case 72:
		moveup();
		break;
	case 's':
	case 'S':
	case 80:
		movedown();
		break;
	case 'A':
	case 'a':
	case 75:
		moveleft();
		break;
	case 'd':
	case 'D':
	case 77:
		moveright();
		break;
	}
}
int main()
{
	//创建窗口
	initgraph(MAX_GRID*GRID_WIDTH + 5 * INTERVAL, MAX_GRID*GRID_WIDTH + 5 * INTERVAL,1);//检查键盘输入
	//initgraph(MAX_GRID*GRID_WIDTH + 5 * INTERVAL, MAX_GRID*GRID_WIDTH + 5 * INTERVAL);
	GameInit();
	while (1)
	{	
		GameDraw();
		GameControl();
		GameJude();
	}

	getchar();
	return 0;
}