#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct Node
{
    int key;
    char* info;
    struct Node* r_ptr; 
    struct Node* l_ptr;
    struct Node* next_ptr;
    
} Node;

typedef struct Tree
{
    struct Node* Head;

} Tree;


char* readln(void);
int get_key();

char* readln(void);
int get_key();
void node_del(Node* cur_ptr);
void tree_read_one(Node* ptr);
void tree_free(Node* ptr);

void tree_add(Tree* tree, int key, char* info);
void tree_del(Tree* tree, int key);
void tree_search(Tree* tree, int key);
void tree_read(Node* ptr);
void tree_search_max_key(Tree* tree);
void tree_draw(Node* ptr, int r);

void read_file(FILE* file, Tree* tree);
char* f_readln(FILE* file);
int main()
{
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->Head = NULL;
	FILE* file;
	
	printf("Trying to open a file\n");
	file = fopen("text.txt", "r+t");
	if (file == NULL)
	{
		printf("File not found\n\n");
	}
	else
	{
		printf("File was found, keep working\n\n");
		read_file(file, tree);
		fclose(file);
	}
    int num_of_command;

    int key;
    char* info;

	while (1)
	{
		num_of_command = -1;
		printf("List of commands:\n1. Add Element \n2. Read All \n3. Delete Element\n4. Find Element\n5. Find Element with max key\n6. Draw Tree\n7. Quit\nChoice: ");
		

		scanf("%d", &num_of_command);
		getchar();
		printf("\n");

		switch (num_of_command)
		{
		case 1:
			key = get_key();

			printf("Type info: ");
			info = readln();

			tree_add(tree, key, info);

			printf("\n");
			break;
		case 2:
			if (tree->Head != NULL)
			{
				tree_read(tree->Head);
			}

			printf("\n");
			break;
		case 3:
			key = get_key();

			if (tree->Head != NULL)
			{
				tree_del(tree, key);
			}

			printf("\n");
			break;
		case 4:
			key = get_key();
			printf("\n");
			if (tree->Head != NULL)
			{
				tree_search(tree, key);
			}

			printf("\n");
			break;
		case 5:

			printf("\n");
			if (tree->Head != NULL)
			{
				tree_search_max_key(tree);
			}
			break;
		case 6:
			if (tree->Head != NULL)
			{
				tree_draw(tree->Head, 0);
				printf("\n");
			
			}
			break;
		case 7:
			if (tree->Head != NULL)
			{
				tree_free(tree->Head);
			}
			free(tree);
			return 0;
		default:
			printf("There is no such command \n\n");
			break;
		}
	}
    return 0;
}

void tree_read_one(Node* ptr)
{
    while (ptr->next_ptr != NULL)
    {
        printf("Key: %d ", ptr->key);
        printf("Info: ");
        printf(ptr->info);
        printf("\n");

        ptr = ptr->next_ptr;
    }

    printf("Key: %d ", ptr->key);
    printf("Info: ");
    printf(ptr->info);
    printf("\n");
}

void tree_search_max_key(Tree* tree)
{
    Node* cur_ptr = tree->Head;
	while (cur_ptr->r_ptr != NULL) {
		cur_ptr = cur_ptr->r_ptr;
	}
	printf("Key: %d ", cur_ptr->key);
	printf("Info: ");
	printf(cur_ptr->info);
	printf("\n");
}


void tree_search(Tree* tree, int key)
{
    Node* cur_ptr = tree->Head;

    while (key != cur_ptr->key)
    {
        if (key < cur_ptr->key && cur_ptr->l_ptr != NULL)
        {
            cur_ptr = cur_ptr->l_ptr;
        }
        else if (key > cur_ptr->key && cur_ptr->r_ptr != NULL)
        {
            cur_ptr = cur_ptr->r_ptr;
        }
        else 
        {
            printf("There is no such key! \n");
            return; 
        }
    }

    tree_read_one(cur_ptr);
}

void node_del(Node* cur_ptr)
{
    Node* prev_ptr;
    while (cur_ptr->next_ptr != NULL)
    {
        prev_ptr = cur_ptr;
        cur_ptr = cur_ptr->next_ptr;

        free(prev_ptr->info);
        free(prev_ptr);
    }

    free(cur_ptr->info);
    free(cur_ptr);
}

