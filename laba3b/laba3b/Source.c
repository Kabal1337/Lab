#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node
{
	struct Node* next_ptr;
	char data;
} Node;

Node* readln();
Node* push_back(Node* ptr, char data);
void algor(Node* ptr);
void writeln(Node* Head);
void free_list(Node* ptr);
Node* fun(Node* ptr);
Node* del(Node* cur_ptr);
Node* delone(Node* Head, Node* ptr);
void Prob(Node* ptr);
int main()
{
	Node* Head;

	do
	{
		Head = readln();
		
		if (Head->next_ptr == NULL) break;
		Prob(Head);
		writeln(Head);
		Node* cur_ptr = Head->next_ptr;
		//printf("%d", cur_ptr->data);
		algor(Head);
		writeln(Head);
		//print("%d", Head->next_ptr->data);
		free_list(Head);

	} while (Head->next_ptr != NULL);

	return 0;
}

Node* push_back(Node* ptr, char data)
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
	char n = 0;	Node* Head = (Node*)malloc(sizeof(Node));
	Head->next_ptr = NULL;

	Node* cur_ptr = Head;
	//cur_ptr->next_ptr = NULL;
	char buf[2];
	  
	do {

		n = scanf("%1[^\n]d", buf);

		if (n == 0)
		{
			scanf("%*c");
			break;
		}
		else
		{
			int m = *buf;
			if((m>47) && (m<58) || (m==32))
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

void algor(Node* ptr) {
	Node* cur_ptr = ptr;

		while (cur_ptr->next_ptr != NULL)  {
			
				if ((cur_ptr->next_ptr->data != ' ') && (cur_ptr->next_ptr->data != '\t')) { 
					cur_ptr = fun(cur_ptr);
					
				}
				else { cur_ptr = cur_ptr->next_ptr; 
			
				}

		}
		if (cur_ptr->data == ' ') cur_ptr = delone(ptr, cur_ptr);
			
			
		
}
	

	Node* fun(Node* ptr)
	{
		Node* cur_ptr=ptr;
		int chis;
		Node* first = cur_ptr;
		 cur_ptr = cur_ptr->next_ptr;
		//cur_ptr = cur_ptr->next_ptr;
		while (1) {
			if ((cur_ptr->data == ' ') || (cur_ptr->next_ptr == NULL)) break;
			chis = cur_ptr->data;
			if (chis% 2 != 0) {
				cur_ptr = first;
				cur_ptr=del(cur_ptr);
				break;
			
			}
			else cur_ptr = cur_ptr->next_ptr;
		}
		if (cur_ptr->next_ptr == NULL) {
			chis = cur_ptr->data;
			if (chis % 2 != 0) {
				cur_ptr = first;
				cur_ptr = del(cur_ptr);
				

			}
		}
		return cur_ptr;
	}
	
	Node* del(Node* ptr) {
		Node* one_ptr = ptr;
		Node* cur_ptr=ptr;

		cur_ptr = cur_ptr->next_ptr;
		Node* prev_ptr;
		
		while ((cur_ptr->data != ' ') && (cur_ptr->next_ptr != NULL))
		{
			prev_ptr = cur_ptr;
			cur_ptr = cur_ptr->next_ptr;
			free(prev_ptr);
			
			
			//if ((cur_ptr->next_ptr->data == ' ') || (cur_ptr->next_ptr->data == '\t') || (cur_ptr->next_ptr == NULL)) break;
		}
		one_ptr->next_ptr = cur_ptr->next_ptr;
		free(cur_ptr);
		return one_ptr;
	}

	Node* delone(Node* Head, Node* ptr) {
		Node* cur_ptr = Head;

		while (cur_ptr->next_ptr != ptr)
		{
			cur_ptr = cur_ptr->next_ptr;
		}

		cur_ptr->next_ptr = ptr->next_ptr;
		free(ptr);

		return cur_ptr->next_ptr;
	}
	void Prob(Node* ptr) {
		Node* cur_ptr = ptr;
		int prev_space = 1;
		cur_ptr = cur_ptr->next_ptr;
		while (cur_ptr->next_ptr != NULL) {
			if (cur_ptr->data != ' ') 
				prev_space = 0;
			if (cur_ptr->data == ' ') {
				if (prev_space == 1) cur_ptr = delone(ptr, cur_ptr);
				else { 
					cur_ptr = cur_ptr->next_ptr;
					prev_space = 1;
				}
			}
			else cur_ptr = cur_ptr->next_ptr;
			

		}
		if (cur_ptr->data == ' ') cur_ptr = delone(ptr, cur_ptr);
	
	
	
	}