// Минимальный элемент
// Задача. Найти и вывести на экран минимальный элемент в массиве А


#include <stdio.h>
const int N = 10;
int main()
{
	int i, A[N], min;
	// Ввод элементов массива
    printf("Введите %d элементов массива:\n", N);
    for (i = 0; i < N; i++) {
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }
    
    
    min = A[0];
    for (i=1; i<N; i++)
    	if (A[i]<min)
    		min=A[i];
    printf("\n Минимальный элемент %d", min);
    
}
   
