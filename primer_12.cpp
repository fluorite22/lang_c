/*
Массив неизвестного размера
Задача. В файле input.dat записаны в два столбика пары чисел (x,y). Записать в файл
output.dat в столбик суммы x+y для каждой пары.
*/
#include <stdio.h>
main()
{
int n, x, y, sum;
FILE *fin, *fout; // указатели на файлы
fin = fopen( "input.dat", "r" ); // открыть файл на чтение
fout = fopen( "output.dat", "w" ); // открыть файл на запись
while ( 1 ) {
n = fscanf ( fin, "%d%d", &x, &y );
if ( n < 2 ) break; // данные ошибочны или нет больше данных
sum = x + y;
fprintf ( fout, "%d\n", sum );
}
fclose ( fout ); // закрыть файлы
fclose ( fin );
}
