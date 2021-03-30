#include <iostream>
#include <stdio.h> 

/* 
1. 데이터 입력 ------------------------------------------------OK
2. R기준으로 움직일 수 있는 방향 탐색
  2.1 한 방향씩 #나올때 까지 탐색(B도 함께 움직임)-------------OK 
  2.2 O와 만나면 종료하고 결과 저장 
  2.3 B가 O와 먼저 만나면 -1
3. 움직인 횟수 10회 넘어가면 -1  
3. 모든 경우의 수 중 가장 작은 값 출력 */

#define MAX 10

//typedef struct{
//	int row;
//	int col;
//}ballPos_t;

typedef enum{
	up=0,
	right,
	down,
	left,
	Ndir
}direction_e;

int N,M;

//init position
char initBoard[MAX][MAX];
int initRed[2]={0,};
int initBlue[2];

//game board
char board[MAX][MAX];
int redBall[10][2];
int blueBall[10][2];

int minCnt=11;

int oneMoving(int *HorPos,int *VerPos,int way,char color);
void debug_printBoard(void);



void initPosition()
{	
	scanf("%d %d",&N, &M);
	
	for(int i=0;i<N;i++)
	{
		scanf("%s",&initBoard[i]);
		
		for(int j=0;j<M;j++)
		{
			board[i][j] = initBoard[i][j];
			
			if(initBoard[i][j]=='R')
			{
				initRed[0] = i;
				initRed[1] = j;
			}		
			
			if(initBoard[i][j]=='B')
			{
				initBlue[0] = i;
				initBlue[1] = j;
			}
		}
	}
			printf("RED :: row/%d,col/%d === char : %c\n",initRed[0],initRed[1],board[initRed[0]][initRed[1]]);
			printf("BLUE :: row/%d,col/%d === char : %c\n",initBlue[0],initBlue[1],board[initBlue[0]][initBlue[1]]);

	for(int i=0;i<2;i++)
	{
		redBall[0][i] = initRed[i];
		blueBall[0][i] = initBlue[i];		
	}	
	
//			
//			if(board[i][j]=='O')
//			{
//				Hole[0] = i;
//				Hole[1] = j;
//			}
//		}
//	}
}

void setBoard(int depth)
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
			board[i][j] = initBoard[i][j];
	}	

	board[initRed[0]][initRed[1]] = '.';
	board[redBall[depth][0]][redBall[depth][1]] = 'R';
	
	board[initBlue[0]][initBlue[1]] = '.';
	board[blueBall[depth][0]][blueBall[depth][1]] = 'B';	
	
}


void moveBall(int cnt,int depth)
{
	int redRes,blueRes;
	//int redPos[2],bluePos[2];
	if(depth >= 9)
		return;
			
	for(int i=0;i<2;i++)
	{
		redBall[depth+1][i] = redBall[depth][i];
		blueBall[depth+1][i] = blueBall[depth][i];		
	}	

	depth++;
	printf("\n\ndepth  %d!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n",depth);	
	for(int i=0;i<Ndir;i++)
	{				
		redRes = oneMoving(&redBall[depth][0],&redBall[depth][1],i,'R');
		blueRes = oneMoving(&blueBall[depth][0],&blueBall[depth][1],i,'B');
		if(redRes>=0 || blueRes>=0)	
		{
			cnt++;
			if(blueRes==0)
				return;
			if(redRes==0)
			{ 
				if(cnt<minCnt)
					minCnt = cnt;				
			}
			moveBall(cnt,depth);
				printf("\n\nEND depth  %d!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n",depth);
			setBoard(depth-1);
		}
	}
	

}

//void switchPos(char A,char B,int rowA,int colA,int rowB,int colB)
//{
//	//char temp;
//	board[rowA][colA] = A;
//	board[rowB][colB] = B;
//	
//}

int oneMoving(int *HorPos,int *VerPos,int way,char color)
{
	char current;	
	int row,col;
	
	row = *HorPos;
	col = *VerPos;
	
	for(int i=1;i<MAX;i++)
	{	
		switch(way)
		{
			case 0: //up
				if(row>0)
				{ row--;break;}
				else
					return -1;			
			case 1: //right
				if(col<M-1)
				{ col++;break;}
				else
					return -1;
			case 2: //down
				if(row<N-1)
				{ row++;break;}
				else
					return -1;				
			case 3: //left
				if(col>0)
				{ col--;break;}
				else
					return -1;				
			default :
				printf("wrong direction!!");
				exit(-1);
		}
		
			printf("row/%d,col/%d H/%d,V/%d=== char : %c\n",row,col,*HorPos,*VerPos,board[row][col]);

		if(board[row][col]=='.')
		{
//			switchPos('.',color,HorPos,VerPos,row,col);
			board[*HorPos][*VerPos] = '.';
			board[row][col] = color;
			*HorPos = row;
			*VerPos = col;
			debug_printBoard();
		}	
		else if(board[row][col]=='O')
			return 0;
		else
		{
			if(i==1)
				return -1;
			return 1;
		 } 

	}
}

int main(int argc, char** argv) 
{
	
	initPosition();

//	for(int i=0;i<N;i++)
//	{
//		printf("%s",board[i]);
//		printf("\n");
//	}
	
	moveBall(0,0);	
	
	if(minCnt==11)
		minCnt = -1;
	printf("Minimum count : %d\n",minCnt);
	
	return 0;
}




void debug_printBoard(void)
{
	for(int i=0;i<N;i++)
	{
		printf("%s",board[i]);
		printf("\n");
	}
}
