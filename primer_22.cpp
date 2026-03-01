// Двоичный поиск в массиве
// Работает только на отсортированном массиве

#include <stdio.h>
const int N = 10;
int main()
{
	int i, x, L=0, R=N-1, m, A[N],
	flag =0;
	// Ввод элементов массива
    printf("Введите %d элементов массива:\n", N);
    for (i = 0; i < N; i++) {
        printf("A[%d] = ", i);
        scanf("%d", &A[i]);
    }
	printf("Введите искомый элемент\n");
	scanf("%d", &x);
	while (L<=R) {
		m=(L+R)/2;
		if (A[m]==x) {
			flag=1;
			break;
		}
		if (x<A[m]) R=m-1;
		else L=m+1;
	}
	if (flag)
		printf("Нашли: A[%d]=%d", m, A[m]);
	else printf("Такого элемента нет");
}


    
   
    
   
