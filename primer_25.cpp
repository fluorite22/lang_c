//Задача. В текстовом файле input.dat записаны строки текста
// Вывести в файл output.dat в столбик длины этих строк
#include <stdio.h>
#include <string.h>
int main()
{
    char s[80];
    FILE *fin, *fout;
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    while (NULL != fgets(s, 80, fin))
	{
		fprintf(fout, "%d\n", strlen(s));
	}
	fclose(fin);
	fclose(fout);
}
