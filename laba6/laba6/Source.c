#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node
{
	
	struct Link* connect;
	char* name;
	struct Node* next;
	
} Node;

typedef struct Graf
{
	struct Node* Head;

} Graf;
typedef struct Link
{
	struct Node* link;
	int weight;

} Link;
void add_Node(Graf* graf, char* name);
char* readln(void);
void read_info(Graf* graf);
void add_link(char* name, char* link, Graf* graf);
int main()
{
	Graf* graf = (Graf*)malloc(sizeof(Graf));
	
	graf->Head = NULL;
	
	int num_of_command;

	char* name;

	while (1)
	{
		num_of_command = -1;
		printf("List of commands:\n1. Add New Node \n2. Read All \n3. Add Link\n4. Find Element\n5. Find Element with max key\n6. Draw Tree\n7. Quit\nChoice: ");


		scanf("%d", &num_of_command);
		getchar();
		printf("\n");

		switch (num_of_command)
		{
		case 1:
			printf("Name: ");
			name = readln();
			add_Node(graf, name);






			break;
		case 2:
			read_info(graf);
			
			break;
		case 3:
			
			printf("Enter Node name: ");
			char* name=readln();
			printf("Enter Node name to link: ");
			char* link = readln();
			add_link(name, link, graf);

			break;
		case 4:

			break;
		case 5:


			break;
		case 6:

		case 7:
			
			return 0;
		default:
			printf("There is no such command \n\n");
			break;
		}

		//return 0;
	}
}



char* readln(void)
{
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

	if (ptr == NULL) ptr = "";

	return ptr;
}
void add_Node(Graf* graf, char* name) {
	Graf* a_graf = graf;
	if (graf->Head == NULL) {
		a_graf->Head = (Node*)malloc(sizeof(Node));
		a_graf->Head->next = NULL;
		a_graf->Head->connect= (Link*)malloc(sizeof(Link));
		a_graf->Head->connect->link = NULL;
		a_graf->Head->connect->weight = NULL;
		a_graf->Head->name = name;
		return;
	}
	
	Node* cur_ptr = a_graf->Head;
 	
	while (cur_ptr->next != NULL) cur_ptr = cur_ptr->next;
	
	Node* new_ptr = (Node*)malloc(sizeof(Node));
	cur_ptr->next = new_ptr;
	cur_ptr = cur_ptr->next;
	cur_ptr->connect= (Link*)malloc(sizeof(Link));
	cur_ptr->name = name;
	cur_ptr->next = NULL;
	Link* cur_link = cur_ptr->connect;
	cur_link->link = NULL;
	cur_link->weight = NULL;
	
	
	

}
void read_info(Graf* graf) {
	Graf* a_graf = graf;
	Node* cur_ptr = a_graf->Head;

	while (cur_ptr->next != NULL)
	{
		printf("Key: ");
		printf(cur_ptr->name);

		printf("\n");
		cur_ptr = cur_ptr->next;

	}
	printf("Key: ");
	printf(cur_ptr->name);

	printf("\n");
}
void add_link(char* name, char* link, Graf* graf)
{
	Graf* a_graf = graf;
	Node* cur_ptr = a_graf->Head;
	Node* need_node=NULL;
	Node* need_link=NULL;
	while (cur_ptr->next!=NULL) {
		if (cur_ptr->name == name) {
			printf("pipka");
			need_node = cur_ptr;
		}
		if (cur_ptr->name == link) {
			printf("pipka");
			need_link = cur_ptr;
		}
		if ((need_link != NULL) && (need_node != NULL)) break;
		cur_ptr = cur_ptr->next;
	}
	if (cur_ptr->name == name) {
		printf("pipka");
		need_node = cur_ptr;
	}
	if (cur_ptr->name == link) {
		printf("pipka");
		need_link = cur_ptr;
	}
	if ((need_link != NULL) && (need_node != NULL))
		need_node->connect->link = need_link;
	else
		printf("No such Nodes");
}