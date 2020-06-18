#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define SIZE 10

//char get_rand();

int main()
{
	srand(time(NULL));
	int** matrix = (char**)malloc(sizeof(char*) * SIZE);
	for (int i = 0; i < SIZE; i++)
	{
		matrix[i] = (int*)malloc(sizeof(char) * SIZE);
	}


	FILE* file;
	file = fopen("C:/Users/thetruemox/source/repos/laba6/laba6/graph.txt", "w+t");

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{

			matrix[i][j] = rand() % 1000;


		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			fprintf(file, "%c", matrix[i][j]);
		}
	}


	return 0;
}

