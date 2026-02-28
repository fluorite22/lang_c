#include <stdio.h>
#include <conio.h>
main()
{
char c;
printf("\nВведите первую букву:");
scanf("%c", &c); // ввести букву
switch ( c ) // заголовок оператора выбора
{
case 'а': printf("\nАнтилопа"); break;
case 'б': printf("\nБарсук"); break;
case 'в': printf("\nВолк"); break;
default: printf("\nНе знаю я таких!"); // по умолчанию
}
getch();
}