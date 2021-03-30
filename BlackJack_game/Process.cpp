#include "Macro.h"
#include "Process.h"
#include "CardMoving.h"

int bet[MAXUSER];
int res[MAXUSER]; // win 1/lose 0
//extern int haveA[MAXUSER+1];

int betDollar(int player, int Dollar){
	int i;
	
	if(player == 0)
	{		
		do
		{	cin>>bet[player];
			
			if(bet[player]<=0)
				cout<<"Please bet over $1"<<endl;
			else if(bet[player]>Dollar)
				cout<<"You have only $"<<Dollar<<endl;
			else 
				break;	
				
		}while(1);
		
		//cin>>bet[player];
		//if(bet[player]>Dollar);		
	}	
	else
		bet[player] = (rand() % MAXBETMONEY)+1;		
	
	if(Dollar - bet[player] < 0)
		return -1;
	
	return bet[player]; 
}


int GoStop(void){
	int answer;
	int res;
		
	while(1)
	{
		cout<<"Dealer : Are you go?? (yes:1 / no:0) -> ";
		cin>>answer;
		
		if(answer==0)	
		{
			cout<<"Stop!"<<endl;
			break;
		}			
		else if(answer == 1)
		{
			cout<<"Go!"<<endl;
			break;
		}				
		else
			cout<<"[error] Please choose 1 or 0"<<endl;	
	}
							
	return answer;
}
	

int GetAction(int player)
{
	while(1)
	{
		int sum = calcCardScore(player);
					
		if( 1 == CheckBJ(player))  //check black jack
		{
			cout<<"Black Jack!!^_^"<<endl;
			break;				
		}
			
		cout<<"  -> ";
		ShowAllCard(player);
		cout<<endl;
		//int sum = calcCardScore(player);
					
		if(sum >21)
		{
			cout<<" Dead (sum:"<<sum<<")";
			break;						
		}	
		else if(player == 0 && 1==GoStop() || player!=0 && sum < 17)
		{
			if(PullCard(player)<0)
				return -1;	
						
		}	
		else
			break;

	}
	
	cout<<endl;	
	return 0;	
}

int CheckResult(int Dscore, int player, int dollar)
{
	int Pscore = calcCardScore(player);
	
	if(player==0)
		cout<<"--- You     : ";
	else
		cout<<"--- Player"<<player<<" : ";
		
	//이긴경우 블랙잭 || 서버 블랙잭 아님 && 21이하 && 서버보다 점수 높음 
	//진경우 21초과 || 블랙잭 아님 && (서버보다 점수 낮음 || 서버 블랙잭)
	if(CheckBJ(player)==1)
	{
		cout<<"WIN!! You are BLACKJACK!!";
		res[player] = 1;
	}	
	else if(CheckBJ(player)==1)
	{
		cout<<"LOSE!! Dealer is BLACKJACK T.T";
		res[player] = 0;		
	}
	else
	{			
		if(Pscore > 21){
			cout<<"LOSE!! You are dead O<-< !!";
			res[player] = 0;
		}else if(Dscore > 21){
			cout<<"WIN!! Dealer is dead O<-< !!";
			res[player] = 1;
		}else if(Pscore >= Dscore){
			cout<<"WIN!! Better than Dealer!!";
			res[player] = 1;
		}else{
			cout<<"LOSE!! Worse than Dealer!!";
			res[player] = 0;
		}
		
	}
	
	cout<<"(sum:"<<Pscore<<") ";	
	
	if(res[player] == 0)
	{
		cout<<"($:"<<dollar<<" - "<<bet[player]<<" = $"<<dollar-bet[player]<<")"<<endl;
		dollar -= bet[player];
		
	}
	else
	{
		cout<<"($:"<<dollar<<" + "<<bet[player]<<" = $"<<dollar+bet[player]<<")"<<endl;	
		dollar += bet[player];	
	}
	
	if(dollar<0)
		return -1;
	
	return dollar;
}

void CheckWinner(int Nplayer, int* dollar)
{
	int BestMoney = 0;
	int winner = 0;
	for(int i=0;i<Nplayer;i++)
	{
		if(i==0)
			cout<<"--- You have ";
		else
			cout<<"--- Player"<<i<<" has ";
		
		cout<<*dollar<<"."<<endl;
		
		if(*dollar>BestMoney)
		{
			BestMoney = *dollar;
			winner = i;
		}
		//	BestMoney = *dollar;
		dollar++;	
	}
	
	cout<<"So the winner is ";
	if(winner==0)
		cout<<"YOU!! Congraturations~~!!!";
	else
		cout<<"player"<<winner<<"!";
}
