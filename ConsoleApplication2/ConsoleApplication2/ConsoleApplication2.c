#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>



int main()
{
	int x = -42;
	int length = snprintf(NULL, 0, "%d", x);
	char* str = malloc(length + 1);
	snprintf(str, length + 1, "%d", x);
	printf(str);
}

