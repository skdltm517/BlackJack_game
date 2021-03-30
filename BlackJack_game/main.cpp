#include "Macro.h"
#include "Process.h"
#include "CardMoving.h"


//int CardTray[MAXCARD];
int Dollar[MAXUSER];
extern int icard;

int main(int argc, char** argv) {
	int i;
	int round =1;
	int Player; 
	int EndGame = 0;
	
	srand(time(NULL));
	
	//1. Set player number
	
	cout<<"Input the player number (max : "<<MAXUSER<< "): ";
	cin>>Player;
	cout<<"Dealer: OK, "<<Player<<" players play."<<endl;
	
	//2. Init money
	
	for(i=0;i<Player;i++)
	{
		Dollar[i] = STARTMONEY;
		//cout<<i<<"->"<<Dollar[i]<<endl;
	}
	
	//3. Mix cards
		mixCardTray();
		
	//4. Start each round
	while(EndGame == 0){
		//4-1. Initialize variable to start new round.
	//	InitRound(Player);
		int cards = MAXCARD-icard; 
			
		cout<<"\nDealer: Now let's play "<<round<<" round!"<<endl;
		cout<<"Dealer: "<<cards<<"cards left."<<endl;

		
		//4-2. Betting money to this round
		cout<<"Dealer: Bet your money."<<endl;
		cout<<"Betting (I have "<<Dollar[0]<<"$..):";
	
		int mybet = betDollar(0,Dollar[0]);
		
		if(mybet<0){
			cout<<"[error]betting error!!";
			EndGame = 1;
			continue;
		}
		
		cout<<endl<<"Dealer: OK, You bet "<<mybet<<"."<<endl;
		cout<<"$$$$$$$$ Betting $$$$$$$$"<<endl;
		
		cout<<"- You     : "<<mybet<<"$"<<endl;
		
		for(i=1;i<Player;i++)
		{
			int bet = betDollar(i,Dollar[i]);
			
			if(bet<0)
			{
				EndGame = 1;
				continue;
			}
			
			cout<<"- plyer "<<i<<" : "<<bet<<"$"<<endl;
		
		}
		cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl<<endl;
		
		//4-3. Distribute card 
		if(FirstCardSetting(Player)<0){
			EndGame = 1;
			continue;
		}
			
		//4-4. Open cards

		cout<<endl<<"******* Card of "<<round<<" Round~!*******"<<endl;
			ShowInitCard(Player);
		cout<<"********************************"<<endl<<endl;
		
		
		//4-5. Play the game 
		cout<<">>>> My turn : "<<endl;
		
		if(GetAction(0)<0)
		{
			EndGame = 1;
			continue;
		}
		
		for(i=1;i<=Player;i++)
		{	
			if(i==Player) 
				cout<<"\n>>>> Dealer's turn : "<<endl;
			else
				cout<<"\n>>>> Player"<<i<<"'s turn : "<<endl;
			
			if(GetAction(i)<0)
			{
				EndGame = 1;
				break;
			}
		}
		
		if(EndGame != 0)
			continue;
					
		//4-6. check result
		cout<<"\n~~~~~~~~~~"<<round<<" round result~~~~~~~~~~~~"<<endl;
		
		int DealerScore = calcCardScore(Player);
		
		if(CheckBJ(Player)==1)
			cout<<"--- Dealer Score : BlackJack"<<endl;
		else
			cout<<"--- Dealer Score : "<<DealerScore<<endl;
		
		int moneyres;
		for(i=0;i<Player;i++)
		{
			 Dollar[i] = CheckResult(DealerScore,i,Dollar[i]);
			 if(Dollar[i]<0)
			 {
			 	EndGame =1;
				break;
			 }
			 					
		}			
		cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		
		if(EndGame != 0)
			continue;
			
		//4-7. go to next round
		round++;
		InitRound(Player);
	}
	//game end(no money/no remain card) -> break round loop
	cout<<"\n\n\n+++++++++++++++++++++\n"<<endl;
	cout<<"      GAME OVER      \n"<<endl;
	cout<<"+++++++++++++++++++++\n\n"<<endl;
	
	//5. Check winner
	cout<<"------------Who is WINNER??-------------"<<endl;

	CheckWinner(Player,Dollar);
	
	return 0;
}
