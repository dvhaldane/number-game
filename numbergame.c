#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
NAME: NumberGame
AUTHOR: David Haldane (VERHAL1)
DATE 10/10/2017

COMMENT: Number game of 2 players vs computer.  Semester project for CSC 389
*/

bool playerOnePassedLast = false;
int playerOnePassCount = 0;
bool playerOnePassLockout = false;
bool playerTwoPassedLast = false;
int playerTwoPassCount = 0;
bool playerTwoPassLockout = false;
int passLimit = 3;


bool passLockHandler(int player)
{

	int passIncrement;

	if (player == 1 && playerOnePassedLast && !playerOnePassLockout)
	{
		playerOnePassLockout = true;
	}
	else if (player == 2 && playerTwoPassedLast && !playerTwoPassLockout)
	{
		playerTwoPassLockout = true;
	}
	else if (player == 1 && playerOnePassedLast && playerOnePassLockout)
	{
		playerOnePassLockout = false;
		playerOnePassedLast = false;
	}
	else if (player == 2 && playerTwoPassedLast && playerTwoPassLockout)
	{
		playerTwoPassLockout = false;
		playerTwoPassedLast = false;
	}
}

void changePlayer(int *player)
{
	if (*player == 1)
	{
		*player = 2;
	}
	else
	{
		*player = 1;
	}

	passLockHandler(*player);
}

int charToInteger(char c)
{
	return (int)c - 48;
}

bool checkNumericAndLength(char input[20], int lengthLimit)
{
	for (int i = 0; i < strlen(input) - 1; i++)
	{
		if (!isdigit(input[i]))
		{
			printf("Invalid input.\n");
			return false;
		}
	}

	if (strlen(input) - 1 <= lengthLimit)
	{
		return true;
	}

	printf("Invalid input. Input length greater than %d\n", lengthLimit);
	return false;

}

bool performPass(int player)
{
	int turnsleft = 0;

	if (player == 1)
	{
		if (playerOnePassedLast)
		{
			printf("You cannot pass two turns in a row.\n");
			return false;
		}
		else
		{
			if (playerOnePassCount < 3)
			{
				playerOnePassCount = playerOnePassCount + 1;
				turnsleft = passLimit - playerOnePassCount;
				printf("You have passed %d number of times, you have %d more times left\n", playerOnePassCount, turnsleft);
				playerOnePassedLast = true;
				return true;
			}
			else
			{
				printf("You have reached the maximum number of passes (3)\n");
				return false;
			}
		}
	}
	else
	{
		if (playerTwoPassedLast)
		{
			printf("You cannot pass two turns in a row.\n");
			return false;
		}
		else
		{
			if (playerTwoPassCount < 3)
			{
				playerTwoPassCount = playerTwoPassCount + 1;
				turnsleft = passLimit - playerTwoPassCount;
				printf("You have passed %d number of times, you have %d more times left\n", playerTwoPassCount, turnsleft);
				playerTwoPassedLast = true;
				return true;
			}
			else
			{
				printf("You have reached the maximum number of passes (3)\n");
				return false;
			}
		}
	}

	return false;
}

void printHeader() {
	printf("#####################\n");
	printf("## The Number Game ##\n");
	printf("#####################\n");
}

void main() {

	srand(time(NULL));
	int currentPlayer = rand() % 2 + 1;
	bool runGame = true;
	char passString[] = "PASS\n";
	char playerGuessString[20];
	char playerNumberEntry[20];
	int playerNumberInteger = 0;
	int targetNumber = rand() % 999 + 1;


	printHeader();

	while (playerNumberInteger != currentPlayer)
	{

		printf("Player Number (1 or 2): ");
		fgets(playerNumberEntry, 20, stdin);

		if (checkNumericAndLength(playerNumberEntry, 1))
		{
			playerNumberInteger = charToInteger(playerNumberEntry[0]);

			if (playerNumberInteger != currentPlayer)
			{
				printf("You have to wait your turn.\n");
			}
		}

	}

	while (runGame)
	{
		printf("Player %d's guess (0-999 or PASS): ", currentPlayer);
		fgets(playerGuessString, 20, stdin);

		//Pass
		if (strcmp(playerGuessString, passString) == 0)
		{
			if (performPass(currentPlayer))
			{
				changePlayer(&currentPlayer);
			}
		}
		else if (checkNumericAndLength(playerGuessString, 3))
		{
			if (atoi(playerGuessString) < targetNumber)
			{
				printf("Guess is less than the target number.\n");
				changePlayer(&currentPlayer);
			}
			else if (atoi(playerGuessString) > targetNumber)
			{
				printf("Guess is greater than the target number.\n");
				changePlayer(&currentPlayer);
			}
			else
			{
				printf("Player %d guessed the correct number! %d!\n", currentPlayer, targetNumber);
				runGame = false;
			}
		}

	}
	printf("Thanks for playing!\n");
}

