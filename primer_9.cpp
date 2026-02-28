#include <stdio.h>
#include <stdlib.h>
const int N = 10;
int random (int N) { return rand() % N; }
main()
{
int i, A[N];
for ( i = 0; i < N; i ++ ) // заполнение массива сл. числами
A[i] = random(26) - 10;
printf("n Исходный массив:\n"); // вывод исходного массива
for ( i = 0; i < N; i ++ )
printf("%d ", A[i]);
for ( i = 0; i < N; i ++ ) // умножить все элементы на 2
A[i] = A[i] * 2;
printf("n Результат:\n");
for ( i = 0; i < N; i ++ ) // вывод результата
printf("%d ", A[i]);
}
