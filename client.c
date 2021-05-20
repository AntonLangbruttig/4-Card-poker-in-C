#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>
#include "deck.h"


int main()
{

	card* curdeck = ((card*)malloc(sizeof(card)*52));

	int s0 = socket(AF_UNIX, SOCK_STREAM, 0);
        if(s0 == -1)
        {
             printf("\n\nSorry server down\n\n");
             return -1;
        }

        struct sockaddr name0 = {AF_UNIX, "Cards"};
      	socklen_t namelen0 = sizeof(struct sockaddr) + 7;

        bind(s0,&name0,namelen0);
        if( connect(s0, &name0, namelen0) == -1)
     	{
             printf("\n\nServer down sorry \n\n");
             return -1;
         }
         read(s0,curdeck,sizeof(card)*52);
         close(s0);


	//poker
	int money = 100;
	int hands = 0;
	int lost = 0;
	int play = 1;
	printf("\n\n\n\n");
	printf("                        Welcome!\n");
	printf("    ------------------------------------------------------      ");
	while(money != 0 && play ==1)
	{
           if(hands == 0 )
           {
              printf("\n\n        Would you like to play a hand of 4 card poker?\n\n");
           }
	   else
	   {
	     printf("\n\n     Would you like to play another hand of 4 card poker?\n\n");
	   }
  	   char ask[2];
	   int l = 0;
	   while(!(ask[0]== 'y' || ask[0] == 'n'))
	   {
		if(l ==0)
		{
                    printf("\n\n                 Yes (y)   No (n) : ");
		}
		else
		{
		    printf("\n\n            That was not a valid selection!");
		    printf("\n\n            Please select Yes(y) or No(n) : ");
		}
		gets(ask);
		fflush(stdout);
		ask[0] = tolower(ask[0]);
		++l;
	   }
	   printf("\n\n    ------------------------------------------------------      ");
	   if(ask[0] == 'y')
	   {

	   	ask[0] = 'p';

		// place bet
		int bet;

		printf("\n          You have %d chips Please place your bet\n ", money);
		printf("\n\n                          Bet = ");
		int takeB = 0;
		char get [12];
                while(takeB ==0)
		{
		     gets(get);
		     bet = atoi(get);
                     if(bet<=0 || bet > money)
	             {
                         printf("\n        Please enter a positive number of chips\n");
			 printf("     less then or equal to your total number of chips");
			 printf("\n\n                          Bet = ");
		      }
		      else
		      {
			 takeB = 1;
	 	      }
		}

		// deal cards and get new deck if deck is empty
		int z=0;
		card* hand = ((card*)malloc(sizeof(card)*4));
		while (z <4)
		{
			printf("\n\n\n");
			for(int i=0; i<52;++i)
			{

				if(curdeck[i].value != 0)
				{
					hand[z].value = curdeck[i].value;
					hand[z].suit = curdeck[i].suit;
					curdeck[i].value = 0;
					++z;
				}
				if(z ==4)
				{
					i = 52;
				}
			}
			if(z !=4)
                        {

        			int s0 = socket(AF_UNIX, SOCK_STREAM, 0);
        			if(s0 == -1)
        			{
                			printf("Did not connect first");
                			return -1;
        			}

        			struct sockaddr name0 = {AF_UNIX, "Cards"};
        			socklen_t namelen0 = sizeof(struct sockaddr) + 7;

        			bind(s0,&name0,namelen0);
        			if( connect(s0, &name0, namelen0) == -1)
        			{
                			printf("Did not conect secound");
                			return -1;
        			}
                                free(curdeck);
				card* curdeck = ((card*)malloc(sizeof(card)*52));
				read(s0,curdeck,sizeof(card)*52);
				close(s0);
                        }

		}
			// print hand
			printf("                  ------- Your Hand -------\n\n");
                        printf("    |---------|  |---------|  |---------|  |---------| \n");
                        printf("    |%c        |  |%c        |  |%c        |  |%c        | \n",hand[0].suit,hand[1].suit,hand[2].suit,hand[3].suit);
                        printf("    |         |  |         |  |         |  |         |  \n");
			printf("    |    ");
		      	for(int i =0; i<4; ++i)
			{

				if(i != 0)
				{
					printf("  |    ");
				}
				if(hand[i].value == 11)
				{
					printf("J");
				}
				else if(hand[i].value == 12)
                                {
                                        printf("Q");
                                }
				else if(hand[i].value == 13)
                                {
                                        printf("K");
                                }
                                else if(hand[i].value == 1)
                                {
                                        printf("A");
                                }
                                else
                                {
                                        printf("%d",hand[i].value);
                                }
				if(hand[i].value == 10)
				{
					printf("   |");
				}
				else
				{
					printf("    |");
				}
			}
                        printf("\n");
			printf("    |         |  |         |  |         |  |         |  \n");
                        printf("    |       %c |  |       %c |  |       %c |  |       %c |  \n",hand[0].suit,hand[1].suit,hand[2].suit,hand[3].suit);
                        printf("    |---------|  |---------|  |---------|  |---------|   \n");


		//sort hand

		for(int i =0 ; i<4; ++i)
		{
			for(int j=i+1; j<4; ++j)
			{
				if(hand[i].value> hand[j].value)
				{
					card n = hand[i];
					hand[i] = hand[j];
					hand[j] = n;
				}
			}
		}
		printf("\n\n\n");
		// check hands
		// 4 of a kind
		if(hand[0].value == hand[1].value && hand[2].value ==hand[3].value
			&& hand[0].value == hand[3].value)
		{
			money += bet*20825;
			printf("       You got 4 of a kind!");
		}
		// straight flush
		else if((hand[0].value+3 == hand[1].value+2 && hand[2].value+1 == hand[3].value) &&
			(hand[0].suit == hand[1].suit && hand[2].suit == hand[3].suit &&
				hand[0].suit == hand[3].suit))
		{
			money += bet*6153;
			printf("       You got a straight flush!");
		}
		// 3 of a kind
		else if((hand[0].value == hand[1].value && hand[0].value==hand[2].value) ||
				 (hand[1].value == hand[2].value && hand[1].value == hand[3].value))
		{
			money += bet*108;
			printf("     You got a 3 of a kind");
		}
		// straight
		else if(hand[0].value+3 == hand[1].value+2 && hand[1].value+2 == hand[2].value+1 &&  hand[2].value+1 == hand[3].value)
		{
			money += bet*98;
			printf("        You got a straight!");
		}
		// 2 pair
		else if (hand[0].value == hand[1].value && hand[2].value ==hand[3].value)
		{
			money += bet*96;
			printf("       You got 2 pair!");
		}
		// flush
		else if (hand[0].suit == hand[1].suit && hand[2].suit == hand[3].suit && hand[0].suit == hand[3].suit)
		{
			money += bet*96;
                        printf("       You got a flush!");
		}
		//pair
		else if (hand[0].value == hand[1].value || hand[1].value ==hand[2].value
				|| hand[2].value == hand[3].value)
		{
			money += bet*3;
                        printf("       You got a pair!");
		}
		//nothing
		else
		{
			money -= bet;
			printf("              You lost !");
			++lost;
		}
		printf("     You now have %d chips!\n\n\n    -----------------------------------------------------",money);
		++hands;
		printf("\n\n\n");
	}
	else
	{
	   play = 0;
	}
    }
    printf("\n                  Thank   You  for Playing! 	");
    printf("\n    ------------------------------------------------------      \n\n");
    printf("                ~Your total Chips are %d ~\n",money);
    printf("                ~You have played %d hands~\n",hands);
    printf("                    ~You lost %d hands~\n",lost);
    printf("                    ~You won %d hands~",hands-lost);
    if(money<100)
    {
         printf("\n\n                BETTER LUCK NEXT TIME !!!!!!");
    }
    printf("\n\n    ------------------------------------------------------      \n\n\n\n\n");

    return 0;
}

