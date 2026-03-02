// задача. ¬вести с клавиатуры им€ файла. »зменить его расширение на ".exe"

#include <stdio.h>
#include <string.h>
int main()
{
    char s[80];
    int n;
    printf("¬ведите им€ файла ");
    gets(s);
    n=0;
    while (  (s[n] != '.') && (s[n] != '\0' ))
    	n++;
    if (s[n] == '.') 
    	strcpy(s+n, ".exe");
    else strcat(s, ".exe");
    puts(s);
	
}
	 
    
