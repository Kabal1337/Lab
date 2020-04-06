// laba3a.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
char* readln();
int main()
{
	char* a;
	do 
	{
		char* stringus;
		a = readln();
		//printf(a);
		//printf("%c", a[0]);
		int dlin= strlen(a);
		int len=0;
		stringus = (char*)malloc(2*dlin *sizeof(char));
		//printf("%d", dlin);
		int j = 0;
		for (int i = 0; i < dlin-1; i++) {
			if (a[i] = a[i + 1]) 
			{
				
				stringus[j] = a[i];
				j++;  
				
			}
			if ((a[i] != a[i + 1]) && (a[i] = a[i-1])) {
				stringus[j] = a[i];
				stringus[j + 1] = ' ';
				j += 2;
			}
		}
		
		
		stringus[j] = '\0';
		
		printf(stringus);
	} 
	while (a != NULL);
}



char* readln() {
	char* ptr = (char*)malloc(1);
	*ptr = '\0';
	char buf[81];
	int n, len = 0;
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			free(ptr);
			ptr = NULL;
			continue;
		}
		if (n == 0)
			scanf("%*c");
		else {
			len += strlen(buf);
			ptr = (char*)realloc(ptr, len + 1);
			strcat(ptr, buf);
		}
	} while (n > 0);
	return ptr;
}