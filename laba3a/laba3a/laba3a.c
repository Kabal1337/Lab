// laba3a.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
char* readln();
int main()
{
	char* stringus;
	char* a;
	while (1)
	{	
		
		a = readln();
		if (a == NULL) break;
		//printf(a);
		//printf("%c", a[0]);
		int dlin= strlen(a);
		
		stringus = (char*)malloc(2*dlin *sizeof(char*));
		//printf("%d", dlin);
		int j = 0;
		for (int i = 0; i < dlin-1; i++) {
			if ((a[i] == a[i + 1]) && (a[i] != ' ')) 
			{
				
				stringus[j] = a[i];
				j++;  
				if ((i == dlin - 2) && (a[i+1] != ' ')) {
					stringus[j] = a[i + 1];
					j++;
				}
			
			}
			if ((a[i] != a[i + 1]) && (a[i] == a[i-1]) && (a[i] != ' ')) {
				stringus[j] = a[i];
				stringus[j + 1] = ' ';
				j += 2;
			}
		}
		
		
		stringus[j] = '\0';
		
		printf(stringus);
		printf("\n");
		free(stringus);
		free(a);
	} 
	
	return 0;
}



char* readln(void) {
	char* ptr = (char*)malloc(1 * sizeof(char*));
	*ptr = NULL;
	char buf[20];
	int n, len = 0;
	do {
		n = scanf("%19[^\n]", buf);

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
	return ptr;
}

