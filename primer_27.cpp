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
    if (strcmp(s1,s2) <= 0)
    	printf("%s\n%s",s1,s2);
    else printf("%s\n%s",s2,s1);
    
}
