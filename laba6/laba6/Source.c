#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define SIZE 10
typedef struct Node
{
	
	struct Link* connect;
	char* name;
	struct Node* next;
	
} Node;

typedef struct Graf
{
	struct Node* Head;
	int size;
} Graf;
typedef struct Link
{
	struct Node* link;
	int weight;
	struct Link* next;
} Link;
char* f_readln(FILE* file);
int** f_read(FILE* file, int size);
//int f_readln(FILE* file, int i, int j);
void readmatrix(int** matrix, int size);
void add_Node(Graf* graf, char* name);
char* readln(void);
void read_info(Graf* graf);
void add_link(char* name, char* link, Graf* graf, int weight);
int find_size(FILE* file_nodes, Graf* graf);
void file_fill(Graf* graph);
//void add_link_file(int** matrix, Graf* graf, int size);
//void del(Node* ptr, Node* first_ptr);
//void f_read()
//void f_add_Node(int size, FILE* file_node, FILE* file_graf, char* name, int** mat);
int find_index(Graf* graph, Node* ptr);
Node* find_node(Graf* graf, int index);
void del_Node(Graf* graf, char* name);
void show_link(Graf* graf, char* name);
void find_max_weight(Graf* graf);
int main()
{
	Graf* graf = (Graf*)malloc(sizeof(Graf));
	
	graf->Head = NULL;
	
	int num_of_command;
	
	char* name;
	FILE* file_graf;
	FILE* file_nodes;
	//printf("Type file name: ");
	//char* file_name = readln();
	printf("\nTrying to open a file\n");
	file_graf = fopen("graph", "r+b");
	file_nodes = fopen("nodes.txt", "r+t");
	int size = find_size(file_nodes, graf);
	graf->size = size;
	int** m=0;
	printf("%d", size);
	//int kop = f_readln(file, 0, 0);
	//printf("%d", kop);
	if (file_nodes == NULL) {
		printf("File with nodes not found");
		return;
	}
	if (file_graf == NULL)
	{
		file_graf = fopen("graph", "ab");
		
		printf("File not found\n\n");
	}
	else
	{
		printf("File was found, keep working\n\n");
		m = f_read(file_graf, size);
		readmatrix(m, size);
		//int** matrix = f_read;
		int* line;
		Node* parent_ptr, * child_ptr;

		for (int i = 0; i < size; i++)
		{
			line = m[i];
			parent_ptr = find_node(graf, i);

			for (int j = 0; j < size; j++)
			{
				if (line[j] != 0)
				{
					child_ptr = find_node(graf, j);
					add_link(parent_ptr->name, child_ptr->name,graf, line[j]);
				}
			}
		}
		fclose(file_graf);
	
	}
	//file_graf = fopen("graph", "r+b");
	

	

	
	while (1)
	{
		num_of_command = -1;
		printf("List of commands:\n1. Add New Node \n2. Read All \n3. Add Link\n4. Find Element\n5.Delete Node\n6. Find Max Weight\n7. Quit\nChoice: ");


		scanf("%d", &num_of_command);
		getchar();
		printf("\n");

		switch (num_of_command)
		{
		case 1:
			printf("Name: ");
			name = readln();
			add_Node(graf, name);
			//f_add_Node(size, file_nodes, file_graf, name, m);
			file_fill(graf);




			break;
		case 2:
			read_info(graf);
			
			break;
		case 3:
			
			printf("Enter Node name: \n");
			char* name=readln();
			printf("Enter Node name to link: \n");
			char* link = readln();
			printf("Enter weight of link: \n");
			int weight;
			scanf("%d", &weight);
			add_link(name, link, graf, weight);
			
			break;
		case 4:
			name = readln();
			show_link(graf, name);
			break;
		case 5:
			printf("Enter Node name: ");
			name = readln();
			del_Node(graf, name);

			break;
		case 6:
			find_max_weight(graf);
			break;
		case 7:
			fclose(file_graf);
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
		a_graf->Head->connect = NULL;
		//a_graf->Head->connect= (Link*)malloc(sizeof(Link));
		//a_graf->Head->connect->next = NULL;
		//a_graf->Head->connect->link = NULL;
		//a_graf->Head->connect->weight = NULL;
		a_graf->Head->name = name;
		
		return;
	}
	else {
		Node* cur_ptr = a_graf->Head;

		while (cur_ptr->next != NULL) cur_ptr = cur_ptr->next;

		Node* new_ptr = (Node*)malloc(sizeof(Node));
		cur_ptr->next = new_ptr;
		cur_ptr = cur_ptr->next;
		//cur_ptr->connect= (Link*)malloc(sizeof(Link));
		cur_ptr->name = name;
		cur_ptr->connect = NULL;
		cur_ptr->next = NULL;
		//cur_ptr->next = NULL;
		//Link* cur_link = cur_ptr->connect;
		//cur_link->link = NULL;
		//cur_link->weight = NULL;
		
	}
	graf->size++;
	

}



void read_info(Graf* graf) {
	Graf* a_graf = graf;
	Node* cur_ptr = a_graf->Head;
	if (cur_ptr != NULL) {
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
	else printf("Empty\n");
}

void add_link(char* name, char* link, Graf* graf, int weight)
{
	Graf* a_graf = graf;
	Node* cur_ptr = a_graf->Head;
	Node* need_node=NULL;
	Node* need_link=NULL;
	while (cur_ptr->next!=NULL) {
		if (strcmp(cur_ptr->name, name)==0) {
			
			need_node = cur_ptr;
		}
		if (strcmp(cur_ptr->name, link)==0) {
			
			need_link = cur_ptr;
		}
		if ((need_link != NULL) && (need_node != NULL)) break;
		cur_ptr = cur_ptr->next;
	}
	if (strcmp(cur_ptr->name, name)==0) {
		
		need_node = cur_ptr;
	}
	if (strcmp(cur_ptr->name, link)==0) {
		
		need_link = cur_ptr;
	}
	
	if ((need_link != NULL) && (need_node != NULL)) {
		
		if (need_node->connect == NULL) {
			need_node->connect = (Link*)malloc(sizeof(Link));
			need_node->connect->link = need_link;
			need_node->connect->weight = weight;
			need_node->connect->next = NULL;
		}
		else {
			Link* cur_link = need_node->connect;
			while (cur_link->next != NULL) cur_link = cur_link->next;
			cur_link->next= (Link*)malloc(sizeof(Link));
			cur_link = cur_link->next;
			cur_link->link = need_link;
			cur_link->weight = weight;
			cur_link->next = NULL;
		}
	}	
	else
		printf("No such Nodes");
	
}

void del_Node(Graf* graf, char* name) 
{
	Node* cur_ptr = graf->Head;
	while (cur_ptr->next != NULL) {
		
			Link* cur_link = cur_ptr->connect;
			if (strcmp(cur_ptr->name, name) == 0) { // обработка вершины с подходящим именем
				if (cur_ptr->connect != NULL) {
					Link* first = cur_link;
					if (first->next == NULL) {

						cur_ptr->connect = NULL;
					}
					else {
						cur_link = cur_link->next;
						while (cur_link->next != NULL)
						{
							first->next = cur_link->next;
							free(cur_link);
							cur_link = first->next;
						}
						first->next = cur_link->next;
						free(cur_link);
						cur_ptr->connect = NULL;
					}
				}
				
			}
			else { //неподходящее имя
				if (cur_ptr->connect != NULL) { //есть ли связи
					Link* first = cur_link;
					while (cur_link->next != NULL)
					{
						if (strcmp(cur_link->link->name, name) == 0) {
							if (first->next == NULL) {
								
								free(cur_ptr->connect);
								cur_ptr->connect = NULL;

							}
							else {

								if (strcmp(first->link->name, name) == 0) {
									cur_ptr->connect = first->next;
									free(first);
									first = cur_ptr->connect;
									cur_link = first;
								}
								else {
									Link* ptr = first;
									while (ptr->next != cur_link) ptr = ptr->next;
									ptr->next = cur_link->next;
									free(cur_link);
									cur_link = ptr->next;
								}
							}
						}
						if (cur_link->next != NULL)
							cur_link = cur_link->next;
					}
					if (strcmp(cur_link->link->name, name) == 0) {
						if (first->next == NULL) {
							free(cur_ptr->connect);
							cur_ptr->connect = NULL;

						}
						else {
							if (strcmp(first->link->name, name) == 0) {
								cur_ptr->connect = first->next;
								free(first);
								first = cur_ptr->connect;
								cur_link = first;
							}
							else {
								Link* ptr = first;
								while (ptr->next != cur_link) ptr = ptr->next;
								ptr->next = cur_link->next;
								free(cur_link);
								cur_link = ptr->next;
							}
						}
					}
				}
			}
		
		if(cur_ptr->next!=NULL)
		cur_ptr = cur_ptr->next;
	}
	
		Link* cur_link = cur_ptr->connect;
		if (strcmp(cur_ptr->name, name) == 0) {
			if (cur_ptr->connect != NULL) {
				Link* first = cur_link;
				if (first->next == NULL) {

					free(cur_ptr->connect);
					cur_ptr->connect = NULL;
				}
				else {
					cur_link = cur_link->next;
					while (cur_link->next != NULL)
					{
						first->next = cur_link->next;
						free(cur_link);
						cur_link = first->next;
					}
					first->next = cur_link->next;
					free(cur_link);
					cur_ptr->connect = NULL;
				}
			}
		}
		else {
			if (cur_ptr->connect != NULL) {
				Link* first = cur_link;
				while (cur_link->next != NULL)
				{
					if (strcmp(cur_link->link->name, name) == 0) {
						if (strcmp(first->link->name, name) == 0) {
							cur_ptr->connect = first->next;
							free(first);
							first = cur_ptr->connect;
							cur_link = first;
						}
						else {
							Link* ptr = first;
							while (ptr->next != cur_link) ptr = ptr->next;
							ptr->next = cur_link->next;
							free(cur_link);
							cur_link = ptr->next;
						}
					}
					cur_link = cur_link->next;
				}
				if (strcmp(cur_link->link->name, name) == 0) {
					if (strcmp(first->link->name, name) == 0) {
						cur_ptr->connect = first->next;
						free(first);
						first = cur_ptr->connect;
						cur_link = first;
					}
					else {
						Link* ptr = first;
						while (ptr->next != cur_link) ptr = ptr->next;
						ptr->next = cur_link->next;
						free(cur_link);
						cur_link = ptr->next;
					}
				}
			}
		}
		cur_ptr = graf->Head;
		while (cur_ptr->next != NULL) {
			if (strcmp(cur_ptr->name, name) == 0) {
				if (cur_ptr->name = graf->Head->name) {
					graf->Head = cur_ptr->next;
					free(cur_ptr);
					cur_ptr = graf->Head;
				}
				else {
					Node* ptr = graf->Head;
					while (ptr->next != cur_ptr) ptr = ptr->next;
					ptr->next = cur_ptr->next;
					free(cur_ptr);
					cur_ptr = ptr->next;
				}
			}
			
			cur_ptr = cur_ptr->next;
		}
		
		if (strcmp(cur_ptr->name, name) == 0) {
			if (cur_ptr->name = graf->Head->name) {
				graf->Head = cur_ptr->next;
				free(cur_ptr);
				cur_ptr = graf->Head;
			}
			else {
				Node* ptr = graf->Head;
				while (ptr->next != cur_ptr) ptr = ptr->next;
				ptr->next = cur_ptr->next;
				free(cur_ptr);
				cur_ptr = ptr->next;
			}
		}
}



void show_link(Graf* graf, char* name) {
	Graf* a_graf = graf;
	Node* cur_ptr = graf->Head;
	
	while (cur_ptr->next != NULL) {
		if (strcmp(cur_ptr->name, name)==0) {
			Link* cur_link = cur_ptr->connect;
			if (cur_link != NULL) {
				printf("All links: \n");
				while (cur_link->next != NULL)
				{


					printf(cur_link->link->name);
					printf(" ");
					printf("%d", cur_link->weight);
					printf("\n");
					cur_link = cur_link->next;
				}

				printf(cur_link->link->name);
				printf(" ");
				printf("%d", cur_link->weight);
				printf("\n");
				
				return;
			}
			else
				printf("No Links\n");
			//printf(cur_link->name);
			
		}
		cur_ptr = cur_ptr->next;
	}
	if (strcmp(cur_ptr->name, name) == 0) {
		Link* cur_link = cur_ptr->connect;
		if (cur_link != NULL) {
			printf("All links: ");
			while (cur_link->next != NULL)
			{



				printf(cur_link->link->name);
				printf(" ");
				printf("%d", cur_link->weight);
				printf("\n");
				cur_link = cur_link->next;
			}

			printf(cur_link->link->name);
			printf(" ");
			printf("%d", cur_link->weight);
			printf("\n");
			return;
		}
		else
			printf("No Links\n");
		//printf(cur_link->name);

	}
}
void find_max_weight(Graf* graf) {
	Node* cur_ptr = graf->Head;
	Link* max_link=NULL;
	Node* max_ptr=NULL;
	if(cur_ptr!=NULL)
	while (cur_ptr->next != NULL) {
		if (cur_ptr->connect != NULL) {
			Link* cur_link = cur_ptr->connect;
			while (cur_link->next != NULL) {
				if (max_link == NULL) {
					max_link = cur_link;
					max_ptr = cur_ptr;
				}
				else 
				if (cur_link->weight > max_link->weight) {
					max_link = cur_link;
					max_ptr = cur_ptr;
				}
				cur_link = cur_link->next;

			}
			if (max_link == NULL) {
				max_link = cur_link;
				max_ptr = cur_ptr;
			}
			else
				if (cur_link->weight > max_link->weight) {
					max_link = cur_link;
					max_ptr = cur_ptr;
				}
		}
		cur_ptr = cur_ptr->next;
	}
	if (cur_ptr->connect != NULL) {
		Link* cur_link = cur_ptr->connect;
		while (cur_link->next != NULL) {
			if (max_link == NULL) {
				max_link = cur_link;
				max_ptr = cur_ptr;
			}
			else
				if (cur_link->weight > max_link->weight) {
					max_link = cur_link;
					max_ptr = cur_ptr;
				}
			cur_link = cur_link->next;

		}
		if (max_link == NULL) {
			max_link = cur_link;
			max_ptr = cur_ptr;
		}
		else
			if (cur_link->weight > max_link->weight) {
				max_link = cur_link;
				max_ptr = cur_ptr;
			}
	}
	printf(max_ptr->name);
	printf(" ");
	printf("to");
	printf(" ");
	printf(max_link->link->name);
	printf(" ");
	printf("weight: ");
	printf("%d", max_link->weight);
}
int** f_read(FILE* file, int size) {
	//file = fopen("graph", "ab");
	
	int** matrix=(int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int) * size);
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			fseek(file, i * size*4 + j*4, 0);
			fread(&matrix[i][j], sizeof(int), 1, file);
		}
	}
	fclose(file);
	return matrix;
}

