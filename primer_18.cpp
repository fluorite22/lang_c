// Минимальный элемент
// Задача. Найти и вывести на экран минимальный элемент в массиве А и его номер


#include <stdio.h>
const int N = 10;
int main()
{
	int i, A[N], nMin;
	// Ввод элементов массива
    printf("Введите %d элементов массива:\n", N);
    for (i = 0; i < N; i++) {
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }
    
    
    nMin = 0;
    for (i=1; i<N; i++)
    	if (A[i]< A[nMin])
    		nMin = i;
    printf("\n Минимальный элемент A[%d]=%d", nMin, A[nMin]);
    
}
   
