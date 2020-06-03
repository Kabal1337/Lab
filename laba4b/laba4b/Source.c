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
#define SIZE 11

/* todo
	Понять как работает профилировщик
*/

typedef struct Item
{
	int key;
	int busy;
	char* info;
	//struct Item* next;

} Item;

typedef struct Table
{
	int size;
	Item* arr;
} Table;
typedef struct f_Item
{
	int key;
	int info_size;
	//long next;
} f_Item;


Table* table_new(int size);

Table* table_find_key(Table* table, int key);


void table_add(Table* table, int key, char* info);
void table_read(Table* table);

//Item* erase(Item* Head, Item* ptr);

void table_delete_key(Table* table, int key);
void f_add(FILE* file, int key, char* info);
void f_read(FILE* file, Table* table);
void f_fill(FILE* file, Table* table);


void table_clear(Table* table);

char* readln(void);
int get_key();
int h1(int key);
int h2(int key);
int main()
{
	int key;
	char* info;
	int choice;
	int release;
	
	Table* table = table_new(SIZE);

	Item* t_table;

	int num_of_command;
	FILE* file;
	printf("Type file name: ");
	char* file_name = readln();
	printf("\nTrying to open a file\n");
	file = fopen(file_name, "r+b");

	if (file == NULL)
	{
		printf("File not found, creating a new one\n\n");
		long f_arr[SIZE];
		for (long i = 0; i < SIZE; i++)
		{
			f_arr[i] = 0;
		}

		file = fopen(file_name, "wb+");
		fwrite(f_arr, sizeof(long), SIZE, file);
	}
	else
	{
		printf("File was found, keep working\n\n");
		f_read(file, table);
	}
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
			printf("Type info: ");
			info = readln();
			table_add(table, key, info);
			f_add(file, key, info);

			printf("\n");
			break;
		case 2:
			table_read(table);

			printf("\n");
			break;
		case 3:
			key = get_key();




			table_delete_key(table, key);



			printf("\n");
			break;
		case 4:
			key = get_key();
			table_find_key(table, key);
			//table_read(t_table);
			//table_clear(t_table);


			printf("\n");
			break;
		case 5:
			freopen(file_name, "wb+", file);
			f_fill(file, table);
			fclose(file);
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
		if (cur_ptr->busy == 1) {
			if (cur_ptr->info != NULL)
				free(cur_ptr->info);

		}
	}

	free(table->arr);
	free(table);
}



Table* table_find_key(Table* table, int key)
{




	int index;
	Item* cur_ptr;
	for (int i = 0; i < 11; i++) {
		index = (h1(key) + i * h2(key)) % 11;
		cur_ptr = &table->arr[index];
		if (cur_ptr->busy == 1) {
			if (cur_ptr->key == key)
			{
				Item* cur_ptr1 = (Item*)malloc(sizeof(Item));

				cur_ptr1->info = cur_ptr->info;
				cur_ptr1->key = cur_ptr->key;
				printf("Key: %d ", cur_ptr1->key);
				printf("Info: ");
				printf(cur_ptr1->info);
				printf("\n");
				free(cur_ptr1);
				return;

			}
		}

	}
	printf("Invalid index");
}
/*
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
*/

void table_delete_key(Table* table, int key)
{
	int index;
	Item* cur_ptr;
	for (int i = 0; i < 11; i++) {
		index = (h1(key) + i * h2(key)) % 11;
		cur_ptr = &table->arr[index];
		if (cur_ptr->busy == 1) {
			if (cur_ptr->key == key)
			{
				cur_ptr->info = NULL;
				cur_ptr->key = NULL;
				cur_ptr->busy = 0;
				return;
			}
		}

	}
	printf("Invalid key");

}



void table_read(Table* table)
{
	Item* cur_ptr;
	for (int i = 0; i < table->size; i++)
	{
		cur_ptr = &table->arr[i];

		if (cur_ptr->busy == 1) {
			printf("Key: %d ", cur_ptr->key);
			printf("Info: ");
			if (cur_ptr->info != NULL)
				printf(cur_ptr->info);
			printf("\n");
		}

	}
}

void table_add(Table* table, int key, char* info)
{
	int index;
	Item* cur_ptr;
	for (int i = 0; i < 11; i++) {
		index = (h1(key) + i * h2(key)) % 11;
		cur_ptr = &table->arr[index];
		if (cur_ptr->busy == 0) {
			cur_ptr->key = key;
			cur_ptr->info = info;
			cur_ptr->busy = 1;
			return;
		}
		else if (cur_ptr->key == key) {
			printf("Invalid Key");
			return;
		}
	}
	printf("TableOFF");
}



Table* table_new(int size)
{
	Table* ptr = (Table*)malloc(sizeof(Table));
	ptr->arr = (Item*)malloc(size * sizeof(Item));

	for (int i = 0; i < size; i++)
	{

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
	//printf("Type info: ");

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

int h1(int key) {
	return (key % 11);
}
int h2(int key) {
	return (key % 9 + 1);


}
void f_add(FILE* file, int key, char* info)
{
	fseek(file, 0, 0);
	int index;
	Item* cur_ptr;
	for (int i = 0; i < 11; i++) {
		index = (h1(key) + i * h2(key)) % 11;


		long* f_arr = (long*)malloc(sizeof(long) * SIZE);
		fread(f_arr, sizeof(long), SIZE, file);

		f_Item* f_item;

		fseek(file, 0, 2);
		long cur_fpos = ftell(file);

		//Заполнение item`а
		f_item = (f_Item*)malloc(sizeof(f_Item));
		f_item->key = key;
		if(info!=NULL)
		f_item->info_size = strlen(info);
		else {
			info = "";
			f_item->info_size = strlen(info);
		}
		fwrite(f_item, sizeof(f_Item), 1, file); //записываю Item в файл
		fwrite(info, sizeof(char), f_item->info_size, file); //записываю строку в файл
		if (f_arr[index] == 0) {
			fseek(file, index * sizeof(long), 0);
			fwrite(&cur_fpos, sizeof(long), 1, file);
			free(f_arr);
			free(f_item);
			return;
		}
	}	
}
void f_fill(FILE* file, Table* table)
{
	long f_arr[SIZE];
	for (long i = 0; i < SIZE; i++)
	{
		f_arr[i] = 0;
	}

	fwrite(f_arr, sizeof(long), SIZE, file);

	Item* cur_ptr;
	for (int i = 0; i < table->size; i++)
	{
		cur_ptr = &table->arr[i];
		if(cur_ptr->busy==1)
		f_add(file, cur_ptr->key, cur_ptr->info);
		

	}
}

void f_read(FILE* file, Table* table)
{
	char* info = (char*)malloc(sizeof(char));
	f_Item* f_item = (f_Item*)malloc(sizeof(f_Item));

	fseek(file, SIZE * sizeof(long), 0);

	while (fread(f_item, sizeof(f_Item), 1, file) != 0)
	{
		info = (char*)malloc(sizeof(char) * (f_item->info_size + 1));
		fread(info, sizeof(char), f_item->info_size, file);

		info[f_item->info_size] = 0;

		table_add(table, f_item->key, info);
	}

}