#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define HEIGHT 21
#define WIDTH 12
#define BLOCK_SIZE 4
#define VARIETY 7

int stage[HEIGHT][WIDTH]={0};
int block[BLOCK_SIZE][BLOCK_SIZE]={0};
int nextblock[BLOCK_SIZE][BLOCK_SIZE]={0};
int field[HEIGHT][WIDTH]={0};

int block_list[VARIETY][BLOCK_SIZE][BLOCK_SIZE]=
{{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
{{0,0,0,0},{0,1,1,0},{0,1,0,0},{0,1,0,0}},
{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
{{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},
{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
{{0,0,0,0},{0,1,1,0},{0,0,1,0},{0,0,1,0}}};

int x=4,y=0;
int oneline,twoline,threeline,fourline;
int score,level;
int gameover=0;

void tutorial();
void Initialize();
int CreateBlock();
void ShowGameField();
void ControlBlock();
int  CheckOverlap(int, int);
void MoveBlock(int, int);
int TurnBlock();
void DropBlock();
void LockBlock();
void CheckLines();
void NextBlock();

int main()
{
	int timecount=0,speed;
	
	char insertcoin='y';
	
	srand((unsigned)time(NULL));
	
	tutorial();
	
	setvbuf(stdout,NULL,_IOFBF,512);
	
	while(insertcoin=='y')
	{
		Initialize();
		while(gameover==0)
		{
			if(level<=10)
			{
				speed=10000-level*500;
			}
			else
			{
				speed=5000-level*100;
			}
			
			if(kbhit())
			{
				ControlBlock();
			}
			else if(timecount<speed)
			{
				timecount++;
			}
			else
			{
				DropBlock();
				timecount=0;
			}
		}
		
		setvbuf(stdout,NULL,_IONBF,512);
		
		system("cls");
		printf("\n\n##########\n\nGAME OVER\n\n##########\n\n\nYOUR SCORE :�@%d\nYOUR LEVEL : %d\n\n\n\n\n\n",score,level);
		
		
		printf("�R���e�B�j���[���܂����H\n�R���e�B�j���[����ꍇ��y���Ȃ��ꍇ��n�������Ă�������\n");
		insertcoin=getch();
		
		while(insertcoin != 'y' && insertcoin!= 'n')
		{
			printf("y��n�������Ă�������(�����ꂽ�L�[: %c)\n",insertcoin);
			insertcoin=getch();
		}
		if(insertcoin=='y')
		{
			setvbuf(stdout,NULL,_IOFBF,512);
			gameover=0;
		}
		
	}
	return 0;
}

void tutorial()
{	
	int key;
	
	printf("�e�g���X\n\n");
	printf("������@\n�� �E�ֈړ�\n�� ���ֈړ�\n�� ����\n�X�y�[�X ��]\n\n");
	printf("���� 5�_\n�u���b�N���� 10�_\nsingle 100�_\ndouble 300�_\ntoriple 600�_\ntetris 1000�_\n\n");
	printf("SCORE500���Ƃ�LEVEL��1�����葬�x���オ��܂�");
	printf("SPACE�������ƊJ�n���܂�");
	
	while(1)
	{
		key=_getch();
		if(key==224)
		{
			key=_getch();
		}
		if(key==32)
		{
			system("cls");
			break;
		}
	}
}	

void Initialize()
{
	int i,j;
	oneline=0;
	twoline=0;
	threeline=0;
	fourline=0;
	score=0;
	level=1;
	
	for(i=0;i<HEIGHT;i++)
	{
		for(j=0;j<WIDTH;j++)
		{
			if((j==0)||(j==WIDTH-1)||(i==HEIGHT-1))
			{
				field[i][j]=stage[i][j]=9;
			}
			else
			{
				field[i][j]=stage[i][j]=0;
			}
		}
	}
	NextBlock();
	CreateBlock();
	ShowGameField();
}

void NextBlock()
{
	int i,j;
	int block_type;
	
	block_type=rand()%7;

	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			nextblock[i][j]=block_list[block_type][i][j];
		}
	}
}

int CreateBlock()
{
	int i,j;
	int block_type;

	y=0;
	x=4;

	srand((unsigned)time(NULL));
	block_type=rand()%7;

	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			block[i][j]=0;
			block[i][j]=nextblock[i][j];
		}
	}
	score=score+10;
	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			nextblock[i][j]=block_list[block_type][i][j];
		}
	}
	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			field[i][j+4]=stage[i][j+4]+block[i][j];
			if(field[i][j+4]>1)
			{
				gameover=1;
				return 1;
			}
		}
	}
	return 0;
}

