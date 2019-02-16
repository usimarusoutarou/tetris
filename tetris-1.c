#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int stage[21][12]={0};
int block[4][4]={0};
int nextblock[4][4]={0};
int field[21][12]={0};

int block_list[7][4][4]=
{{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
{{0,0,0,0},{0,1,1,0},{0,1,0,0},{0,1,0,0}},
{{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
{{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
{{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},
{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
{{0,0,0,0},{0,1,1,0},{0,0,1,0},{0,0,1,0}}};

int y=0;
int x=4;
int oneline,twoline,threeline,fourline;
int gameover=0;

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
	int time=0;
	char insertcoin='y';
	
	while(insertcoin=='y')
	{
		Initialize();
		while(gameover==0)
		{
			if(kbhit())
			{
				ControlBlock();
			}
			else
			{
				Sleep(1000);
				DropBlock();
			}
		}
		system("cls");
		printf("\n\n##########\n\nGAME OVER\n\n##########\n\nYOUR SCORE :　　%d\n\n\n\n\n\n\n\n\n\n\n\n",oneline*100 + twoline*300 + threeline*700 + fourline*1500);
		
		
		printf("コンティニューしますか？\nコンティニューする場合はyしない場合はnを押してください\n");
		insertcoin=getch();
		
		while(insertcoin != 'y' && insertcoin!= 'n')
		{
			printf("yかnを押してください(押されたキー: %c)\n",insertcoin);
			insertcoin=getch();
		}
		if(insertcoin=='y')
		{
			gameover=0;
		}
		
	}
	return 0;
}

void Initialize()
{
	int i,j;
	oneline=0;
	twoline=0;
	threeline=0;
	fourline=0;
	
	for(i=0;i<=20;i++)
	{
		for(j=0;j<=11;j++)
		{
			if((j==0)||(j==11)||(i==20))
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

	srand((unsigned)time(NULL));
	block_type=rand()%7;

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
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

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			block[i][j]=0;
			block[i][j]=nextblock[i][j];
		}
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			nextblock[i][j]=block_list[block_type][i][j];
		}
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
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
	for(i=0;i<21;i++)
	{
		for(j=0;j<12;j++)
		{
			if(field[i][j]==0)
			{
				printf("　");
			}
			else if(field[i][j]==9)
			{
				printf("□");
			}
			else
			{
				printf("■");
			}
		}
		if(i==3){
			printf("　　　□□□□□□");
		}
		if(i==4){
			printf("　　　□");
			for(k=0;k<4;k++)
			{
				if(nextblock[0][k]==0)
				{
					printf("　");
				}
				else
				{
					printf("■");
				}
			}
			printf("□");
		}
		if(i==5)
		{
			printf("　　　□");
			for(k=0;k<4;k++)
			{
				if(nextblock[1][k]==0)
				{
					printf("　");
				}
				else
				{
					printf("■");
				}
			}
			printf("□");
		}
		if(i==6)
		{
			printf("　　　□");
			for(k=0;k<4;k++)
			{
				if(nextblock[2][k]==0)
				{
					printf("　");
				}
				else
				{
					printf("■");
				}
			}
			printf("□");
		}
		if(i==7)
		{
			printf("　　　□");
			for(k=0;k<4;k++)
			{
				if(nextblock[3][k]==0)
				{
					printf("　");
				}
				else
				{
					printf("■");
				}
			}
			printf("□");
		}
		if(i==8)
		{
			printf("　　　□□□□□□");
		}
		if(i==13)
		{
			printf("　　　□□□□□□");
		}
		if(i==14)
		{
			printf("　　　　 SCORE");
		}
		if(i==15)
		{
			printf("　　　　　%d",oneline*100+twoline*300+threeline*500+fourline*700);
		}
		if(i==16)
		{
			printf("　　　□□□□□□");
		}
		printf("\n");
	}
	printf("\n１行消し：%d回　２行消し：%d回　３行消し：%d回　４行消し：%d回\n",oneline,twoline,threeline,fourline);
}

void ControlBlock()
{
	char key;

	key=getch();

	if(key=='l')
	{
		if(!CheckOverlap(x+1,y))
		{
			MoveBlock(x+1,y);
		}
	}
	else if(key=='j')
	{
		if(!CheckOverlap(x-1,y))
		{
			MoveBlock(x-1,y);
		}
	}
	else if(key=='k')
	{
		if(!CheckOverlap(x,y+1))
		{
			MoveBlock(x,y+1);
		}
	}
	else if(key==' ')
	{
		TurnBlock();
	}
}

int CheckOverlap(int x2,int y2)
{
	int i,j;

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
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
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			field[y+i][x+j]=field[y+i][x+j]-block[i][j];
		}
	}
	x=x2;
	y=y2;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			field[y+i][x+j]=field[y+i][x+j]+block[i][j];
		}
	}
	ShowGameField();
}

int TurnBlock()
{
	int i,j;
	int temp[4][4]={0};
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			temp[i][j]=block[i][j];
		}
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			block[i][j]=temp[3-j][i];
		}
	}
	if(CheckOverlap(x,y))
	{
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				block[i][j]=temp[i][j];
			}
		}
		return 1;
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
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
	
	for(i=0;i<21;i++)
	{
		for(j=0;j<12;j++)
		{
			stage[i][j]=field[i][j];
		}
	}
	CheckLines();
	for(i=0;i<21;i++)
	{
		for(j=0;j<12;j++)
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
	
	for(i=0;i<20;i++)
	{
		comp=1;
		for(j=1;j<11;j++)
		{
			if(stage[i][j]==0)
			{
				comp=0;
			}
		}
		if(comp==1)
		{
			lines++;
			for(j=1;j<11;j++)
			{
				stage[i][j]=0;
			}
			for(k=i;k>0;k--)
			{
				for(j=1;j<11;j++)
				{
					stage[k][j]=stage[k-1][j];
				}
			}
		}	
	}
	if(lines==1)
	{
		oneline++;
	}
	else if(lines==2)
	{
		twoline++;
	}
	else if(lines==3)
	{
		threeline++;
	}
	else if(lines==4)
	{
		fourline++;
	}
}
