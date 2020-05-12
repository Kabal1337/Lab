#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node
{
	struct Node* next_ptr;
	int data;
} Node;

Node* readln();
Node* push_back(Node* ptr, int data);

void writeln(Node* Head);
void free_list(Node* ptr);

int main()
{
	Node* Head;

	do
	{
		Head = readln();
		if (Head->next_ptr == NULL) break;
		Node* cur_ptr = Head->next_ptr;
		printf("%d", cur_ptr->data);

		writeln(Head);
		//print("%d", Head->next_ptr->data);
		free_list(Head);

	} while (Head->next_ptr != NULL);

	return 0;
}

Node* push_back(Node* ptr, int data)
{
	while (ptr->next_ptr != NULL)
	{
		ptr = ptr->next_ptr;
	}

	ptr->next_ptr = (Node*)malloc(sizeof(Node));
	ptr = ptr->next_ptr;
	ptr->data = data;
	ptr->next_ptr = NULL;

	return ptr;
}

Node* readln()
{
	int n = 0;
	Node* Head = (Node*)malloc(sizeof(Node));
	Head->next_ptr = NULL;

	Node* cur_ptr = Head;

	int buf[2];

	do {
		n = scanf("%1[^\n]d", buf);

		if (n == 0)
		{
			scanf("%*c");
			break;
		}
		else
		{
			cur_ptr = push_back(cur_ptr, *buf);
		}

	} while (n > 0);

	return Head;
}

void writeln(Node* Head)
{
	Node* cur_ptr = Head->next_ptr;

	printf("'");
	if (cur_ptr != NULL)
	{
		while (cur_ptr->next_ptr != NULL)
		{
			printf("%c", cur_ptr->data);
			cur_ptr = cur_ptr->next_ptr;
		}

		printf("%c", cur_ptr->data);

	}

	printf("'");

	printf("\n");
}

void free_list(Node* ptr)
{
	Node* t_ptr;
	while (1)
	{
		t_ptr = ptr;

		if (ptr->next_ptr != NULL)
		{
			ptr = ptr->next_ptr;
			free(t_ptr);
		}
		else
		{
			free(t_ptr);
			break;
		}
	}
}