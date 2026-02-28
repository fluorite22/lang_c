#include <stdio.h>
#include <conio.h>
main()
{
float A, B;
printf ("Введите A и B :");
scanf ( "%f%f", &A, &B );
if ( A > B )
{
printf ( "Наибольшее %f",
A );
}
else
{
printf ( "Наибольшее %f",
B );
}
getch();
}