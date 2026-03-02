// задача ввести две строки и вывести их в алфавитном пор€дке
#include <stdio.h>
#include <string.h>
int main()
{
    char s1[80], s2[80];
    printf("¬ведите первую строку");
    gets(s1);
    printf("¬ведите вторую строку");
    gets(s2);
    if (0 == strncmp(s1,s2, 2))
    	printf("ѕервые два символа %s и %s одинаковы", s1,s2);
    else printf("ѕервые два символа %s и %s разные", s1,s2);
    
}
