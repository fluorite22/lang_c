#include <stdio.h>

int main()
{
    char s[80];
    int i;
    FILE *fin, *fout;
    
    fin = fopen("input.txt", "r");
    if (fin == NULL) {
        printf("Error: Cannot open input.dat\n");
        return 1;
    }
    
    fout = fopen("output.txt", "w");
    if (fout == NULL) {
        printf("Error: Cannot create output.dat\n");
        fclose(fin);
        return 1;
    }
    
    while (fgets(s, 80, fin) != NULL) {
        i = 0;
        while (s[i] != '\0') {
            // Русская 'А' в Windows-1251 имеет код 0xC0
            // Русская 'Б' в Windows-1251 имеет код 0xC1
            if (s[i] == 0xC0) {  // 'А' в кодировке CP1251
                s[i] = 0xC1;      // 'Б' в кодировке CP1251
            }
            i++;
        }
        fprintf(fout, "%s", s);
    }
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}
