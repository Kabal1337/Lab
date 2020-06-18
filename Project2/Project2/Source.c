#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 10

/*
todo
	файл сразу в массив
	добавлять элемент в файл сразу при появлении в таблице
	структура для ввода элемента в массив
	заголовок в файле в виде массива указателей таблицы
*/

typedef struct Item
{
	int key;
	int release;
	char* info;
	struct Item* next;

} Item;

typedef struct f_Item
{
	int key;
	int info_size;
	long next;
} f_Item;

typedef struct Table
{
	int size;
	Item arr[SIZE];
} Table;

Table* table_new();

int hash(int num, int size);

Table* table_find_key(Table* table, int key);
Table* table_find_release(Table* table, int key, int release);

void table_add(Table* table, int key, char* info);
void table_read(Table* table);

Item* erase(Item* Head, Item* ptr);
void table_delete_key(Table* table, int key);
void table_delete_release(Table* table, int key, int release);

char* readln(void);
int get_key();

void table_clear(Table* table);

//------file fun-------
void f_add(FILE* file, int key, char* info);
void f_read(FILE* file, Table* table);
void f_fill(FILE* file, Table* table);

int main()
{
	int key;
	char* info;
	int choice;
	int release;
	Table* table = table_new();

	Table* t_table;

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
			printf("Key (1), Release (2) \n");

			do
			{
				scanf("%d", &choice);
				getchar();
			} while (choice != 1 && choice != 2);

			if (choice == 1)
			{
				table_delete_key(table, key);
			}
			else if (choice == 2)
			{
				printf("Enter Release: ");

				do
				{
					scanf("%d", &release);
				} while (getchar() != '\n');

				table_delete_release(table, key, release);
			}

			printf("\n");
			break;
		case 4:
			key = get_key();
			printf("Key (1), Release (2) \n");

			do
			{
				scanf("%d", &choice);
				getchar();
			} while (choice != 1 && choice != 2);

			if (choice == 1)
			{
				t_table = table_find_key(table, key);
				table_read(t_table);
				table_clear(t_table);
			}
			else if (choice == 2)
			{
				printf("Enter Release: ");

				do
				{
					scanf("%d", &release);
				} while (getchar() != '\n');

				t_table = table_find_release(table, key, release);
				table_read(t_table);
				table_clear(t_table);
			}

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
		while (cur_ptr->next != NULL)
		{
			cur_ptr = cur_ptr->next;
			f_add(file, cur_ptr->key, cur_ptr->info);
		}

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

void f_add(FILE* file, int key, char* info)
{
	int index = hash(key, SIZE);

	//считывание массива смещений из файла
	fseek(file, 0, 0);
	long* f_arr = (long*)malloc(sizeof(long) * SIZE);
	fread(f_arr, sizeof(long), SIZE, file);

	f_Item* f_item;

	fseek(file, 0, 2);
	long cur_fpos = ftell(file);

	//Заполнение item`а
	f_item = (f_Item*)malloc(sizeof(f_Item));
	f_item->key = key;
	f_item->info_size = strlen(info);
	f_item->next = 0;

	fwrite(f_item, sizeof(f_Item), 1, file); //записываю Item в файл
	fwrite(info, sizeof(char), f_item->info_size, file); //записываю строку в файл

	if (f_arr[index] != 0)
	{
		fseek(file, f_arr[index], 0);
		fread(f_item, sizeof(f_Item), 1, file);

		while (f_item->next != 0)
		{
			fseek(file, f_item->next, 0);
			fread(f_item, sizeof(f_Item), 1, file);
		}

		f_item->next = cur_fpos;
		fseek(file, ftell(file) - sizeof(f_Item), 0);
		fwrite(f_item, sizeof(f_Item), 1, file);
	}
	else
	{
		fseek(file, index * sizeof(long), 0);
		fwrite(&cur_fpos, sizeof(long), 1, file);
	}

	free(f_arr);
	free(f_item);
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

	free(table);
}

Table* table_find_release(Table* table, int key, int release)
{
	Table* t_table = table_new(table->size);

	Item* cur_ptr = &table->arr[hash(key, table->size)];

	while (cur_ptr->next != NULL)
	{
		cur_ptr = cur_ptr->next;
		if (cur_ptr->key == key && cur_ptr->release == release)
		{
			table_add(t_table, key, cur_ptr->info);
			return t_table;
		}
	}

	if (cur_ptr->key == key && cur_ptr->release == release)
	{
		table_add(t_table, key, cur_ptr->info);
	}

	return t_table;
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

void table_delete_release(Table* table, int key, int release)
{
	int index = hash(key, table->size);

	Item* cur_ptr = &table->arr[index];

	while (cur_ptr->next != NULL)
	{
		cur_ptr = cur_ptr->next;

		if (cur_ptr->release == release)
		{
			erase(&table->arr[index], cur_ptr);
			return;
		}

	}

	if (cur_ptr->release == release)
	{
		erase(&table->arr[index], cur_ptr);
		return;
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
			printf("Release: %d ", cur_ptr->release);
			printf("Info: ");
			printf(cur_ptr->info);
			printf("\n");
		}

	}
}

void table_add(Table* table, int key, char* info)
{
	int index = hash(key, table->size);
	int release = 0;

	Item* cur_ptr;

	cur_ptr = &table->arr[index];

	while (cur_ptr->next != NULL)
	{
		if (cur_ptr->key == key)
		{
			cur_ptr->release = release;
			release++;
		}
		cur_ptr = cur_ptr->next;
	}

	if (cur_ptr->key == key)
	{
		cur_ptr->release = release;
		release++;
	}

	cur_ptr->next = (Item*)malloc(sizeof(Item));
	cur_ptr = cur_ptr->next;
	cur_ptr->next = NULL;

	cur_ptr->key = key;
	cur_ptr->info = info;
	cur_ptr->release = release;
}

int hash(int key, int size)
{
	return abs(key % size);
}

Table* table_new()
{
	Table* ptr = (Table*)malloc(sizeof(Table));

	for (int i = 0; i < SIZE; i++)
	{
		ptr->arr[i].next = NULL;
	}

	ptr->size = SIZE;

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