void tree_del(Tree* tree, int key)
{
    Node* prev_ptr = tree->Head;
    Node* cur_ptr = tree->Head;
    
    //Поиск удалаемого элемента и предыдущего
    while (cur_ptr->key != key)
    {
        if (key < cur_ptr->key && cur_ptr->l_ptr != NULL)
        {
            prev_ptr = cur_ptr;
            cur_ptr = cur_ptr->l_ptr;
        }
        else if (key > cur_ptr->key && cur_ptr->r_ptr != NULL)
        {
            prev_ptr = cur_ptr;
            cur_ptr = cur_ptr->r_ptr;
        }
        else
        {
            printf("There is no such key! \n");
            return;
        }
    }

    //Случай когда у элемента нет детей
    if (cur_ptr->l_ptr == NULL && cur_ptr->r_ptr == NULL)
    {
        if (key < prev_ptr->key)
        {
            prev_ptr->l_ptr = NULL;
        }
        else prev_ptr->r_ptr = NULL;

        if (cur_ptr == tree->Head)
        {
            tree->Head = NULL;
        }

        node_del(cur_ptr);

        return;
    }
    
    //Случай когда у элемента одно дитя
    if (cur_ptr->l_ptr != NULL && cur_ptr->r_ptr == NULL) //Левое дитя
    {
        if (cur_ptr == tree->Head)
        {
            tree->Head = cur_ptr->l_ptr;
        } 
        else if (key < prev_ptr->key)
        {           
            prev_ptr->l_ptr = cur_ptr->l_ptr;
        }
        else if (key > prev_ptr->key) 
        {
            prev_ptr->r_ptr = cur_ptr->l_ptr;
        }

        node_del(cur_ptr);

        return;
    }
    else if (cur_ptr->l_ptr == NULL && cur_ptr->r_ptr != NULL) //Правое дитя
    {       
        if (cur_ptr == tree->Head)
        {
            tree->Head = cur_ptr->r_ptr;
        }
        else if (key < prev_ptr->key)
        {
            prev_ptr->l_ptr = cur_ptr->r_ptr;
        }
        else if (key > prev_ptr->key)
        {
            prev_ptr->r_ptr = cur_ptr->r_ptr;
        }

        node_del(cur_ptr);

        return;
    }
   
    //Случай когда у элемента двое детей
    if (cur_ptr->l_ptr != NULL && cur_ptr->r_ptr != NULL)
    {
        //Если у правого элемента есть правый ребенок и нет левого
        if (cur_ptr->r_ptr->r_ptr != NULL && cur_ptr->r_ptr->l_ptr == NULL)
        {         
            if (cur_ptr == tree->Head)
            {
                tree->Head = cur_ptr->r_ptr;
            }
            else if (key < prev_ptr->key)
            {
                prev_ptr->l_ptr = cur_ptr->r_ptr;               
            }
            else if (key > prev_ptr->key)
            {
                prev_ptr->r_ptr = cur_ptr->r_ptr;                
            }

            cur_ptr->r_ptr->l_ptr = cur_ptr->l_ptr;

            node_del(cur_ptr);

            return;
        }

        //Если у правого элемента нет левого ребенка
        if (cur_ptr->r_ptr->l_ptr == NULL)
        {
            if (cur_ptr == tree->Head)
            {
                tree->Head = cur_ptr->r_ptr;
            }
            else if (key < prev_ptr->key)
            {
                prev_ptr->l_ptr = cur_ptr->r_ptr;
            }
            else if (key > prev_ptr->key)
            {
                prev_ptr->r_ptr = cur_ptr->r_ptr;
            }

            cur_ptr->r_ptr->l_ptr = cur_ptr->l_ptr;

            node_del(cur_ptr);

            return;
        }

        //Если у правого элемента есть левый ребенок
        if (cur_ptr->r_ptr->l_ptr != NULL)
        {
            Node* elem_ptr = cur_ptr->r_ptr->l_ptr;
            
            while (elem_ptr->l_ptr != NULL)
            {
                elem_ptr = elem_ptr->l_ptr;
            }
            
            if (cur_ptr == tree->Head)
            {
                tree->Head = elem_ptr;
            } 
            else if (key < prev_ptr->key)
            {
                prev_ptr->l_ptr = elem_ptr;              
            }
            else if (key > prev_ptr->key)
            {
                prev_ptr->r_ptr = elem_ptr;
            }
               
            elem_ptr->l_ptr = cur_ptr->l_ptr;
            cur_ptr->r_ptr->l_ptr = NULL;

            while (elem_ptr->r_ptr != NULL)
            {
                elem_ptr = elem_ptr->r_ptr;
            }

            elem_ptr->r_ptr = cur_ptr->r_ptr;
            
            node_del(cur_ptr);

            return;
        }
    }

    printf("Oh crap, i think we got exception here\n");
    return;
}

