#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int A, B, C;  // сомножители и произведение
    
    srand(time(NULL));  // смешиваем «карты»
    
    do {
        A = 1 + rand() % 10;  // от 1 до 10
        B = 1 + rand() % 10;  // от 1 до 10
        
        printf("Сколько будет %d x %d ? ", A, B);
        scanf("%d", &C);
        
        if (C == 0) break;  // завершение цикла, если C=0
        
        // проверяем правильность вычисления
        if (A * B == C) {
            printf("Молодец, правильно!\n");
        } else {
            printf("Ошибка, повтори таблицу умножения!\n");
        }
        
    } while (1);  // бесконечный цикл!
    
    return 0;
}
