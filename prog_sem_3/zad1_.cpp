/*Написать программу для вычисления стоимости покупки,
состоящей из нескольких тетрадей и карандашей.
Исходные данные: Стоимость одной тетради и одного карандаша.
Количество карандашей */
#include <stdio.h>
#include <conio.h>
#include <math.h>
int main()
{
    float st_tet, st_kar;
    int kol_tet, kol_kar;
    printf("Стоимость покупки\n");
    printf("Введите стоимость тетради и карандаша\n");
    scanf("%f%f", &st_tet, &st_kar);
    printf("Введите количество тетрадей и карандашей\n");
    scanf("%i%i", &kol_tet, &kol_kar);
    float S=kol_tet*st_tet+kol_kar*st_kar;
    printf("Стоимость покупки = %f\n", S);
    getch();
    return 0;
}
