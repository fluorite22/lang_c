#include <stdio.h>
#include <string.h>

int main() {
    char S[256];
    char C;
    int k, L;
    
    do {
        printf("¬ведите строку: ");
        fgets(S, sizeof(S), stdin);
        
        // ”бираем символ новой строки в конце
        S[strcspn(S, "\n")] = '\0';
        
        L = strlen(S);  // определ€ем длину строки
        
        for (k = 0; k < L; k++) {
            C = S[k];  // выбираем очередной символ
            printf("%c\n", C);  // и печатаем его в отдельной строке
        }
        
    } while (L != 0);  // L=0, если строка пуста
    
    return 0;
}
