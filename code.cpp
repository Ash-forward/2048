#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

#define PROBABILITY 0.7  //生成 2 的概率

int Menu();
int save();
void rules();
void fun_issave();
void tips();
void refresh();
int keydown();
int game();
void up();
void down();
void left();
void right();
int new_num();
void load();
int check();

int arr_a[6][6] = {{-1,-1,-1,-1,-1,-1},

				   {-1, 0, 0, 0, 0, -1},
				   {-1, 0, 0, 0, 0, -1},
				   {-1, 0, 0, 0, 0, -1},
				   {-1, 0, 0, 0, 0, -1},
					{-1,-1,-1,-1,-1,-1}};

int main()
{
	Menu();
	system("pause");
	return 0;
}

int Menu()
{
	tips();
	int key = -1;
	int state = -1;
	int i,j;
	while(true)
	{
		scanf("%d",&key);
		switch(key)
		{
		case 1:
			rules();
			break;
		case 2:
			while(state = game());
			if(!state)
			{
				for(i = 1;i < 5;i++)
				{
					for(j = 1;j < 5;j++)
						arr_a[i][j] = 0;
				}
				return 0;
			}
			break;
		case 3:
			load();
			while(state = game());
			if(!state)
			{
				for(i = 1;i < 5;i++)
				{
					for(j = 1;j < 5;j++)
						arr_a[i][j] = 0;
				}
				return 0;
			}
			break;
		case 4:
			return 0;
			break;
		default:
			{
				printf("输入了非法选项，请重新输入!\n\n");
				system("pause");
				system("cls");
				tips();
			}
		}
	}


}

int game()
{
	system("cls");
	refresh();
	new_num();
	refresh();
	//return keydown();
	int isfail = check();
		if(isfail == 1)
		{
			return keydown();
		}
		else if(isfail == 0)
		{
			printf("你输了...还是不行吧!!!\n");
			system("pause");
			return 0;
		}
		else if(isfail == -1)
		{
			printf("你赢了,算你厉害...\n");
			system("pause");
			return 0;
		}

	
}

int check()
{
	int *p = NULL,*q = NULL;
	int i = 0,j = 0;

	for(i = 1;i < 5;i++)
	{
		for(j = 1;j < 5;j++)
		{
			if(arr_a[i][j] == 8192)
				return -1;
		}
	}

	for(i = 1; i < 5; i++)
	{
		for(j = 1; j < 5; j++)
		{
			if(arr_a[i][j] == 0)
				return 1;
		}
	}


	//遍历列
	for(j = 1; j < 5; j++)
	{
		p = q = &arr_a[1][j];
		while(1)
		{
			//查找是否有相同数字
			while(*p == 0)
			{
				p+=6;
			}
			q = p+6;

			if(*p == -1 || *q == -1)
				break;

			while(*q == 0)
			{
				q+=6;
			}
			
			if(*p == *q)
			{
				return 1;
			}
		
			p+=6;
			
		}

	}

	//遍历行
	for(j = 1; j < 5; j++)
	{
		p = q = &arr_a[j][1];
		while(1)
		{
			//合并
			while(*p == 0)
			{
				p++;
			}
			q = p + 1;

			if(*p == -1 || *q == -1)
				break;

			while(*q == 0)
			{
				q++;
			}
			
			if(*p == *q)
			{
				return 1;
			}
		
			p++;
			
		}
	}


	return 0;
}
int new_num()

{
	srand(time(NULL));
    double threshold = PROBABILITY;
    int random_number = 0;
	int x = 1, y = 1;
	int i,j;
	x = rand() % 4 + 1;
	y = rand() % 4 + 1;
	for(i = 1; i < 5; i++)
	{
		for(j = 1; j < 5; j++)
		{
			if(arr_a[i][j] == 0)
			{
				while(arr_a[x][y] != 0)
				{
					x = rand() % 4 + 1;
					y = rand() % 4 + 1;
				}
				while(arr_a[x][y] == 0)
				{
					arr_a[x][y] =  (rand() / (double)RAND_MAX) < threshold ? 2 : 4;
					return 0;
				}
			} 
		}
	}
	

}

