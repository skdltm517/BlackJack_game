#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue> 

using namespace std;

#define MAX 20

struct p{
	int x;
	int y;
};

p fish[MAX*MAX];

int N;
int map[MAX][MAX]={0,};
int dist[MAX][MAX]={0,};

bool check[MAX][MAX];

int dy[4]={-1,0,1,0};
int dx[4]={0,1,0,-1};

int sharkP[2];
int sharkSize=2;
int eatFishN=0;
int fishN=0,fishMax;
int dst[2];
int sec=0;

int getAbs(int input){
	if(input<0) return -input;
	else input;
}

p makeP(int y,int x){
	p temp;
	temp.y = y;
	temp.x = x;
	return temp;
}

void initFish(void){
	
	//get fish position
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(map[i][j]==9){
				sharkP[0]=i;
				sharkP[1]=j;
			}else if(map[i][j]>0 && map[i][j]<=6){
				fish[fishN].y = i;
				fish[fishN].x = j;
				fishN++;					
			}
		}
	} 
	fishMax = fishN;	
}


bool oneMove(int y,int x){
	//printf("shark level : %d\n",sharkSize);
	if(y>=0 && y<N && x>=0 && x<N){
		if(check[y][x]==true) return false;
		else if(map[y][x]<=sharkSize) return true;
		else return false;			
	}else return false;
}

//최단거리 탐색 
void calcDist(){
 	
 	memset(check,0,sizeof(check));	
 	
	queue <p> Q;
	Q.push(makeP(sharkP[0],sharkP[1]));
	check[sharkP[0]][sharkP[1]] = true;
	dist[sharkP[0]][sharkP[1]] = 0;

	while(!Q.empty()){
		
		p cur = Q.front();
		Q.pop();
		
		for(int k=0;k<4;k++){
		
			int nextR = cur.y + dy[k];
			int nextC = cur.x + dx[k];			
			
			if(oneMove(nextR,nextC)==true){
				check[nextR][nextC] = true;
				Q.push(makeP(nextR,nextC));
				dist[nextR][nextC] = dist[cur.y][cur.x]+1;
			}		
		}
		
	}		
}

int main(int argc, char** argv) {
	
	scanf("%d",&N);
	
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			scanf("%d",&map[i][j]);
	}

	//input map and fish position
	initFish();
	
	int findFood =1;
	while(findFood ==1){
		memset(dist,0,sizeof(dist));
		int minDist=99;
		findFood =0;
		
		//calculate real distance
		calcDist();	
		
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				if(dist[i][j]<minDist && map[i][j]<sharkSize && map[i][j]!=0){
					minDist = dist[i][j];
					findFood = 1;				
					dst[0]=i;
					dst[1]=j;
				}
			}
		}			
	
		if(findFood==1){
			sec+=minDist;
			
			//move shark and eat fish		
			map[dst[0]][dst[1]]=9;
			map[sharkP[0]][sharkP[1]]=0;
			
			sharkP[0]=dst[0];
			sharkP[1]=dst[1];
			
			eatFishN++;
			fishN--;
			
			//check shark's growth
			if(eatFishN==sharkSize){
				eatFishN = 0;
				sharkSize++;			
			}
		}
							
	}	
	printf("%d",sec); 	
	
	return 0;
}


