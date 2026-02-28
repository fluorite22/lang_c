#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    
    // Пятикратный вызов rand() % 100
    for (int i=0; i<5; i++)
    printf("%d\n", 1+rand() % 10);
    
    // Ожидание ввода (аналог Readln)
    getchar();
    
    return 0;
}
