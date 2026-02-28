// Перестановка наоброт (инверсия)


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
    
    
    for (i=0; i< N/2; i++)
    {
    	c=A[i];
    	A[i]=A[N-1-i];
    	A[N-1-i]=c;
    }
    printf("\n Результат: \n");
    for (i=0; i<N; i++)
    	printf("%d", A[i]);

}


   
