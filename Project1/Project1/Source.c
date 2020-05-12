#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node
{
	struct Node* next_ptr;
	int data;
} Node;

//Node* readln();
//Node* push_back(Node* ptr, int data);

//void writeln(Node* Head);
//void free_list(Node* ptr);

int main()
{
	Node* cur_ptr;
	Node* Head = (Node*)malloc(sizeof(Node));
	cur_ptr = Head;
	cur_ptr->next_ptr = NULL;
	scanf("%d", &cur_ptr->data);
	printf("%d", cur_ptr->data);

}
