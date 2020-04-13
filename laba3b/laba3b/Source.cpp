#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
//char* readln();

typedef struct list
{
	int field; // поле данных
	struct list* next; // указатель на следующий элемент

}list;

int main() {
	list* Head = (list*)malloc(sizeof(list));
	list* cur_ptr= Head;
	
	cur_ptr->next = (list*)malloc(sizeof(list));
	cur_ptr = cur_ptr->next;
	cur_ptr->next = NULL;
	int n;
	scanf("%d", &n);
	cur_ptr->field = n;
	
	printf("%d", cur_ptr->field);
	





	return 0;
}

