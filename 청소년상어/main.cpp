#include <iostream>
#include <stdio.h> 

/* 
1. 상어 입장
2. 물고기 이동
  2.1 1번부터 시작, 이동한곳에 물고기가없거나, 상어가 있는지 확인
  2.2 이동 불가 하면 각도 조정 후 다시 체크
  2.3 이동할 수 있다면 그 곳의 물고기와 자리바꿈
3. 상어 이동
  3.1 방향을 확인하여 가능한 경우의 수 모두 체크
  3.2 모든 가능성에 대해 덧셈하여 결과 배열에 저장
4. 결과 확인
  4.1 최댓값 도출   
 */
#define ROW 4
#define COL 4
#define FISHMAX 16

typedef struct {
	int fishNum;
	int direction;
}oneSpace_t;

oneSpace_t space[ROW][COL];
int fishSum=0;

void checkSpace()
{
	
}

void changeFish(int row, int col, int direction)
{
	oneSpace_t temp;
	
	temp = space[row][col];
	
	space[row][col].fishNum = space[]
}

void moveFish(int fish)
{
	for(int i=0;i<ROW;i++)
	{
		for(int j=0;j<COL;j++)
		{
			if(space[i][j].fishNum == fish)
			{
				changeFish(i,j,space[i][j].direction);
			}
		}	
	}
}


int main(int argc, char** argv) {
	
	const int shark = 0;
	
	for(int i=0;i<ROW;i++)
	{
		for(int j=0;j<COL;j++)
			scanf("%d %d",&space[i][j].fishNum, &space[i][j].direction);
	}
	
	//entering the shark
	fishSum += space[0][0].fishNum;
	space[0][0].fishNum = shark;
	
	//moving fishs
	for(int i=0;i<ROW;i++)
	{
		for(int j=0;j<COL;j++)
		{
			for(int k=1;k<=FISHMAX;k++)
			{
				moveFish();
					
			}
		}	
	}


	
//	for(int i=0;i<ROW;i++)
//	{
//		for(int j=0;j<COL;j++)
//			printf("%d %d ",space[i][j].fishNum, space[i][j].direction);
//		printf("\n");
//	}	
	
	return 0;
}
