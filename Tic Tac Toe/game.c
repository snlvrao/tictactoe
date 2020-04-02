#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio_ext.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "game_struct.h"

void checkStatusP2(tictactoe *shmptr);
void checkStatusP1(tictactoe *shmptr);

int main(int argc, char *argv[])
{
	int shmid, i ,j, pos;
	char sign, k = '1';
	tictactoe *shmptr;
	
	if(argc < 3)
	{
		printf("Insufficient arguments\n");
		exit(1);
	}
	
	/* Create shared memory if P1 else open if P2 */
	if(strcmp(argv[2], "P1") == 0)
	{
		shmid = shmget(atoi(argv[1]), 100, IPC_CREAT | 0660);
	}
	else
	{
		shmid = shmget(atoi(argv[1]), 0, 0);
	}
	if(shmid == -1)
		{
			perror("shmget");
			exit(1);
		}
	
	/* Attach shared memory */
	shmptr = shmat(shmid, 0, 0);
	if(shmptr == (tictactoe *) -1)
	{
		perror("shmat");
		exit(1);
	}
	
	/* Initialize structure */
	for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				shmptr->data[i][j] = k++;
			}
		}
	shmptr->status = 1;
	shmptr->count = 0;
	
	/* Gameplay based on turns */
	while(1)
	{
		if(strcmp(argv[2], "P1") == 0)
		{
			checkStatusP2(shmptr);
			
			/* Read data from shared memory */
			printf("\n");
			for(i = 0; i < 3; i++)
			{
				for(j = 0; j < 3; j++)
				{
					printf("%c ", shmptr->data[i][j]);
				}
				printf("\n");
			}
			
			/* Write data to shared memory */
			printf("\nEnter sign and position\n");
			__fpurge(stdin);
			scanf("%c", &sign);
			__fpurge(stdin);
			scanf("%d", &pos);
			switch(pos)
			{
				case 1: shmptr->data[0][0] = sign;
						break;
				case 2: shmptr->data[0][1] = sign;
						break;
				case 3: shmptr->data[0][2] = sign;
						break;
				case 4: shmptr->data[1][0] = sign;
						break;
				case 5: shmptr->data[1][1] = sign;
						break;
				case 6: shmptr->data[1][2] = sign;
						break;
				case 7: shmptr->data[2][0] = sign;
						break;
				case 8: shmptr->data[2][1] = sign;
						break;
				case 9: shmptr->data[2][2] = sign;
						break;
				default: printf("Invalid\n");
			}
			shmptr->status = 2;
			
			/* Display modified data */
			printf("\n");
			for(i = 0; i < 3; i++)
			{
				for(j = 0; j < 3; j++)
				{
					printf("%c ", shmptr->data[i][j]);
				}
				printf("\n");
			}
		}
		else
		{
			checkStatusP1(shmptr);
			
			/* Read data from shared memory */
			printf("\n");
			for(i = 0; i < 3; i++)
			{
				for(j = 0; j < 3; j++)
				{
					printf("%c ", shmptr->data[i][j]);
				}
				printf("\n");
			}
			
			/* Write data to shared memory */
			printf("\nEnter sign and position\n");
			__fpurge(stdin);
			scanf("%c", &sign);
			__fpurge(stdin);
			scanf("%d", &pos);
			switch(pos)
			{
				case 1: shmptr->data[0][0] = sign;
						break;
				case 2: shmptr->data[0][1] = sign;
						break;
				case 3: shmptr->data[0][2] = sign;
						break;
				case 4: shmptr->data[1][0] = sign;
						break;
				case 5: shmptr->data[1][1] = sign;
						break;
				case 6: shmptr->data[1][2] = sign;
						break;
				case 7: shmptr->data[2][0] = sign;
						break;
				case 8: shmptr->data[2][1] = sign;
						break;
				case 9: shmptr->data[2][2] = sign;
						break;
				default: printf("Invalid\n");
			}
			shmptr->status = 1;
			
			/* Display modified data */
			printf("\n");
			for(i = 0; i < 3; i++)
			{
				for(j = 0; j < 3; j++)
				{
					printf("%c ", shmptr->data[i][j]);
				}
				printf("\n");
			}
		}
		shmptr->count++;
		
		/* Check Victory */
		if((shmptr->data[0][0] == sign) && (shmptr->data[0][1] == sign) && (shmptr->data[0][2] == sign))
		{
			printf("%s is the winner!\n", argv[2]);
			shmptr->status = 0;
			break;
		}
		else if((shmptr->data[1][0] == sign) && (shmptr->data[1][1] == sign) && (shmptr->data[1][2] == sign))
		{
			printf("%s is the winner!\n", argv[2]);
			shmptr->status = 0;
			break;
		}
		else if((shmptr->data[2][0] == sign) && (shmptr->data[2][1] == sign) && (shmptr->data[2][2] == sign))
		{
			printf("%s is the winner!\n", argv[2]);
			shmptr->status = 0;
			break;
		}
		else if((shmptr->data[0][0] == sign) && (shmptr->data[1][0] == sign) && (shmptr->data[2][0] == sign))
		{
			printf("%s is the winner!\n", argv[2]);
			shmptr->status = 0;
			break;
		}
		else if((shmptr->data[0][1] == sign) && (shmptr->data[1][1] == sign) && (shmptr->data[2][1] == sign))
		{
			printf("%s is the winner!\n", argv[2]);
			shmptr->status = 0;
			break;
		}
		else if((shmptr->data[0][2] == sign) && (shmptr->data[1][2] == sign) && (shmptr->data[2][2] == sign))
		{
			printf("%s is the winner!\n", argv[2]);
			shmptr->status = 0;
			break;
		}
		else if((shmptr->data[0][0] == sign) && (shmptr->data[1][1] == sign) && (shmptr->data[2][2] == sign))
		{
			printf("%s is the winner!\n", argv[2]);
			shmptr->status = 0;
			break;
		}
		else if((shmptr->data[0][2] == sign) && (shmptr->data[1][1] == sign) && (shmptr->data[2][0] == sign))
		{
			printf("%s is the winner!\n", argv[2]);
			shmptr->status = 0;
			break;
		}
		else if(shmptr->count == 9)
		{
			printf("\nMatch Draw!\n");
			shmptr->status = 3;
			break;
		}
		else
		{
			continue;
		}
	}
}

void checkStatusP1(tictactoe *shmptr)
{	
	printf("\nWaiting for opponent\n");
	while(1)
	{
		sleep(1);
		if(shmptr->status == 2)
		{
			return;
		}
		else if(shmptr->status == 0)
		{
			printf("\nP1 is the winner!\n");
			exit(0);
		}
		else if(shmptr->status == 3)
		{
			printf("\nMatch Draw!\n");
			exit(0);
		}
	}
}

void checkStatusP2(tictactoe *shmptr)
{
	if(shmptr->count)
	{
		printf("\nWaiting for opponent\n");
	}
	while(1)
	{
		sleep(1);
		if(shmptr->status == 1)
		{
			return;
		}
		else if(shmptr->status == 0)
		{
			printf("\nP2 is the winner!\n");
			exit(0);
		}
		else if(shmptr->status == 3)
		{
			printf("\nMatch Draw!\n");
			exit(0);
		}
	}
}
