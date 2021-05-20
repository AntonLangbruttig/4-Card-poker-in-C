#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	int value;
	char suit;
}card;

void deck(card* deck)
{
	for(int i = 0; i<52; i++)
	{
		deck[i].value = i % 13 +1;

		if(i< 13)
		{
			deck[i].suit = 'H';
		}
		else if(i<26)
		{
			deck[i].suit = 'D';
		}
		else if(i<39)
		{
			deck[i].suit = 'C';
		}
		else
		{
			deck[i].suit = 'S';
		}
	}
	//shuffle deck
	for (int a = 0; a<100; ++a)
	{
		srand(time(NULL));
		for (int i = 0; i<51; ++i)
		{
			int s = rand() %52;
			card d = deck[i];
			deck[i] = deck[s];
			deck[s] = d;
		}
	}
}
