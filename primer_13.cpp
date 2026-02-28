// Решето эратосфена
#include <stdio.h>
main()
{
unsigned char *A;
int i, k, N;
printf ("Введите максимальное число ");
scanf ( "%d", &N );
A = new unsigned char[N+1]; // выделить память под массив
if ( A == NULL ) return 1; // выход в случае ошибки
for ( i = 1; i <= N; i ++ ) A[i] = 1;
for ( k = 2; k*k <= N; k ++ )
if ( A[k] != 0 )
for ( i = k+k; i <= N; i += k ) A[i] = 0;
for ( i = 1; i <= N; i ++ )
if ( A[i] == 1 ) printf ( "%d\n", i );
}
