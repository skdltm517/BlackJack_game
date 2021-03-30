#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAX 20

struct fishInfo{
	int size;
	int dist;
	int locat[2];
};

int N;
int space[MAX][MAX];
fishInfo fishs[400]; 

int sharkLoc[2];
int sharkSize=2;
int eatFishN=0;
int fishN=0, fishMax=0;
int dst[2];
int sec=0;
int minDist;

void initFish(void){
	
	//get fish location
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(space[i][j]==9){
				sharkLoc[0]=i;
				sharkLoc[1]=j;
				printf("sharkpos %d/%d\n",i,j);
			}else if(space[i][j]>0){
				fishs[fishN].size = space[i][j];
				fishs[fishN].locat[0] = i;
				fishs[fishN].locat[1] = j;
				fishN++;					
			}
		}
	} 
	fishMax = fishN;
	
	//get fish distance
	int x,y;
	for(int i=0;i<fishMax;i++){
		x = fishs[i].locat[0] - sharkLoc[0];
		fishs[i].locat[0]>sharkLoc[0] ? x : -x;
		
		y = fishs[i].locat[1] - sharkLoc[1];
		fishs[i].locat[1]>sharkLoc[1] ? y : -y;
		//printf("fish num %d, fishsize %d\n",i,fishs[i].size);
		fishs[i].dist = x+y;		
	}
}

int searchFood(void){
	
	int foodDist = 2*(N-1);
	int findFood=0;
	dst[0]=N;dst[1]=N;
	
	for(int i=0;i<fishMax;i++){
		if(fishs[i].size<sharkSize){
			findFood = 1;
			
			if(fishs[i].dist<=foodDist)
			{
				if(fishs[i].dist==foodDist && fishs[i].locat[0] > dst[0] ||
				 fishs[i].dist==foodDist && fishs[i].locat[0] == dst[0] && fishs[i].locat[1]>dst[1])
					continue;

				foodDist = fishs[i].dist;
				
				dst[0]=fishs[i].locat[0];
				dst[1]=fishs[i].locat[1];
			}
		}
	}
	printf("Search food : findfood %d, fishpos %d/%d\n",findFood,dst[0],dst[1]);
	return findFood;	
}

int oneMove(int dir,int row,int col){
	int cnt=0;

	switch(dir){
		case 0:
			row--;
			break;
		case 1:
			col++;
			break;
		case 2:
			row++;
			break;
		case 3:
			col--;
			break;									
	}
	
	if(row>=0 && row<N && col>=0 && col<N){
		if(space[row][col]>0 && space[row][col]>sharkSize)
			return cnt;
		cnt++;
		sharkLoc[0]=row;
		sharkLoc[1]=col;
		printf("r %d, c %d\n",row,col);
	}
			
	return cnt;
}

void eatFish(int x,int y){
	space[x][y]=0;
	for(int i=0;i<fishMax;i++){
		if(fishs[i].locat[0]==x &&fishs[i].locat[1]==y )
			fishs[i].size = 99;
	}
	eatFishN++;
}

//최단거리 탐색 
int moveShark(int dep){
	
	printf("moveShark depth %d\n",dep);
	int dr = dst[0],dc = dst[1];
	int current[2],direction;	
	current[0]=sharkLoc[0];
	current[1]=sharkLoc[1];
	printf("r %d/%d, c %d/%d\n",sharkLoc[0],dr,sharkLoc[1],dc);
	
	if(sharkLoc[0]== dr &&sharkLoc[1]== dc || dep>=2*N){
		if(dep>=N*N)
			return -1;
		if(minDist>dep+1)
			minDist = dep+1;
		eatFish(dr,dc);
		return 0;
	}else{	
		int row=current[0],col=current[1];
		if(row>dr) direction=0;
		else if(col>dc) direction=3;
		else direction=2;
		//한칸 움직이기
		for(int i=0;i<4;i++){
			direction = direction%4;
			if(oneMove(direction,row,col)==1)
				moveShark(dep+1);
			sharkLoc[0]=current[0];
			sharkLoc[1]=current[1];	
			direction++;	
		}		
	}
	
	return 0;		
}

int main(int argc, char** argv) {
	
	scanf("%d",&N);
	
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			scanf("%d",&space[i][j]);
	} 
	
	initFish();
	
	int debug;
	while(searchFood()==1){
		//printf("!!%d\n",debug);
		debug++;
		
		minDist = 2*(N-1);
		moveShark(1);
		
		sec += minDist;
		
		if(eatFishN==sharkSize){
			eatFishN -= sharkSize;
			sharkSize++;			
		}					
		
	}

	
	printf("%d",sec); 	
	
	return 0;
}