void up()
{
	int *p = NULL,*q = NULL;
	int i = 0,j = 0;

	
	for(j = 1; j < 5; j++)
	{
		p = q = &arr_a[1][j];
		while(1)
		{
			//合并
			while(*p == 0 && *p != -1)
			{
				p+=6;
			}
			q = p+6;

			if(*p == -1 || *q == -1)
				break;

			while(*q == 0 && *q != -1)
			{
				q+=6;
			}
			
			if(*p == *q)
			{
				*p = 2 * (*p);
				*q = 0;
			}
		
			p+=6;
			
		}
		
		//移动
		
		for(i = 1; i < 5; i++)
		{
			p = &arr_a[i][j];
			while(*p != 0 && *p != -1)
			{
				p+=6;
			}

			q = p + 6;
			if(*p == -1 || *q == -1)
				break;

			while(*q == 0 && *q != -1)
			{
				q+=6;
			}

			if(*p == -1 || *q == -1)
				break;
			*p = *q;
			*q = 0;
			
		}
	}
}

void down()
{
	int *p = NULL,*q = NULL;
	int i = 0,j = 0;

	
	for(j = 1; j < 5; j++)
	{
		p = q = &arr_a[4][j];
		while(1)
		{
			//合并
			while(*p == 0)
			{
				p-=6;
			}
			q = p-6;

			if(*p == -1 || *q == -1)
				break;

			while(*q == 0)
			{
				q-=6;
			}
			
			if(*p == *q)
			{
				*p = 2 * (*p);
				*q = 0;
			}
		
			p-=6;
			
		}
		
		//移动
		
		for(i = 4; i > 0; i--)
		{
			p = q = &arr_a[i][j];
			while(*p != 0 && *p != -1)
			{
				p-=6;
			}

			if(*p == -1 || *q == -1)
				break;
			q = p - 6;
			
			while(*q == 0 && *q != -1)
			{
				q-=6;
			}

			if(*p == -1 || *q == -1)
				break;

			*p = *q;
			*q = 0;
			
		}
	}
}

void left()
{
	int *p = NULL,*q = NULL;
	int i = 0,j = 0;

	
	for(j = 1; j < 5; j++)
	{
		p = q = &arr_a[j][1];
		while(1)
		{
			//合并
			while(*p == 0 && *p !=-1)
			{
				p++;
			}
			q = p + 1;

			if(*p == -1 || *q == -1)
				break;

			while(*q == 0 && *q != -1)
			{
				q++;
			}
			
			if(*p == *q)
			{
				*p = 2 * (*p);
				*q = 0;
			}
		
			p++;
			
		}
		
		//移动
		
		for(i = 1; i < 5; i++)
		{
			p = &arr_a[j][i];
			while(*p != 0 && *p != -1)
			{
				p++;
			}

			q = p + 1;
			
			if(*p == -1 || *q == -1)
				break;

			while(*q == 0 && *q != -1)
			{
				q++;
			}

			if(*p == -1 || *q == -1)
				break;
			*p = *q;
			*q = 0;
			
		}
	}

}

void right()
{
	int *p = NULL,*q = NULL;
	int i = 0,j = 0;

	
	for(j = 1; j < 5; j++)
	{
		p = q = &arr_a[j][4];
		while(1)
		{
			//合并
			while(*p == 0 && *p != -1)
			{
				p--;
			}
			q = p - 1;

			if(*p == -1 || *q == -1)
				break;

			while(*q == 0 && *q != -1)
			{
				q--;
			}
			
			if(*p == *q)
			{
				*p = 2 * (*p);
				*q = 0;
			}
		
			p--;
			
		}
		
		//移动
		
		for(i = 4; i > 0; i--)
		{
			p = q= &arr_a[j][i];
			while(*p != 0 && *p != -1)
			{
				p--;
			}
			if(*p == -1 || *q == -1)
				break;

			q = p - 1;
			
			while(*q == 0 && *q != -1)
			{
				q--;
			}

			if(*p == -1 || *q == -1)
				break;
			*p = *q;
			*q = 0;
			
		}
	}

}

