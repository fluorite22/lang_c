// Метод выбора минимального элемента


#include <stdio.h>
const int N = 10;
int main()
{
	int i, A[N], c;
	
	// Ввод элементов массива
    printf("Введите %d элементов массива:\n", N);
    for (i = 0; i < N; i++) {
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }
    
	for (i=0; i<N-1; i++) {
		nMin = i;
		for (j=i+1; j<N; j++)
			if (A[j]<A[nMin])
				nMin = j;
		if (nMin != i) {
			c=A[i]; A[i] =A[nMin];
			A[nMin] = c;
		}
	}
	printf('\n Отсортированный массив: \n';)
	for (i=0; i<N; i++)
		printf("%d", A[i]);
}

    
   
    
   
