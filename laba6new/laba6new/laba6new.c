#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef struct Node_way
{
    int length_way;
    char** prev_name;

} Node_way;
typedef struct Way
{
    Node_way* way1;
    Node_way* way2;
    Node_way* way3;

} Way;
typedef struct Node_f
{
    int length;
    
    int x, y;
} Node_f;
typedef struct Node
{
    int num;
    char* name;
    struct Link* links;
    struct Node* next_ptr;
    int x, y;
} Node;

typedef struct Graph
{
    int size;
    struct Node* node;
} Graph;

typedef struct Link
{
    int weight;
    
    struct Node* node;
    struct Link* next_link;
} Link;
int infinity();
//Служебные 
void find_way(Node* graph, char* parent, char* child, Way* ways);
char* readln();
void read_node(Graph* graph);
void check_links(Graph* graph, char* name);
void list_del_link(Node* ptr, Link* link);
void list_del_node(Graph* graph, Node* ptr);

Node* find_node(Graph* graph, int index);
int find_index(Graph* graph, Node* ptr);
void node_num(Graph* graph, char* nodes);
//Основные 
void add_node(Graph* graph, char* name, char x, char y);
void add_link(Graph* graph, char* parent, char* child);
void del_node(Graph* graph, char* name);

void fill_graphviz(Graph* graph);





//Файл
void file_fill(Graph* graph);
void file_read(Graph* graph);
char* f_readln(FILE* file);

int main()
{
    int inf = infinity();
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->node = NULL;
    graph->size = 0;

    int command, dir;
    char* name, * child, * parent;
    char** names;
    int x, y;
    file_read(graph);

    while (1)
    {
        command = -1;

        printf("List of commands:\n1. Add Node \n2. Read All Nodes\n3. Make Link\n4. Check Link\n5. Delete Node\n6. Find shortest way\n8. Draw Graph\n9. Exit\n");
        printf("Choice: ");
        scanf("%d", &command);
        getchar();
        printf("\n");

        switch (command)
        {
        case 1:
            printf("New Node name: ");
            name = readln();
            printf("Coordinate X: ");
            scanf("%d", &x);
            printf("Coordinate Y: ");
            scanf("%d", &y);
            printf("\n");
            
            add_node(graph, name, x, y);

            file_fill(graph);
            printf("\n");
            break;
        case 2:
            printf("\n");

            if (graph->node != NULL)
            {
                read_node(graph);
            }

            printf("\n");
            break;
        case 3:
            printf("Parent name: ");
            parent = readln();

            printf("Child name: ");
            child = readln();

            printf("\n");

            add_link(graph, parent, child);

            file_fill(graph);
            printf("\n");
            break;
        case 4:
            printf("Node name: ");
            parent = readln();

            check_links(graph, parent);
            printf("\n");

            break;
        case 5:
            printf("Node name: ");
            name = readln();

            del_node(graph, name);

            file_fill(graph);
            printf("\n");
            break;
        

            

            printf("\n");
            break;
        case 8:
            fill_graphviz(graph);
            break;
        case 9:

            file_fill(graph);
            return 0;
            break;
        case 6:
            printf("Parent name: ");
            parent = readln();

            printf("Child name: ");
            child = readln();
           // for (int i = 0; i < 1000; i++) {
             //   find_way(graph, "0", "5");
           // }
            
           
            Way ways;
            ways.way1=NULL;
            ways.way2=NULL;
            ways.way3=NULL;
            for(int i=0; i<3; i++)
            find_way(graph, parent, child, &ways);
            if (ways.way1 != NULL) {
             printf("%d", ways.way1->length_way);
               printf(" ");
           
                for (int i = 0; i < 3; i++)
                {

                    if (strcmp(ways.way1->prev_name[i], "busy") == 0) break;
                    //printf(" ");
                    printf(ways.way1->prev_name[i]);

                }
            }
                printf("\n");
            if (ways.way2 != NULL) {
                printf("%d", ways.way2->length_way);
                printf(" ");
            
            
                for (int i = 0; i < 3; i++)
                {

                    if (strcmp(ways.way2->prev_name[i], "busy") == 0) break;
                    //printf(" ");
                    printf(ways.way2->prev_name[i]);

                }
            }
                printf("\n");
            if (ways.way3 != NULL) {
             printf("%d", ways.way3->length_way);
                printf(" ");
            
            
                for (int i = 0; i < 3; i++)
                {

                    if (strcmp(ways.way3->prev_name[i], "busy") == 0) break;
                    //printf(" ");
                    printf(ways.way3->prev_name[i]);
                }

                printf("\n");
            }
            break;
        default:
            printf("There is no such command \n\n");
            break;
        }
    }

    return 0;
}