int keydown()		//按键检测
{
	printf("\n\n\n按 esc 键结束/暂停...\n");
	while(1)
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
		  fun_issave();
		  return 0;
		   //break;
        }
        else if (GetAsyncKeyState('W') & 0x8000) {
			up();
			refresh();
			if(!game())
				return 0;
			printf("\n\n\n按 esc 键结束/暂停...\n");
        }
        else if (GetAsyncKeyState('S') & 0x8000) {
			down();
			refresh();
			if(!game())
				return 0;
			printf("\n\n\n按 esc 键结束/暂停...\n");
        }
        else if (GetAsyncKeyState('A') & 0x8000) {
            left();
			refresh();
			if(!game())
				return 0;
			printf("\n\n\n按 esc 键结束/暂停...\n");
        }
        else if (GetAsyncKeyState('D') & 0x8000) {
            right();
			refresh();
			if(!game())
				return 0;
			printf("\n\n\n按 esc 键结束/暂停...\n");
        }
	
	
		Sleep(120);
	 }
	

	return 1;
}
void refresh()
{
	system("cls");
	char arr_b1[4][5] = {" ", " ", " ", " "};
	char arr_b2[4][5] = {" ", " ", " ", " "};
	char arr_b3[4][5] = {" ", " ", " ", " "};
	char arr_b4[4][5] = {" ", " ", " ", " "};
	char tmp[6];
	int i,j;

	for(i = 1,j=0; i < 5; i++,j++)
	{
		if(arr_a[1][i] !=0)
		{
			itoa(arr_a[1][i],tmp,10);
			strcpy(arr_b1[j],tmp);
		}
	}

	for(i = 1,j=0; i < 5; i++,j++)
	{
		if(arr_a[2][i] !=0)
		{
			itoa(arr_a[2][i],tmp,10);
			strcpy(arr_b2[j],tmp);
		}
	}

	for(i = 1,j=0; i < 5; i++,j++)
	{
		if(arr_a[3][i] !=0)
		{
			itoa(arr_a[3][i],tmp,10);
			strcpy(arr_b3[j],tmp);
		}
	}

	for(i = 1,j=0; i < 5; i++,j++)
	{
		if(arr_a[4][i] !=0)
		{
			itoa(arr_a[4][i],tmp,10);
			strcpy(arr_b4[j],tmp);
		}
	}
	printf("\n\n\t\t\t\t............................................\n");
	printf("\t\t\t\t.	  . 	     .	   	.          .\n");
	printf("\t\t\t\t.	  . 	     . 		.          .\n");
	printf("\t\t\t\t.  %4s   .   %4s   .   %4s   .   %4s   .\n",arr_b1[0] ,arr_b1[1],arr_b1[2],arr_b1[3]);
	printf("\t\t\t\t.	  . 	     .		.          .\n");
	printf("\t\t\t\t............................................\n");
	printf("\t\t\t\t.	  . 	     .	   	.          .\n");
	printf("\t\t\t\t.	  . 	     . 		.          .\n");
	printf("\t\t\t\t.  %4s   .   %4s   .   %4s   .   %4s   .\n",arr_b2[0],arr_b2[1],arr_b2[2],arr_b2[3]);
	printf("\t\t\t\t.	  . 	     .		.          .\n");
	printf("\t\t\t\t............................................\n");
	printf("\t\t\t\t.	  . 	     .	   	.          .\n");
	printf("\t\t\t\t.	  . 	     . 		.          .\n");
	printf("\t\t\t\t.  %4s   .   %4s   .   %4s   .   %4s   .\n",arr_b3[0],arr_b3[1],arr_b3[2],arr_b3[3]);
	printf("\t\t\t\t.	  . 	     .		.          .\n");
	printf("\t\t\t\t............................................\n");
	printf("\t\t\t\t.	  . 	     .	   	.          .\n");
	printf("\t\t\t\t.	  . 	     . 		.          .\n");
	printf("\t\t\t\t.  %4s   .   %4s   .   %4s   .   %4s   .\n",arr_b4[0],arr_b4[1],arr_b4[2],arr_b4[3]);
	printf("\t\t\t\t.	  . 	     .		.          .\n");
	printf("\t\t\t\t............................................\n");
}
int save()
{
	FILE *fp;
	int i,j;
	for(i = 0; i < 3; i++)
	{
		
		if((fp = fopen("data.dat","wb+")) == NULL)
		{

				printf("文件打开错误!");
				printf("关闭!");				
				fclose(fp);
				printf("正在重试...");
		}
		else
		{
			break;
		}
	}

	if(i == 3)
		return 0;

	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			fprintf(fp,"%d ",arr_a[i][j],1);
		}
	}
	fprintf(fp,"%s",'\0',1);
	fclose(fp);
	return 1;
}