/*int f_readln(FILE* file, int i, int j) {
	int p;
	fseek(file, i * SIZE + j, 0);
	fread(p, sizeof(int), 1, file);
	return p;
}
*/
void readmatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j <size; j++) {
			printf("%d", matrix[i][j]);
			printf(" ");
		}
		printf("\n");
	}
	
}
int find_size(FILE* file_nodes, Graf* graf) {

	int i = 0;
	char* m;
	while (1) {

		m = f_readln(file_nodes);
		
		if (m == NULL) break;
		add_Node(graf, m);
		i++;
	}
	return i;

}
char* f_readln(FILE* file)
{

	char* ptr = (char*)malloc(1 * sizeof(char*));
	*ptr = NULL;
	char buf[10];
	int n, len = 0;
	do {
		n = fscanf(file, "%9[^\n]", buf);
		if (n == -1)
		{
			return NULL;
		}
		if (n == 0)
			fscanf(file, "%*c");
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
/*void add_link_file(int** matrix, Graf* graf, int size, FILE* file)
{
	char* line;
	Node* parent_ptr, * child_ptr;

	for (int i = 0; i < size; i++)
	{
		line = f_readln(file);
		parent_ptr = find_node(graf, i);

		for (int j = 0; j < size; j++)
		{
			if (line[j] != 0)
			{
				child_ptr = find_node(graf, j);
				add_link(graf, parent_ptr->name, child_ptr->name, line[j]);
			}
		}
	}
}*/
Node* find_node(Graf* graf, int index)
{
	Node* cur_ptr = graf->Head;

	for (int i = 0; i < index; i++)
	{
		cur_ptr = cur_ptr->next;
	}

	return cur_ptr;
}
/*void f_add_Node(int size, FILE* file_node, FILE* file_graf, char* name, int** mat) {
	file_node = fopen("nodes.txt", "a+");
	fprintf(file_node, name);
	fprintf(file_node, "\n");
	fclose(file_node);
	size++;
	fclose(file_node);
	int** matrix = (int**)malloc(sizeof(int*) * size);
	for (int i = 0; i < size; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int) * size);
	}
	for (int i = 0; i < size - 1; i++) {
		matrix[i] = mat[i];
	}
	for (int j = 0; j < size; j++) {
		matrix[size][j] = 0;
	}
	file_graf = fopen("graf", "wb");
	for (int i = 0; i < size; i++)
	{



		
		fwrite(matrix[i], sizeof(int), size, file_graf);




	}
	fclose(file_graf);
}
*/
void file_fill(Graf* graph)
{
	FILE* file = fopen("graph", "a");

	int** matrix = (int**)malloc(sizeof(int*) * graph->size);
	for (int i = 0; i < graph->size; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int) * graph->size);
	}

	for (int i = 0; i < graph->size; i++)
	{
		for (int j = 0; j < graph->size; j++)
		{
			matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < graph->size; i++)
	{
		for (int j = 0; j < graph->size; j++)
		{
			printf("%d", matrix[i][j]);
			printf(" ");
		
		}
		printf("\n");
	}
	
	Node* cur_ptr = graph->Head;
	Link* cur_link;

	for (int i = 0; i < graph->size-1; i++)
	{
		cur_link = cur_ptr->connect;
		while (cur_link != NULL)
		{
			matrix[i][find_index(graph, cur_link->link)] = cur_link->weight;
			cur_link = cur_link->next;
		}
		cur_ptr = cur_ptr->next;
	}
	for (int i = 0; i < graph->size; i++)
	{
		for (int j = 0; j < graph->size; j++)
		{
			printf("%d", matrix[i][j]);
			printf(" ");

		}
		printf("\n");
	}

	for (int i = 0; i < graph->size; i++)
	{
		
		
			fwrite(matrix[i], sizeof(int), 1, file);
		



	}
	fclose(file);

	file = fopen("nodes.txt", "w+t");

	cur_ptr = graph->Head;

	for (int i = 0; i < graph->size; i++)
	{
		fprintf(file, cur_ptr->name);
		fprintf(file, "\n");
		cur_ptr = cur_ptr->next;
	}

	fclose(file);
}
int find_index(Graf* graph, Node* ptr)
{
	Node* cur_ptr = graph->Head;
	int num = 0;

	while (cur_ptr != ptr)
	{
		cur_ptr = cur_ptr->next;
		num++;
	}

	return num;
}
