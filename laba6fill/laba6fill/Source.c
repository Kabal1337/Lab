#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define SIZE 10

typedef struct Node_f
{
    int length;

    int x, y;
} Node_f;
//int find_size(FILE* file_nodes);
//char* f_readln(FILE* file);
char* readln(void);
int main()
{
   
    srand(time(NULL));
    FILE* file_nodes;
    FILE* file_graf;
    file_nodes = fopen("C:/Users/34110/Desktop/Labs/Lab/laba6new/laba6new/nodes", "wb");
    file_graf = fopen("C:/Users/34110/Desktop/Labs/Lab/laba6new/laba6new/graph.txt", "w+t");
    int size;
    scanf("%d", &size);
    char** matrix = (char**)malloc(sizeof(char*) * size);
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (char*)malloc(sizeof(char) * size);
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {   if (rand()%10<=6)
            matrix[i][j] = '0';
            else  
            matrix[i][j] = '1';
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fprintf(file_graf, "%c", matrix[i][j]);
        }
        fprintf(file_graf, "\n");
    }

    fclose(file_graf);
    for (int i = 0; i < size; i++)
    {
        char* name=(char*)malloc(sizeof(char));
        sprintf(name, "%d", i);
        Node_f node_f;


        node_f.x = rand()%1000;
        node_f.y = rand()%1000;
        node_f.length = strlen(name);

        fwrite(&node_f, sizeof(Node_f), 1, file_nodes);
        fwrite(name, sizeof(char), node_f.length, file_nodes);

        
    }





}