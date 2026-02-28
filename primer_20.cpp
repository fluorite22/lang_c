// ÷иклический сдвиг


#include <stdio.h>
const int N = 10;
int main()
{
	int i, A[N], c;
	
	// ¬вод элементов массива
    printf("¬ведите %d элементов массива:\n", N);
    for (i = 0; i < N; i++) {
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }
    
    c=A[N-1];
    
    for (i=N-1; i>0; i--)
    	A[i]=A[i-1];
    A[0]=c;
    printf("\n –езультат: \n");
    for (i=0; i<N; i++)
    	printf("%d ", A[i]);
	}
    
   