void ShowGameField()
{
	int i,j,k;
	
	system("cls");
	for(i=0;i<HEIGHT;i++)
	{
		for(j=0;j<WIDTH;j++)
		{
			if(field[i][j]==0)
			{
				printf("�@");
			}
			else if(field[i][j]==9)
			{
				printf("��");
			}
			else
			{
				printf("��");
			}
		}
		if(i==3){
			printf("�@�@�@������������");
		}
		if(i==4){
			printf("�@�@�@��");
			for(k=0;k<BLOCK_SIZE;k++)
			{
				if(nextblock[0][k]==0)
				{
					printf("�@");
				}
				else
				{
					printf("��");
				}
			}
			printf("��");
		}
		if(i==5)
		{
			printf("�@�@�@��");
			for(k=0;k<BLOCK_SIZE;k++)
			{
				if(nextblock[1][k]==0)
				{
					printf("�@");
				}
				else
				{
					printf("��");
				}
			}
			printf("��");
		}
		if(i==6)
		{
			printf("�@�@�@��");
			for(k=0;k<BLOCK_SIZE;k++)
			{
				if(nextblock[2][k]==0)
				{
					printf("�@");
				}
				else
				{
					printf("��");
				}
			}
			printf("��");
		}
		if(i==7)
		{
			printf("�@�@�@��");
			for(k=0;k<BLOCK_SIZE;k++)
			{
				if(nextblock[3][k]==0)
				{
					printf("�@");
				}
				else
				{
					printf("��");
				}
			}
			printf("��");
		}
		if(i==8)
		{
			printf("�@�@�@������������");
		}
		if(i==13)
		{
			printf("�@�@�@�������������@�@������������");
		}
		if(i==14)
		{
			printf("�@�@�@�@ SCORE�@�@�@�@�@ LEVEL");
		}
		if(i==15)
		{
			printf("�@�@�@�@�@ %d�@�@�@�@�@�@�@ %d",score,level);
		}
		if(i==16)
		{
			printf("�@�@�@�������������@�@������������");
		}
		printf("\n");
	}
	printf("\nsingle�F%d�@double�F%d�@triple�F%d�@tetris�F%d\n",oneline,twoline,threeline,fourline);
	
	fflush(stdout);
}

void ControlBlock()
{
	int key;

	key=_getch();
	if(key==224)
	{
		key=_getch();
	}
	if(key==77)
	{
		if(!CheckOverlap(x+1,y))
		{
			MoveBlock(x+1,y);
		}
	}
	else if(key==75)
	{
		if(!CheckOverlap(x-1,y))
		{
			MoveBlock(x-1,y);
		}
	}
	else if(key==80)
	{
		DropBlock();
		score=score+5;
	}
	else if(key==32)
	{
		TurnBlock();
	}
}

int CheckOverlap(int x2,int y2)
{
	int i,j;

	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			if(block[i][j]!=0)
			{
				if(stage[y2+i][x2+j]!=0)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

void MoveBlock(int x2, int y2)
{
	int i,j;
	
	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			field[y+i][x+j]=field[y+i][x+j]-block[i][j];
		}
	}
	x=x2;
	y=y2;
	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			field[y+i][x+j]=field[y+i][x+j]+block[i][j];
		}
	}
	ShowGameField();
}

int TurnBlock()
{
	int i,j;
	int temp[BLOCK_SIZE][BLOCK_SIZE]={0};
	
	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			temp[i][j]=block[i][j];
		}
	} 
	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			block[i][j]=temp[3-j][i];
		}
	}
	if(CheckOverlap(x,y))
	{
		for(i=0;i<BLOCK_SIZE;i++)
		{
			for(j=0;j<BLOCK_SIZE;j++)
			{
				block[i][j]=temp[i][j];
			}
		}
		return 1;
	}
	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			field[y+i][x+j]=field[y+i][x+j]-temp[i][j];
			field[y+i][x+j]=field[y+i][x+j]+block[i][j];
		}
	}
	ShowGameField();
	
	return 0;
}

void DropBlock()
{
	if(!CheckOverlap(x,y+1))
	{
		MoveBlock(x,y+1);
	}
	else
	{
		LockBlock();
		CreateBlock();
		ShowGameField();
	}
}

void LockBlock()
{
	int i,j;
	
	for(i=0;i<HEIGHT;i++)
	{
		for(j=0;j<WIDTH;j++)
		{
			stage[i][j]=field[i][j];
		}
	}
	CheckLines();
	for(i=0;i<HEIGHT;i++)
	{
		for(j=0;j<WIDTH;j++)
		{
			field[i][j]=stage[i][j];
		}
	}
}

void CheckLines()
{
	int i,j,k;
	int comp;
	int lines=0;
	
	for(i=0;i<HEIGHT-1;i++)
	{
		comp=1;
		for(j=1;j<WIDTH-1;j++)
		{
			if(stage[i][j]==0)
			{
				comp=0;
			}
		}
		if(comp==1)
		{
			lines++;
			for(j=1;j<WIDTH-1;j++)
			{
				stage[i][j]=0;
			}
			for(k=i;k>0;k--)
			{
				for(j=1;j<WIDTH-1;j++)
				{
					stage[k][j]=stage[k-1][j];
				}
			}
		}	
	}
	if(lines==1)
	{
		oneline++;
		score=score+100;
	}
	else if(lines==2)
	{
		twoline++;
		score=score+300;
	}
	else if(lines==3)
	{
		threeline++;
		score=score+600;
	}
	else if(lines==4)
	{
		fourline++;
		score=score+1000;
	}
	level=score/500+1;
}