void file_fill(Graph* graph)
{
    FILE* file = fopen("graph.txt", "w+t");

    char** matrix = (char**)malloc(sizeof(char*) * graph->size);
    for (int i = 0; i < graph->size; i++)
    {
        matrix[i] = (char*)malloc(sizeof(char) * graph->size);
    }

    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            matrix[i][j] = '0';
        }
    }

    Node* cur_ptr = graph->node;
    Link* cur_link;

    for (int i = 0; i < graph->size; i++)
    {
        cur_link = cur_ptr->links;
        while (cur_link != NULL)
        {
            matrix[i][find_index(graph, cur_link->node)] = '1';
            cur_link = cur_link->next_link;
        }
        cur_ptr = cur_ptr->next_ptr;
    }


    for (int i = 0; i < graph->size; i++)
    {
        for (int j = 0; j < graph->size; j++)
        {
            fprintf(file, "%c", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);

    file = fopen("nodes", "wb");

    cur_ptr = graph->node;

    for (int i = 0; i < graph->size; i++)
    {
       
        Node_f node_f;
       
       
        node_f.x = cur_ptr->x;
        node_f.y = cur_ptr->y;
        node_f.length = strlen(cur_ptr->name);
       
        fwrite(&node_f, sizeof(Node_f), 1, file);
        fwrite(cur_ptr->name, sizeof(char), node_f.length, file);
        
        cur_ptr = cur_ptr->next_ptr;
    }

    for (int i = 0; i < graph->size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    fclose(file);
    
}

int find_index(Graph* graph, Node* ptr)
{
    Node* cur_ptr = graph->node;
    int num = 0;

    while (cur_ptr != ptr)
    {
        cur_ptr = cur_ptr->next_ptr;
        num++;
    }

    return num;
}

char** top_logic_sort(Graph* graph)
{
    int SIZE = graph->size;
    char** name_arr = (char**)malloc(sizeof(char*) * graph->size);
    int it = 0;

    Node* cur_ptr = graph->node;
    Node* prev_ptr = cur_ptr;


    char* temp;

    while (graph->node != NULL)
    {
        cur_ptr = graph->node;

        for (int i = 0; i < SIZE; i++)
        {
            if (cur_ptr->links == NULL)
            {
                temp = (char*)malloc(sizeof(char) * strlen(cur_ptr->name) + 1);
                strcpy(temp, cur_ptr->name);

                name_arr[it] = temp;

                it++;

                prev_ptr = cur_ptr;
                cur_ptr = cur_ptr->next_ptr;

                del_node(graph, prev_ptr->name);
            }
            else
            {
                cur_ptr = cur_ptr->next_ptr;
            }
        }

        SIZE = graph->size;
    }

    /*
    for (int i = 0; i < it; i++)
    {
        printf(name_arr[i]);
        printf("\n");
    }
    */

    return name_arr;
}

Node* find_node(Graph* graph, int index)
{
    Node* cur_ptr = graph->node;

    for (int i = 0; i < index; i++)
    {
        cur_ptr = cur_ptr->next_ptr;
    }

    return cur_ptr;
}

void file_read(Graph* graph)
{   
    Node_f node_f;
    int length;
    
    FILE* file = fopen("nodes", "rb");

    if (file != NULL)
    {
        //printf("File nodes.txt was found, keep working...\n");
    }
    else
    {
        printf("File nodes.txt was not found!\n");
        return;
    }

    char* name;
    while (1)
    {
        node_f.length = 0;
        name = NULL;
        fread(&node_f, sizeof(Node_f), 1, file);
        name = (char*)malloc(sizeof(char) * node_f.length + 1);
        fread(name, sizeof(char), node_f.length, file);
        name[node_f.length] = 0;
        if (node_f.length == 0)
        {
            break;
        }

        add_node(graph, name, node_f.x, node_f.y);
    }

    fclose(file);
    file = fopen("graph.txt", "r+t");

    if (file != NULL)
    {
        //printf("File graph.txt was found, keep working...\n");
    }
    else
    {
        printf("File graph.txt was not found!\n");
        return;
    }

    char* line;
    Node* parent_ptr, * child_ptr;

    for (int i = 0; i < graph->size; i++)
    {
        line = f_readln(file);
        parent_ptr = find_node(graph, i);

        for (int j = 0; j < graph->size; j++)
        {
            if (line[j] == '1')
            {
                child_ptr = find_node(graph, j);
                add_link(graph, parent_ptr->name, child_ptr->name);
            }
        }
    }
}

void list_del_node(Graph* graph, Node* ptr)
{
    Node* cur_ptr = graph->node;
    Node* prev_ptr = cur_ptr;

    if (graph->node == ptr)
    {
        graph->node = cur_ptr->next_ptr;
        free(cur_ptr->name);
        free(cur_ptr);
        return;
    }

    while (cur_ptr->next_ptr != ptr)
    {
        prev_ptr = cur_ptr;
        cur_ptr = cur_ptr->next_ptr;
    }

    prev_ptr = cur_ptr;
    cur_ptr = cur_ptr->next_ptr;

    prev_ptr->next_ptr = cur_ptr->next_ptr;
    free(cur_ptr->name);
    free(cur_ptr);
}

void list_del_link(Node* ptr, Link* link)
{
    Link* cur_ptr = ptr->links;
    Link* prev_ptr = cur_ptr;

    if (cur_ptr == link)
    {
        ptr->links = cur_ptr->next_link;
        free(cur_ptr);
        return;
    }

    while (cur_ptr->next_link != link)
    {
        prev_ptr = cur_ptr;
        cur_ptr = cur_ptr->next_link;
    }

    cur_ptr = cur_ptr->next_link;
    prev_ptr->next_link = cur_ptr->next_link;
    free(cur_ptr);
}

void del_node(Graph* graph, char* name)
{
    Node* cur_ptr = graph->node;
    Node* del_ptr = NULL;
    Link* link_ptr, * prev_link;

    for (int i = 0; i < graph->size; i++)
    {
        if (strcmp(cur_ptr->name, name) == 0)
        {
            del_ptr = cur_ptr;
        }
        else
        {
            link_ptr = cur_ptr->links;

            while (link_ptr != NULL)
            {
                if (strcmp(link_ptr->node->name, name) == 0)
                {
                    prev_link = link_ptr;
                    link_ptr = link_ptr->next_link;
                    list_del_link(cur_ptr, prev_link);
                }
                else link_ptr = link_ptr->next_link;
            }
        }

        cur_ptr = cur_ptr->next_ptr;

    }

    if (del_ptr == NULL) return;

    link_ptr = del_ptr->links;
    prev_link = link_ptr;

    while (link_ptr != NULL)
    {
        prev_link = link_ptr;
        link_ptr = link_ptr->next_link;
        list_del_link(del_ptr, prev_link);
    }

    list_del_node(graph, del_ptr);

    graph->size--;

}



void fill_graphviz(Graph* graph)
{
    FILE* file;
    file = fopen("cringe.txt", "w+t");

    Node* cur_ptr = graph->node;
    Link* link_ptr;

    fprintf(file, "digraph G {\n");

    for (int i = 0; i < graph->size; i++)
    {
        link_ptr = cur_ptr->links;

        if (link_ptr == NULL)
        {
            fprintf(file, cur_ptr->name);
            fprintf(file, "\n");
        }
        else
        {
            while (link_ptr != NULL)
            {
                fprintf(file, cur_ptr->name);
                fprintf(file, " -> ");
                fprintf(file, link_ptr->node->name);

                fprintf(file, "\n");

                link_ptr = link_ptr->next_link;
            }
        }

        cur_ptr = cur_ptr->next_ptr;
    }

    fprintf(file, "}\n");

    fclose(file);
}

void check_links(Graph* graph, char* name)
{
    Node* cur_ptr = graph->node;
    int check = 0;

    for (int i = 0; i < graph->size; i++)
    {
        if (strcmp(cur_ptr->name, name) == 0)
        {
            check = 1;
            break;
        }
        cur_ptr = cur_ptr->next_ptr;
    }
    if (check == 0)
    {
        printf("There is no such Node!\n");
        return;
    }

    Link* link_ptr = cur_ptr->links;
    if (link_ptr == NULL)
    {
        printf("This Node has no links!\n");
        return;
    }

    while (link_ptr != NULL)
    {
        printf(link_ptr->node->name);
        printf(" ");
        printf("%d", link_ptr->weight);
        printf("%c",'\n');
        link_ptr = link_ptr->next_link;
    }


}

void make_all_white(Graph* graph)
{
    Node* cur_ptr = graph->node;
    Link* link_ptr;

    for (int i = 0; i < graph->size; i++)
    {
        link_ptr = cur_ptr->links;

        while (link_ptr != NULL)
        {
            
            link_ptr = link_ptr->next_link;
        }

        cur_ptr = cur_ptr->next_ptr;
    }
}



void add_link(Graph* graph, char* parent, char* child)
{
    Node* child_ptr = NULL;
    Node* parent_ptr = NULL;
    Node* cur_ptr = graph->node;
    
    for (int i = 0; i < graph->size; i++)
    {
        if (strcmp(cur_ptr->name, parent) == 0)
        {
            parent_ptr = cur_ptr;
        }
        else if (strcmp(cur_ptr->name, child) == 0)
        {
            child_ptr = cur_ptr;
        }

        if (parent_ptr != NULL && child_ptr != NULL)
        {
            //printf("Found them!\n");
            break;
        }

        cur_ptr = cur_ptr->next_ptr;
    }

    if (parent_ptr == NULL || child_ptr == NULL)
    {
        printf("There is no such parent or child!\n");
        return;
    }

    Link* link_ptr;

    if (parent_ptr->links == NULL)
    {
        parent_ptr->links = (Link*)malloc(sizeof(Link));
        link_ptr = parent_ptr->links;
    }
    else
    {
        link_ptr = parent_ptr->links;
        while (link_ptr->next_link != NULL)
        {
            link_ptr = link_ptr->next_link;
        } 
        link_ptr->next_link = (Link*)malloc(sizeof(Link));
        link_ptr = link_ptr->next_link;
    }
    int x = parent_ptr->x - child_ptr->x;
    int y = parent_ptr->y - child_ptr->y;
    link_ptr->next_link = NULL;
    
    link_ptr->node = child_ptr;
    link_ptr->weight = sqrt(pow(x,2) + pow(y,2));
    
}

void read_node(Graph* graph)
{
    Node* ptr = graph->node;
    printf("Graph size: %d \n", graph->size);
    while (ptr->next_ptr != NULL)
    {

        printf(ptr->name);
        printf(" ");
        printf("%d", ptr->x);
        printf(" ");
        printf("%d", ptr->y);
        printf("\n");
        ptr = ptr->next_ptr;
    }


    printf(ptr->name);
    printf(" ");
    printf("%d", ptr->x);
    printf(" ");
    printf("%d", ptr->y);
    printf("\n");


}

void add_node(Graph* graph, char* name, int x, int y)
{
   
    
    Node* ptr;
    if (graph->node == NULL)
    {
       
        
        graph->node = (Node*)malloc(sizeof(Node));
        ptr = graph->node;
        ptr->x = x;
        ptr->y = y;

    }
    else
    {
        ptr = graph->node;
        while (ptr->next_ptr != NULL)
        {
            if (strcmp(ptr->name, name) == 0)
            {
                printf("This name already taken! \n");
                return;
            }

            ptr = ptr->next_ptr;
        }
        if (strcmp(ptr->name, name) == 0)
        {
            printf("This name already taken!");
            return;
        }
        ptr->next_ptr = (Node*)malloc(sizeof(Node));
        ptr = ptr->next_ptr;
    }

    graph->size++;
    ptr->links = NULL;
    ptr->name = name;
    ptr->next_ptr = NULL;
    ptr->x = x;
    ptr->y = y;

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

char* readln()
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

    return ptr;
}

void find_way(Graph* graph, char* parent, char* child, Way* ways)
{
    int inf = infinity();
    Link* link_ptr;
    Node_way* b= (Node_way*)malloc(graph->size * sizeof(Node_way));
   
    for (int g = 0; g < graph->size; g++) {
        b[g].prev_name = (char**)malloc(graph->size * sizeof(char*));
        for (int i = 0; i < graph->size; i++) {
            b[g].prev_name[i] = (char*)malloc(graph->size * sizeof(char));
        }
        for (int i = 0; i < graph->size; i++) {
            b[g].prev_name[i] = "busy";
        }
    }
    Node* node = graph->node;
    node_num(graph, parent);
    b[0].length_way=0;
    //b[0].prev_name = NULL;
    
    for (int i = 1; i < graph->size; i++)
    {
        b[i].length_way = inf;
       

    }
    // Node* node_next;
    int o = 0;
    
    for (int i = 0; i < graph->size-1; i++) //итерации по Бельману-Форду
    {   
        for (int j = 0; j < graph->size; j++) { //проход по массиву b
            if (b[j].length_way != inf) {
                
                for (int m = 0; m < graph->size; m++)//поиск первого эелемента в списке вершин
                {
                    if (node->num == j) break;

                    if (node->next_ptr == NULL) node = graph->node;
                    else
                        node = node->next_ptr;
                }
                link_ptr = node->links;//указатель на прохождение связей данной вершины 
                if (link_ptr != NULL)
                 // выполняется, если прошлый размер пути меньше предыдущего 
                
                    while (1) { //для каждой связи node выполняем
                        if (b[j].length_way + link_ptr->weight < b[link_ptr->node->num].length_way) // выполняется, если прошлый размер пути меньше предыдущего 
                        {   
                            if (((ways->way1==NULL)||(ways->way1->length_way != b[j].length_way + link_ptr->weight)) && ((ways->way2 == NULL) || (ways->way2->length_way != b[j].length_way + link_ptr->weight)) && ((ways->way3 == NULL) || (ways->way3->length_way != b[j].length_way + link_ptr->weight))) {
                                b[link_ptr->node->num].length_way = b[j].length_way + link_ptr->weight;//складываем вес node и вес связи

                                for (int s = 0; s < graph->size; s++) {
                                    //b[link_ptr->node->num].prev_name[s][0] = 0;
                                    b[link_ptr->node->num].prev_name[s] = "busy";
                                    b[link_ptr->node->num].prev_name[s] = b[j].prev_name[s];//прошлый путь удаляется и заменяется прошлым без последней пройденной вершины
                                }
                                int k = 0;
                                while (1)
                                {
                                    if (strcmp(b[link_ptr->node->num].prev_name[k], "busy") == 0) break; //доходим до конца массива

                                    k++;
                                }
                                b[link_ptr->node->num].prev_name[k] = node->name;//вписываем  последнюю пройденную вершину

                                //if (link_ptr->next_link == NULL) break;// если связи кончились, останавливаемся.
                                //link_ptr = link_ptr->next_link; //идем к следующей связи
                            }
                        }
                        if (link_ptr->next_link == NULL) break;
                        link_ptr = link_ptr->next_link;
                    }
                
            }
        }
    }
    
    int num_child;
    node = graph->node;
    for (int i = 0; i < graph->size; i++) {
        
        if (strcmp(node->name, child)==0) {
            num_child = node->num;
            break;
        }
        node = node->next_ptr;
    }
    if (b[num_child].length_way == inf) {
        printf("No way");
        return;
    }
    /*printf("%d",b[num_child].length_way);
    printf(" ");
    for (int i = 0; i < graph->size; i++)
    {   
        if (b[num_child].prev_name[i] == "busy") break;
        printf(b[num_child].prev_name[i]);
    }
    printf("\n");*/
    while (1) {
        if (ways->way1 == NULL) {
            ways->way1 = &b[num_child];
            break;
        }
        if (ways->way2 == NULL) {
            ways->way2 = &b[num_child];
            break;
        }
        if (ways->way3 == NULL) {
            ways->way3 = &b[num_child];
            break;
        }
    }
    /* for (int g = 0; g < graph->size; g++) {
        //b[g].prev_name = (char**)malloc(graph->size * sizeof(char*));
        for (int i = 0; i < graph->size; i++) {
            for (int s = 0; s < graph->size; s++) {
                free(b[g].prev_name[i][s]);
            }
        }
    }
    for (int g = 0; g < graph->size; g++) {
        //b[g].prev_name = (char**)malloc(graph->size * sizeof(char*));
        for (int i = 0; i < graph->size; i++) {
            free(b[g].prev_name[i]);

        }
    }
    */
   /* for (int i = 0; i < 3; i++)
    {
        printf("%d", ways[i].length_way);
        
        for (int g = 0; g < graph->size; g++) {
            if (strcmp(ways[i].prev_name[g], "busy") == 0) break;
            printf(" ");
            printf(ways[i].prev_name[g]);
        }
        printf("\n");
    }
   */
    //printf("\n");
    //for (int g = 0; g < graph->size; g++) {
        //b[g].prev_name = (char**)malloc(graph->size * sizeof(char*));
       
      //      free(b[g].prev_name);

        
    //}
    //free(b);

}


int infinity() {
    int a = pow(2, 31);
    int b = abs(1 + a);
    return(b);
}

void node_num(Graph* graph, char* nodes) {
    Node* node = graph->node;
    for (int i = 0; i < graph->size; i++) {
        if (strcmp(node->name, nodes)==0) break;
        node = node->next_ptr;
    }
    for (int i = 0; i < graph->size; i++)
    {   
        node->num = i;
        if (node->next_ptr == NULL) node = graph->node;
        else
        node = node->next_ptr;
        
    }

}