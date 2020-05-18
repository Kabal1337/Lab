#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
//int clean_stdin(c);
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/* todo
	Понять как работает профилировщик
*/

typedef struct Item
{
	int key;
	int busy;
	char* info;
	struct Item* next;

} Item;

typedef struct Table
{
	int size;
	Item* arr;
} Table;


int hash(int num, int size);

Table* table_new(int size);

Table* table_find_key(Table* table, int key);


void table_add(Table* table, int key, char* info);
void table_read(Table* table);

Item* erase(Item* Head, Item* ptr);

void table_delete_key(Table* table, int key);



void table_clear(Table* table);

char* readln(void);
int get_key();

int main()
{
	int key;
	char* info;
	int choice;
	int release;
	const int SIZE = 10;
	Table* table = table_new(SIZE);

	Item* t_table;

	int num_of_command;

	while (1)
	{
		num_of_command = -1;
		choice = 0;

		printf("List of commands:\n1. Add Element \n2. Read All \n3. Delete Element\n4. Find Element\n5. Quit\nChoice: ");

		scanf("%d", &num_of_command);
		getchar();
		printf("\n");

		switch (num_of_command)
		{
		case 1:
			key = get_key();
			info = readln();
			table_add(table, key, info);


			printf("\n");
			break;
		case 2:
			table_read(table);

			printf("\n");
			break;
		case 3:
			key = get_key();
			printf("Key (1)\n");

			do
			{
				scanf("%d", &choice);
				getchar();
			} while (choice != 1 && choice != 2);

			
			
				table_delete_key(table, key);
			
	

			printf("\n");
			break;
		case 4:
			key = get_key();
			t_table = table_find_key(table, key);
			table_read(t_table);
			table_clear(t_table);
			

			printf("\n");
			break;
		case 5:
			table_clear(table);
			return 0;
		default:
			printf("There is no such command \n\n");
			break;
		}
	}

	return 0;
}

void table_clear(Table* table)
{
	Item* cur_ptr, * prev_ptr;

	for (int i = 0; i < table->size; i++)
	{
		cur_ptr = &table->arr[i];

		if (cur_ptr->next != NULL)
		{
			cur_ptr = cur_ptr->next;

			while (cur_ptr->next != NULL)
			{
				prev_ptr = cur_ptr;
				cur_ptr = cur_ptr->next;
				free(prev_ptr);
			}

			free(cur_ptr);
		}

	}

	free(table->arr);
	free(table);
}



Table* table_find_key(Table* table, int key)
{
	Table* t_table = table_new(table->size);

	Item* cur_ptr = &table->arr[hash(key, table->size)];

	while (cur_ptr->next != NULL)
	{
		cur_ptr = cur_ptr->next;
		if (cur_ptr->key == key)
		{
			table_add(t_table, key, cur_ptr->info);
		}
	}

	return t_table;
}

Item* erase(Item* Head, Item* ptr)
{
	Item* cur_ptr = Head;

	while (cur_ptr->next != ptr)
	{
		cur_ptr = cur_ptr->next;
	}

	cur_ptr->next = ptr->next;
	free(ptr);

	return cur_ptr;
}

void table_delete_key(Table* table, int key)
{
	int index = hash(key, table->size);

	Item* cur_ptr = &table->arr[index];

	while (cur_ptr->next != NULL)
	{
		cur_ptr = cur_ptr->next;

		if (cur_ptr->key == key)
		{
			cur_ptr = erase(&table->arr[index], cur_ptr);
		}

	}

	if (cur_ptr->key == key)
	{
		erase(&table->arr[index], cur_ptr);
	}
}



void table_read(Table* table)
{
	Item* cur_ptr;
	for (int i = 0; i < table->size; i++)
	{
		cur_ptr = &table->arr[i];
		while (cur_ptr->next != NULL)
		{
			cur_ptr = cur_ptr->next;
			printf("Key: %d ", cur_ptr->key);
			printf("Info: ");
			printf(cur_ptr->info);
			printf("\n");
		}

	}
}

void table_add(Table* table, int key, char* info)
{
	int index = hash(key, table->size);
	

	Item* cur_ptr;

	cur_ptr = &table->arr[index];

	while (cur_ptr->next != NULL)
	{
		cur_ptr = cur_ptr->next;
	}

	
	if (cur_ptr->busy == 0) {
		cur_ptr->next = (Item*)malloc(sizeof(Item));
		cur_ptr->busy = 1;
		cur_ptr = cur_ptr->next;
		cur_ptr->next = NULL;

		cur_ptr->key = key;
		cur_ptr->info = info;
		
	}
	else printf("Miss");
}

int hash(int key, int size)
{
	return abs(key % size);
}

Table* table_new(int size)
{
	Table* ptr = (Table*)malloc(sizeof(Table));
	ptr->arr = (Item*)malloc(size * sizeof(Item));

	for (int i = 0; i < size; i++)
	{
		ptr->arr[i].next = NULL;
		ptr->arr[i].busy = 0;
	}

	ptr->size = size;

	return ptr;
}


int get_key()
{
	printf("Enter key: ");

	int key;

	do
	{
		scanf("%d", &key);
	} while (getchar() != '\n');

	return key;
}

char* readln(void) {
	printf("Type info: ");

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
	return ptr;
}