void tree_read(Node* ptr)
{
    if (ptr->l_ptr != NULL)
    {
        tree_read(ptr->l_ptr);
    }
    
    if (ptr->next_ptr != NULL)
    {
        tree_read(ptr->next_ptr);
    }

    printf("Key: %d ", ptr->key);
    printf("Info: ");
    printf(ptr->info);
    printf("\n");

    if (ptr->r_ptr != NULL)
    {
        tree_read(ptr->r_ptr);
    }
}

void tree_add(Tree* tree, int key, char* info)
{   
    if (tree->Head == NULL)
    {
        tree->Head = (Node*)malloc(sizeof(Node));
        tree->Head->info = info;
        tree->Head->key = key;
        tree->Head->l_ptr = NULL;
        tree->Head->next_ptr = NULL;
        tree->Head->r_ptr = NULL;
        return;
    }

    Node* cur_ptr = tree->Head;

    while (1)
    {
        if (key < cur_ptr->key)
        {
            if (cur_ptr->l_ptr == NULL)
            {
                cur_ptr->l_ptr = (Node*)malloc(sizeof(Node));
                cur_ptr = cur_ptr->l_ptr;
                cur_ptr->info = info;
                cur_ptr->key = key;
                cur_ptr->l_ptr = NULL;
                cur_ptr->next_ptr = NULL;
                cur_ptr->r_ptr = NULL;

                break;
            }
            else 
            {
                cur_ptr = cur_ptr->l_ptr;
            }
        }
        else if (key == cur_ptr->key)
        {
            
                
				printf(cur_ptr->info);
                cur_ptr->info = info;
                cur_ptr->key = key;
                

                break;
            
           
        }
        else if (key > cur_ptr->key)
        {
            if (cur_ptr->r_ptr == NULL)
            {
                cur_ptr->r_ptr = (Node*)malloc(sizeof(Node));
                cur_ptr = cur_ptr->r_ptr;
                cur_ptr->info = info;
                cur_ptr->key = key;
                cur_ptr->l_ptr = NULL;
                cur_ptr->next_ptr = NULL;
                cur_ptr->r_ptr = NULL;

                break;
            }
            else
            {
                cur_ptr = cur_ptr->r_ptr;
            }
        }
    }
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
char* f_readln(FILE* file)
{
	fscanf(file, "%*c");

	char* ptr = (char*)malloc(1 * sizeof(char*));
	*ptr = NULL;
	char buf[10];
	int n, len = 0;
	do {
		n = fscanf(file, "%9[^\n]", buf);

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
void read_file(FILE* file, Tree* tree)
{
	int key;
	char* info;

	while (fscanf(file, "%d", &key) == 1)
	{
		info = f_readln(file);
		tree_add(tree, key, info);
	}
}
void tree_draw(Node* ptr, int r)
{
	if (ptr->r_ptr != NULL) tree_draw(ptr->r_ptr, r + 5);

	for (int i = 0; i < r; i++)
	{
		printf(" ");
	}

	printf("%d\n", ptr->key);

	if (ptr->l_ptr != NULL) tree_draw(ptr->l_ptr, r + 5);


}
void tree_free(Node* ptr)
{
	if (ptr->l_ptr != NULL)
	{
		tree_free(ptr->l_ptr);
	}

	if (ptr->r_ptr != NULL)
	{
		tree_free(ptr->r_ptr);
	}

	node_del(ptr);

}