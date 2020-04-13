#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
//char* readln();

typedef struct list
{
	char field; // поле данных
	struct list* next; // указатель на следующий элемент

}list;
list* push_back(list* ptr, int data);
int main() {
	list* Head = (list*)malloc(sizeof(list));
	list* cur_ptr = Head;
	

	






	return 0;
}

list* push_back(list* ptr) 
{	
	ptr->next = (list*)malloc(sizeof(list));
	ptr = ptr->next;
	ptr->next = NULL;
	int n;
	scanf("%d", &n);
	ptr->field = n;

	return ptr;

}