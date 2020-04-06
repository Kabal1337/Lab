#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* readln(void);
int line_length(char* start);

int main()
{
	int flen, fi, len;
	char* word;
	char* fin_word;

	while (1)
	{
		word = readln();
		if (word == NULL) break;

		fin_word = (char*)malloc(strlen(word) * sizeof(char*));
		fin_word[0] = 0;

		for (int i = 0; i < strlen(word); i++)
		{
			if (word[i] != '\0' && word[i] != '\t' && word[i] != ' ')
			{
				flen = line_length(&word[i]);
				break;
			}
		}

		for (int i = 0; i < strlen(word); i++)
		{
			if (word[i] != '\0' && word[i] != '\t' && word[i] != ' ')
			{
				len = line_length(&word[i]);
				if (flen == len)
				{
					strncat(fin_word, &word[i], flen);
					strcat(fin_word, " ");
				}
				i += len;
			}
		}
		printf(fin_word);
		printf("\n");

		free(fin_word);
		free(word);
	}

	//system("pause");
	return 0;
}

int line_length(char* start)
{
	int i = 0, len = 0;
	while (start[i] != '\0' && start[i] != '\t' && start[i] != ' ')
	{
		len++;
		i++;
	}
	return len;
}

char* readln(void) {
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
	return ptr;
}

