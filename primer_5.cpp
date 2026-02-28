#include <stdio.h>
#include <conio.h>
main()
{
int N, sum; // sum - сумма цифр числа
sum = 0; // сначала сумму обнуляем
do { // начало цикла
printf ( "\nВведите натуральное число:" );
scanf ( "%d", &N );
}
while ( N <= 0 ); // условие цикла «пока N <= 0»
while ( N > 0 ) {
sum += N % 10;
N /= 10;
}
printf ( "Сумма цифр этого числа равна %d\n", sum );
getch();
}

