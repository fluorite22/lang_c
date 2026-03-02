// задача Составить программу, которая определяет , сколько цифр
// в символьной строке. Программа должна работать только при вводе пароля "куку"
#include <stdio.h>
#include <string.h>
int main()
{
    char pass[]="куку",
    s[80];
	int i, count=0;
	printf("Введите пароль ");
	gets(s);
	if (strcmp(pass, s) != 0)
	{
		printf("Неверный пароль ");
		return 1;
	}
	printf("Введите строку ");
	gets(s);
	i=0;
	while(s[i]!= '\0') {
		if (s[i] >= '0' && s[i] <= '9')
			count++;
		i++;
	}
	printf("\n Нашли %d цифр", count);
}
	 
    
