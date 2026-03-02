//
#include <stdio.h>
#include <string.h>
int main()
{
    char s1[]="Вася";
    char s2[]="Петя";
    if (0 == strcmp(s1,s2))
    	printf("Строки %s и %s одинаковы", s1, s2);
    else printf("Строки %s и %s разные", s1, s2);
}
