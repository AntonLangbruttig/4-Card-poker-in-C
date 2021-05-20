#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <time.h>
#include "deck.h"

void ctrlc();

int main()
{
	printf("\n");
    	struct card* curdeck = ((card*)malloc(sizeof(card)*52));
	deck(curdeck);
	int s1;
        void ctrlc()
        {
                unlink("Cards");
                close(s1);
                free(curdeck);
                fflush(stdout);
                printf("\n\n\n\n\nHave a nice day!\n\n\n\n");
		exit(1);
        }


	// structs to hold the old a new function pointers
        struct sigaction news;
        struct sigaction olds;

      	// assign new handler function pointer
        news.sa_handler = ctrlc;
        news.sa_flags = 0;

	sigaction(SIGINT,&news,&olds);


	s1 = socket(AF_UNIX, SOCK_STREAM, 0);
	if (s1 == -1)
	{
		printf("\n\n\nDid not work first\n\n\n");
		return -1;
	}

	struct sockaddr name1 = {AF_UNIX, "Cards"};
	socklen_t namelen1 = sizeof(struct sockaddr) + 12;

	bind(s1, &name1, namelen1);


     	 printf("\n");


	printf("\n\n\nWelcome\n\n\n");
	while(1)
	{
		if (listen(s1, 1) == -1)
		{
			printf("fails at listen\n\n");
			return -1;
		}

		struct sockaddr name1_0;
		socklen_t namelen1_0;

		int s2;
		if (((s2 = accept(s1, &name1_0, &namelen1_0)) == -1))
		{
                        printf("\n\naccept fail\n\n\n");
                        return -1;

		}


		printf("connected\n");
		deck(curdeck);
        	write(s2,curdeck, sizeof(card)*52);
		fflush(stdout);

		close(s2);
	}

	return 0;

}
void ctrlc()
{
	printf("\n Have a nice day! \n");
}


