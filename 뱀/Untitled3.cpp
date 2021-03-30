#include <cstdio>


#define MAX 100

struct p{
	int x;
	int y;
};

int N,K,L;
int X[MAX];
char C[MAX];
int map[MAX][MAX]={0,}; //6=apple, 1=snake

int dy[4] ={-1,0,1,0};
int dx[4] ={0,1,0,-1};

p before[MAX];
p head;
int bodyLen=1;
int sec=0;

int main(int argc, char** argv) {
	
	//input
	scanf("%d %d",&N,&K);
	
	p apple;
	for(int i=0;i<K;i++){
		scanf("%d %d",&apple.y,&apple.x);
		map[apple.y-1][apple.x-1] = 6;
	}	
	
	scanf("%d",&L);
	
	for(int i=0;i<L;i++){
		scanf("%d %c",&X[i],&C[i]);
	}
	
	
	head.y=0;
	head.x=0;
	map[head.y][head.x]=1;
	
	bool endGame =false;
	int dir =1;
	int idx=0,trace=0;
	//game start
	while(!endGame){
		sec++;
		before[trace].y = head.y;
		before[trace].x = head.x;
		trace++;
		
		p tmp=head;
		tmp.y += dy[dir];
		tmp.x += dx[dir];
		
		if(tmp.y >= N || tmp.y<0 || tmp.x>=N || tmp.x<0 ||map[tmp.y][tmp.x]==1){
			
			endGame = true;
			continue;
		}		
		
		if(map[tmp.y][tmp.x] ==6 )
			bodyLen++;
		else 
			map[before[trace-bodyLen].y][before[trace-bodyLen].x]=0;
			
		head=tmp;
		map[head.y][head.x]=1;
		
		
		if(sec==X[idx]){
			if(C[idx]=='D') dir+=1;
			else if((C[idx]=='L')) dir+=3;
			dir = dir%4;
			idx++;
		}
		
	}

	printf("%d\n",sec); 
	 
	
	return 0;
}