void load()
{
	int i,j;
	FILE *fp = fopen("data.dat", "r");
    if (fp== NULL) {
        printf("你还没有存档记录！");
    } else {
		for(i = 0; i < 6;i++)
		{
			for(j = 0; j < 6; j++)
			{
				fscanf(fp,"%d",&arr_a[i][j],1);
			}
		}
        fclose(fp);
    }
}
void rules()
{
	char esc = 0;
	system("cls");
	printf("\n\n\t\t............................................................................\n");
	printf("\t\t.									   .\n");
	printf("\t\t. 1、本游戏通过按键 W S A D（不区分大小写）四个键分别控制滑块 上 下 左 右  .\n");
	printf("\t\t.									   .\n");
	printf("\t\t.									   .\n");
	printf("\t\t. 2、每次操作之后会在空白的方格处随机生成一个2或者4（生成2的概率要大一些） .\n");
	printf("\t\t.									   .\n");
	printf("\t\t.									   .\n");
	printf("\t\t. 3、最终得到一个“2048”的方块你就胜利了，敢来尝试吗？小趴菜 :)	   .\n");
	printf("\t\t.									   .\n");
	printf("\t\t............................................................................\n");

	
	printf("\n\n\n按 esc 键返回...\n");
	while(1)
	{
	 if (_kbhit() && _getch() == 27)
        {
		   system("cls");
           Menu();
		   //break;
        }
	 }

}

void fun_issave()
{
	int issave = -1;
	printf("是否保存当前进度:  -0- 不保存   -1- 保存\n");
			
			while(1)
			{
				scanf("%d",&issave);
				if(issave == 1 || issave == 0)
				{
					break;
				}else
				{
					printf("非法输入，请重新选择!\n");
				}
			}
			
			if(issave)
			{
				if(save())
				{
					printf("已保存!\n");
					system("pause");
					exit(0);
				}
			}
			else
			{
				printf("已退出!\n");
				system("pause");
				exit(0);
			}

}


void tips()
{
	printf("\n\n\t\t...................................................\n");
	printf("\t\t.						  .\n");
	printf("\t\t.    欢迎使用由 Mr. Chen 制作的2048休闲小游戏     . \n");
	printf("\t\t.						  .\n");
	printf("\t\t...................................................\n");
	printf("\t\t.  请输入：					  .\n");
	printf("\t\t.  		   -1-  游戏规则		  .\n");
	printf("\t\t.						  .\n");
	printf("\t\t.						  .\n");
	printf("\t\t.  		   -2-  开始游戏		  .\n");
	printf("\t\t.						  .\n");
	printf("\t\t.						  .\n");
	printf("\t\t.  		   -3-  继续游戏		  .\n");
	printf("\t\t.						  .\n");
	printf("\t\t.						  .\n");
	printf("\t\t.  		   -4-  退出游戏		  .\n");
	printf("\t\t.						  .\n");
	printf("\t\t.						  .\n");
	printf("\t\t...................................................\n\n\n\n");

}