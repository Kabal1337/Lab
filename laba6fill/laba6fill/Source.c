#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define SIZE 10
//int find_size(FILE* file_nodes);
//char* f_readln(FILE* file);
char* readln(void);
int main()
{
	
	FILE* file_nodes;
	FILE* file_graf;
	file_graf = fopen("C:/Users/Борис/source/repos/laba6/laba6/graph", "wb");
	file_nodes = fopen("C:/Users/Борис/source/repos/laba6/laba6/nodes.txt", "w+t");
	int size;
	scanf("%d", &size);
	for (int i = 0; i < size; i++)
	{
		
			fprintf(file_nodes, "%d", i);
			fprintf(file_nodes, "\n");
	}
	fclose(file_nodes);
	if (file_nodes != NULL) {
		//int size = find_size(file_nodes);
		//printf("%d", size);
		srand(time(NULL));
		int** matrix = (int**)malloc(sizeof(int*) * size);
		for (int i = 0; i < size; i++)
		{
			matrix[i] = (int*)malloc(sizeof(int) * size);
		}

		//file = fopen("C:/Users/Борис/source/repos/laba6/laba6/graph.txt", "w+t");
		//char* file_name = readln();

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				char chis = rand() % 100;
				matrix[i][j] = rand() % 100;;


			}
		}

		for (int i = 0; i < size; i++)
		{



			//fseek(file, 0, 2);
			fwrite(matrix[i], sizeof(int), size, file_graf);




		}
		
		fclose(file_graf);
	}
	else {
		
		printf("No such files");
	}
	
	return 0;
}

char* readln(void)
{
	char* ptr = (char*)malloc(1 * sizeof(char*));
	*ptr = NULL;
	char buf[10];
	int n, len = 0;
	do {
		n = scanf("%9[^\n]", buf);

		if (n == 0)
			scanf("%*c");
		else
		{
			len = len + strlen(buf) + 1;
			ptr = (char*)realloc(ptr, len);
			strcat(ptr, buf);
		}

	} while (n > 0);
	if (ptr[0] == '\0') ptr = NULL;

	if (ptr == NULL) ptr = "";

	return ptr;
}
/*int find_size(FILE* file_nodes) {
	
		int i = 0;
		char* m;
		while (1) {
			
			m = f_readln(file_nodes);
			if (m == NULL) break;
			i++;
		}
		return i;
	
}
*/
/*char* f_readln(FILE* file)
{

	char* ptr = (char*)malloc(1 * sizeof(char*));
	*ptr = NULL;
	char buf[10];
	int n, len = 0;
	do {
		n = fscanf(file, "%9[^\n]", buf);
		if (n == -1)
		{
			return NULL;
		}
		if (n == 0)
			fscanf(file, "%*c");
		else
		{
			len = len + strlen(buf) + 1;
			ptr = (char*)realloc(ptr, len);
			strcat(ptr, buf);
		}

	} while (n > 0);
	if (ptr[0] == '\0') ptr = NULL;

	return ptr;
}
*/