#include <iostream>
#include <stdio.h> 

/* 
1. ��� ����
2. ����� �̵�
  2.1 1������ ����, �̵��Ѱ��� ����Ⱑ���ų�, �� �ִ��� Ȯ��
  2.2 �̵� �Ұ� �ϸ� ���� ���� �� �ٽ� üũ
  2.3 �̵��� �� �ִٸ� �� ���� ������ �ڸ��ٲ�
3. ��� �̵�
  3.1 ������ Ȯ���Ͽ� ������ ����� �� ��� üũ
  3.2 ��� ���ɼ��� ���� �����Ͽ� ��� �迭�� ����
4. ��� Ȯ��
  4.1 �ִ� ����   
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
