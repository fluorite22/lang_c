#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    char S[256];  // строка для вопроса
    int randomAnswer;
    
    srand(time(NULL));  // чтобы случайный ряд не повторялся
    
    do {
        printf("Ваш вопрос: ");
        fgets(S, sizeof(S), stdin);
        
        // Убираем символ новой строки в конце
        S[strcspn(S, "\n")] = '\0';
        
        if (strlen(S) == 0) break;  // завершение цикла, если строка пуста
        
        randomAnswer = rand() % 5;  // случайное число от 0 до 4
        
        switch (randomAnswer) {
            case 0:
                strcpy(S, "Когда рак на горе свиснет");
                break;
            case 1:
                strcpy(S, "После дождика в четверг");
                break;
            case 2:
                strcpy(S, "За углом налево");
                break;
            case 3:
                strcpy(S, "Это элементарно, Ватсон!");
                break;
            default:
                strcpy(S, "Не знаю, я не местный");
                break;
        }
        
        printf("%s\n", S);  // печать ответа
        
    } while (1);  // бесконечный цикл
    
    return 0;
}
