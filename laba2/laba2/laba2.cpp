#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
int main()
{   
	int a;
	scanf("%d", &a);
}

int* Enter(int chis){
	char answer[256];
	fgets(answer, sizeof(answer), stdin);
	while ((scanf(answer, "%d", &chis) != 1)) {
		printf("Некоректный ввод, введите еще раз: "); // выводим сообщение об ошибке
		fgets(answer, sizeof(answer), stdin); // и заново считываем строку
	}
}