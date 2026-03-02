// Просмотреть строку и заменить А на Б

#include <stdio.h>
int main()
{
	char s[80];
	int i;
	printf("\n Введите строку \n");
	gets(s);
	i=0;
	while (s[i]!='\0')
	{
		if (s[i]=='А')
			s[i]='Б';
		i++;
	}
	puts("Результат: \n");
	puts(s);
	
}


    
   
    
   
