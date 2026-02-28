/*
Задача. Ввести массив из 10 целых чисел из файла input.dat, умножить каждый элемент на
2 и вывести в столбик в файл output.dat
*/
#include <stdio.h>
const int N = 10;
main()
{
int i, A[N];
FILE *fp; // указатель на файл
fp = fopen( "input.txt", "r" ); // открыть файл на чтение
if ( fp == NULL ) { // обработка ошибки
printf("Нет файла данных");
return 1; // выход по ошибке, код ошибки 1
}
for ( i = 0; i < N; i ++ )
if ( 1 != fscanf(fp,"%d",&A[i]) ) { // чтение и обработка
printf("Не хватает данных в файле"); // ошибки
return 1;
}
fclose ( fp ); // закрыть файл
for ( i = 0; i < N; i ++ )
A[i] = A[i] * 2;
fp = fopen( "output.txt", "w" ); // открыть файл на запись
for ( i = 0; i < N; i ++ ) // вывести массив в файл
fprintf ( fp, "%d\n", A[i] ); // в столбик
fclose ( fp );
}
