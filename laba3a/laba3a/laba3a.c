
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
char* readln();
int main()
{
	char sym[3] = { '\t', ' ', '\0' };
	char* stringus;
	char* a;
	
	while (1)
	{
		
		a = readln();
		if (a == NULL) break;
		//printf(a);
		//printf("%c", a[0]);
		int dlin = strlen(a);
		stringus = (char*)malloc(2*dlin * sizeof(char*));
		stringus[0] = '\0';
		//printf("%d", dlin);
		//int len = strspn(&a[0], sym);
		for (int i = 0; i < dlin - 1; i++) {
			int len = strspn(&a[i], sym);
			if (len == 0) {
				if ((i != dlin - 1) && (a[i] == a[i + 1])) {
					
						strncat(stringus, &a[i], 1);
						if (a[i+1] != a[i + 2]) {
							strncat(stringus, &a[i+1], 1);
							strcat(stringus, " ");
						}


					
					
				}
			}
			
			
		}
		
		//stringus[strlen(stringus)] = '\0';
		//printf('"');
		printf(stringus);
		printf("%c",'!');
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
