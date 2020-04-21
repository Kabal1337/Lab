#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
//int clean_stdin(c);
int main()
{   
    int** a;  // указатель на указатель на строку элементов
    int i, j, n, m;
    
	system("chcp 1251");
    system("cls");
    printf("Введите количество строк: ");
	
	
	while ((scanf("%d", &n) != 1)||(n==0)) {
		printf("Некоректный ввод, введите еще раз: ");
		getchar();
	}
	// printf("Введите количество столбцов: ");
    
    // Выделение памяти под указатели на строки
    a = (int**)malloc(n * sizeof(int*));
    // Ввод элементов массива
    int *f;
    f = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)  // цикл по строкам
	{
		printf("Введите количество столбцов: ");

		while ((scanf("%d", &m) != 1)||(m==0)) {
			printf("Некоректный ввод, введите еще раз: ");
			getchar();
		}
		f[i] = m;
		
			// Выделение памяти под хранение строк
			a[i] = (int*)malloc(m * sizeof(int));
			
			for (j = 0; j < m; j++)  // цикл по столбцам
			{
				printf("a[%d][%d] = ", i, j);


				while ((scanf("%d", &a[i][j]) != 1)) {
					printf("Некоректный ввод, введите еще раз: ");
					getchar();
				}
			}
		
	}
   
    for (i = 0; i < n; i++)  // цикл по строкам
    {
        
        for (j = 0; j < f[i]; j++) // цикл по столбцам
        {
            printf("%5d ", a[i][j]); 
        }
        printf("\n");
    }
    int* b;
    b=(int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        //printf("joap");
		int l=0;
        int max=a[i][0];
        int k=0;
        for (int m=0; m<f[i]; m++)
        {
			//printf("joap1");
			
        if (max<a[i][m]){
        max=a[i][m];
        k=m;
        }
	
		}
		//printf("K:");
		//printf("%d", k);
		int y1 = a[i][0];
		int x1=0;
		for (int o = 0; o < f[i]; o++) {
			//printf("joap2");
			if (y1 > a[i][o]) {
				y1 = a[i][o];
				x1 = o;
			}
	    }
		int y2 = a[0][k];
		
		for (int o = 0; o < n; o++) {
			
			//printf("joap3");
			if (k < f[o]) {
				if (y2 > a[o][k]) {
					y2 = a[o][k];
					
				}
			}
		} 
		
		if (y1 < y2) l = x1;
		else l = k;
		//printf("%3d",l);
		b[i] = 0;
        for (int j = 0; j <=l; j++) {
			if (j < n) {
				//printf("joap4");
				int hop = k;

				if (f[j] - 1 < hop) hop = f[j] - 1;
				b[i] += a[i][j] * a[j][hop];
			}
        }
    }
	for (int i = 0; i < n; i++) {
		free(a[i]);
	}
	free(f);
	free(a);

	printf("Итоговый вектор b: ");
	for (int i = 0; i < n; i++) {
		
		printf("%d", b[i]);
        printf("%c", ' ');
    }
	free(b);
	return 0;
}
