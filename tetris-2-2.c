#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define HEIGHT 21
#define WIDTH 12
#define BLOCK_SIZE 4
#define VARIETY 7

#define color(col) printf("\x1b[%dm",col)
#define color_set printf("\x1b[m")

int stage[HEIGHT][WIDTH]={0};
int block[BLOCK_SIZE][BLOCK_SIZE]={0};
int nextblock[BLOCK_SIZE][BLOCK_SIZE]={0};
int holdblock[BLOCK_SIZE][BLOCK_SIZE]={0};
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
int block_type,colortype,colortype_next,colortype_hold1,colortype_hold2,colortype_stage=37;
int oneline,twoline,threeline,fourline;
int score,level;
int gameover=0;
int h1=0;
int h2=0;

void tutorial();
void Initialize();
int CreateBlock();
void ShowGameField();
void ControlBlock();
int  CheckOverlap(int, int);
void MoveBlock(int, int);
int TurnBlock();
void HoldBlock();
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
		printf("\n\n##########\n\nGAME OVER\n\n##########\n\n\nYOUR SCORE :　%d\nYOUR LEVEL : %d\n\n\n\n\n\n",score,level);
		
		
		printf("コンティニューしますか？\nコンティニューする場合はyしない場合はnを押してください\n");
		insertcoin=getch();
		
		while(insertcoin != 'y' && insertcoin!= 'n')
		{
			printf("yかnを押してください(押されたキー: %c)\n",insertcoin);
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
	
	system("cls");
	printf("テトリス\n\n");
	printf("操作方法\n→ 右へ移動\n← 左へ移動\n↓ 加速\nスペース 回転\n\n");
	printf("加速 5点\nブロック生成 10点\nsingle 100点\ndouble 300点\ntoriple 600点\ntetris 1000点\n\n");
	printf("SCORE500ごとにLEVELが1あがり速度が上がります");
	printf("SPACEを押すと開始します");
	
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
	h1=0;
	for(i=0;i<HEIGHT;i++)
	{
		for(j=0;j<WIDTH;j++)
		{
			holdblock[i][j]=0;
		}
	}
	
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
	
	block_type=rand()%7;
	
	if(block_type==0)
	{
		colortype_next=36;
	}
	else if(block_type==1)
	{
		colortype_next=37;
	}
	else if(block_type==2)
	{
		colortype_next=32;
	}
	else if(block_type==3)
	{
		colortype_next=31;
	}
	else if(block_type==4)
	{
		colortype_next=34;
	}
	else if(block_type==5)
	{
		colortype_next=33;
	}
	else if(block_type==6)
	{
		colortype_next=35;
	}

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

	y=0;
	x=4;

	for(i=0;i<BLOCK_SIZE;i++)
	{
		for(j=0;j<BLOCK_SIZE;j++)
		{
			colortype=colortype_next;
			block[i][j]=0;
			block[i][j]=nextblock[i][j];
		}
	}
	score=score+10;
	NextBlock();
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
			if(i==0)
			{
				printf("                 ");
			}
			if(i==1)
			{
				printf("                 ");
			}
			if(i==2)
			{
				printf("                 ");
			}
			if(i==3)
			{
				printf("  □□□□□□   ");
			}
			if(i==4)
			{
				printf("  □");
				for(k=0;k<4;k++)
				{
					if(holdblock[0][k]==0)
					{
						printf("　");
					}
					else
				{
					color(colortype_hold1);
					color(1);
					printf("■");
					color_set;
					color_set;
				}
				}
				printf("□   ");
			}
			if(i==5)
			{
				printf("  □");
				for(k=0;k<4;k++)
				{
					if(holdblock[1][k]==0)
					{
						printf("　");
					}
					else
				{
					color(colortype_hold1);
					color(1);
					printf("■");
					color_set;
					color_set;
				}
				}
				printf("□   ");
			}
			if(i==6)
			{
				printf("  □");
				for(k=0;k<4;k++)
				{
					if(holdblock[2][k]==0)
					{
						printf("　");
					}
					else
				{
					color(colortype_hold1);
					color(1);
					printf("■");
					color_set;
					color_set;
				}
				}
				printf("□   ");
			}
			if(i==7)
			{
				printf("  □");
				for(k=0;k<4;k++)
				{
					if(holdblock[3][k]==0)
					{
						printf("　");
					}
					else
				{
					color(colortype_hold1);
					color(1);
					printf("■");
					color_set;
					color_set;
				}
				}
				printf("□   ");
			}
			if(i==8)
			{
				printf("  □□□□□□   ");
			}
			if(i==9)
			{
				printf("                 ");
			}
			if(i==10)
			{
				printf("                 ");
			}
			if(i==11)
			{
				printf("                 ");
			}
			if(i==12)
			{
				printf("                 ");
			}
			if(i==13)
			{
				printf("                 ");
			}
			if(i==14)
			{
				printf("                 ");
			}
			if(i==15)
			{
				printf("                 ");
			}
			if(i==16)
			{
				printf("                 ");
			}
			if(i==17)
			{
				printf("                 ");
			}
			if(i==18)
			{
				printf("                 ");
			}
			if(i==19)
			{
				printf("                 ");
			}
			if(i==20)
			{
				printf("                 ");
			}
			if(i==21)
			{
				printf("                 ");
			}
		for(j=0;j<WIDTH;j++)
		{
			if(field[i][j]==0)
			{
				printf("　");
			}
			else if(field[i][j]==9)
			{
				printf("□");
			}
			else if(stage[i][j]>0)
			{
				color(colortype_stage);
				printf("■");
				color_set;
				color_set;
			}
			else
			{
				color(colortype);
				color(1);
				printf("■");
				color_set;
				color_set;
			}
		}
		if(i==3){
			printf("　　　□□□□□□");
		}
		if(i==4){
			printf("　　　□");
			for(k=0;k<BLOCK_SIZE;k++)
			{
				if(nextblock[0][k]==0)
				{
					printf("　");
				}
				else
				{
					color(colortype_next);
					color(1);
					printf("■");
					color_set;
					color_set;
				}
			}
			printf("□");
		}
		if(i==5)
		{
			printf("　　　□");
			for(k=0;k<BLOCK_SIZE;k++)
			{
				if(nextblock[1][k]==0)
				{
					printf("　");
				}
				else
				{
					color(colortype_next);
					color(1);
					printf("■");
					color_set;
					color_set;
				}
			}
			printf("□");
		}
		if(i==6)
		{
			printf("　　　□");
			for(k=0;k<BLOCK_SIZE;k++)
			{
				if(nextblock[2][k]==0)
				{
					printf("　");
				}
				else
				{
					color(colortype_next);
					color(1);
					printf("■");
					color_set;
					color_set;
				}
			}
			printf("□");
		}
		if(i==7)
		{
			printf("　　　□");
			for(k=0;k<BLOCK_SIZE;k++)
			{
				if(nextblock[3][k]==0)
				{
					printf("　");
				}
				else
				{
					color(colortype_next);
					color(1);
					printf("■");
					color_set;
					color_set;
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
			printf("　　　□□□□□□　　□□□□□□");
		}
		if(i==14)
		{
			printf("　　　　 SCORE　　　　　 LEVEL");
		}
		if(i==15)
		{
			printf("　　　　　 %d　　　　　　　 %d",score,level);
		}
		if(i==16)
		{
			printf("　　　□□□□□□　　□□□□□□");
		}
		printf("\n");
	}
	printf("\nsingle：%d　double：%d　triple：%d　tetris：%d\n",oneline,twoline,threeline,fourline);
	
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
	else if(key=='h')
	{
		HoldBlock();
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

void HoldBlock()
{
	int i,j;
	int spareblock[BLOCK_SIZE][BLOCK_SIZE];
	if(!CheckOverlap(x,y)){
		if(h1==0 && h2==0)
		{
			for(i=0;i<BLOCK_SIZE;i++)
			{
				for(j=0;j<BLOCK_SIZE;j++)
				{
					holdblock[i][j]=block[i][j];
				}
			}
			for(i=0;i<BLOCK_SIZE;i++)
			{
				for(j=0;j<BLOCK_SIZE;j++)
				{
					field[y+i][x+j]=field[y+i][x+j]-holdblock[i][j];
				}
			}
		
			for(i=0;i<BLOCK_SIZE;i++)
			{
				for(j=0;j<BLOCK_SIZE;j++)
				{
					block[i][j]=0;
				}
			}
			colortype_hold1=colortype;
			CreateBlock();
			ShowGameField();
			h1=1;
			h2=1;
		}
		else if(h1==1 && h2==0)
		{
			for(i=0;i<BLOCK_SIZE;i++)
			{
				for(j=0;j<BLOCK_SIZE;j++)
				{
					field[y+i][x+j]=field[y+i][x+j]-block[i][j];
				}
			}
			for(i=0;i<BLOCK_SIZE;i++)
			{
				for(j=0;j<BLOCK_SIZE;j++)
				{
					spareblock[i][j]=block[i][j];
				}
			}
			for(i=0;i<BLOCK_SIZE;i++)
			{
				for(j=0;j<BLOCK_SIZE;j++)
				{
					block[i][j]=holdblock[i][j];
				}
			}
			for(i=0;i<BLOCK_SIZE;i++)
			{
				for(j=0;j<BLOCK_SIZE;j++)
				{
					holdblock[i][j]=spareblock[i][j];
				}
			}
			for(i=0;i<BLOCK_SIZE;i++)
			{
				for(j=0;j<BLOCK_SIZE;j++)
				{
					x=4,y=0;
					field[y+i][x+j]=field[y+i][x+j]+block[i][j];
				}
			}
			h2=1;
			colortype_hold2=colortype_hold1;
			colortype_hold1=colortype;
			colortype=colortype_hold2;
			ShowGameField();

		}
	}
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
			stage[i][j]=field[i][j];
		}
	}
	h2=0;
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
