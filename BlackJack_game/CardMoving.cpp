#include "Macro.h"
#include "Process.h"
#include "CardMoving.h"

int icard;
int Ncard[MAXUSER+1]={0,}; //having cards
int UserCardVal[MAXUSER+1][MAXHAVECARD]; //each card value
int CardTray[MAXCARD];
int haveA[MAXUSER+1];
extern int bet[MAXUSER];

void mixCardTray(void){
	int i,temp,rdv;
	
	for(i=0;i<MAXCARD;i++)
	{
		CardTray[i] = i+1;
	}
	
	for(i=0;i<MAXCARD;i++)
	{
		rdv = rand()%(MAXCARD-1);
		temp = CardTray[i];
		CardTray[i] = CardTray[rdv];
		CardTray[rdv] = temp;
	}
	
	cout<<"Dealer: The cards were mixed."<<endl;	

}

int PullCard(int player)
{
	int card;
	
	card = CardTray[icard]; 
//	cout<<"pick carf!!! "<<card<<endl;
	icard++;
		
	if(icard>MAXCARD){
		UserCardVal[player][Ncard[player]] = -1;
	}else{
		UserCardVal[player][Ncard[player]] = card; 
		Ncard[player]++;
	}

	return UserCardVal[player][Ncard[player]];
}

int CheckCards(int Nplay)
{
	for(int i=0;i<Nplay;i++)
	{
		for(int j=1;j<Ncard[i];j++)
		{
		 	if(UserCardVal[i][j]<0)
			 	return -1; 	
		}	 
	}
	return 0;
}

int FirstCardSetting(int Nplay)
{	
	int i,j;
	
	for(i=0;i<2;i++)
	{
		PullCard(Nplay);
		PullCard(0);

		for(j=1;j<Nplay;j++)
		{
		 	PullCard(j);		 	
		}	 
	}
	
	if(CheckCards(Nplay)<0)
		return -1;	 
	return 0;
}



void ShowCardShape(int card)
{
	int Npershape = 12;
	int i = card/Npershape;
	int j = card%Npershape +1;
	
	switch(i%4){
		case 0:
			cout<<"¢¾";
			break;
		case 1:
			cout<<"¢¼";
			break;
		case 2:
			cout<<"¢À";
			break;	
		case 3:
			cout<<"¡ß";
			break;
	}
			
	switch(j){
		case 10:
			cout<<"J ";
			break;
		case 11:
			cout<<"Q ";
			break;
		case 12:
			cout<<"K ";
			break;
		case 1:
			cout<<"A ";
			break;
		default:
			cout<<j<<" " ;
			break;
	}
}

void ShowInitCard(int Nplayer)
{
	
	cout<<"--Dealer  :  ?  ";
	ShowCardShape(UserCardVal[Nplayer][1]);
	cout<<endl;
	
	cout<<"--You     : ";
	ShowCardShape(UserCardVal[0][0]);
	ShowCardShape(UserCardVal[0][1]);
	cout<<endl;
	
	for(int i=1;i<Nplayer;i++){
		cout<<"--Player"<<i<<" : ";
		ShowCardShape(UserCardVal[i][0]);
		ShowCardShape(UserCardVal[i][1]);
		cout<<endl;
	}
		
}


int CardScoreVal(int card)
{
	int score;
	int num = card%12 + 1;
	
	if(num>9)
		score = 10;
	else if(num==1)
		score = 11;	
	else
		score = num;
	
	return score;
}

int calcCardScore(int player)
{
	int score = 0;//CardScoreVal(UserCardVal[player][0]);
	
	for(int j=0;j<Ncard[player];j++)
	{
		if(CardScoreVal(UserCardVal[player][j]) == 11)
			haveA[player]++;
			 
		score += CardScoreVal(UserCardVal[player][j]);
		//cout<<"score : "<<score<<endl;
	}	
		
	if(score>21 && haveA[player]!=0)	
		return score-10;
	else	
		return score;
}

int CheckBJ(int player)
{	
	int card1 = UserCardVal[player][0];
	int card2 = UserCardVal[player][1];
	int sum = CardScoreVal(card1)+CardScoreVal(card2);
	//if(calcCardScore(player) == 21)
	if(sum==21)
		return 1;
	else
		return 0 ;	
}

void ShowAllCard(int player)
{					
	for(int j=0;j<Ncard[player];j++)
	{
		ShowCardShape(UserCardVal[player][j]);
	}		
}

void InitRound(int player)
{
	int i,j;
	
	for(i=0;i<=player;i++){
	 	//withdraw player's card
	 	for(j=0;j<Ncard[i];j++)
		 {
		 	UserCardVal[i][j]=0;
		 }
		 //reset to 0 for next round
		 bet[i]=0;
		 Ncard[i]=0;
		 haveA[i]=0;
	 }
				
}


