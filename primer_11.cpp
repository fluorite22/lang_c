/*
Работа с двоичными файлами
Задача. В файле input.dat записаны в два столбика пары чисел (x,y). Записать в файл
output.dat в столбик суммы x+y для каждой пары.
*/
#include <stdio.h>
const int N = 10;
main()
{
int i, n, A[N];
FILE *fp; // указатель на файл
fp = fopen( "input.dat", "rb" ); // открыть двоичный файл на чтение
n = fread ( A, sizeof(int), N, fp ); // читаем весь массив
if ( n < N ) { // обработка ошибки
printf("Не хватает данных в файле");
return;
}
fclose ( fp ); // закрыть файл
for ( i = 0; i < N; i ++ )
A[i] = A[i] * 2;
fp = fopen( "output.dat", "wb" ); // открыть двоичный файл на запись
fwrite ( A, sizeof(int), N, fp ); // записать весь массив
fclose ( fp ); // закрыть файл
}