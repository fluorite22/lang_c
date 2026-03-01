// ћетод пузырька


#include <stdio.h>
const int N = 10;
int main()
{
	int i, j, A[N], c;
	
	// ¬вод элементов массива
    printf("¬ведите %d элементов массива:\n", N);
    for (i = 0; i < N; i++) {
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }
    
	for (i=0; i<N-1; i++)
		for (j=N-2; j>=i;j--)
			if (A[j]>A[j+1])
			{
				c=A[j]; A[j]=A[j+1];
				A[j+1] = c;
			}
	
	printf("\n ќтсортированный массив: \n");
	for (i=0; i<N; i++)
		printf("%d ", A[i]);
}

    
   
    
   
