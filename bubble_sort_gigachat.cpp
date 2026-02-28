#include <stdio.h>
#include <conio.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) { // Внешний цикл проходит по массиву столько раз, сколько элементов минус один
        for (int j = 0; j < n-i-1; j++) { // Внутренний цикл каждый раз сокращается, потому что наибольшие элементы постепенно оказываются справа
            if (arr[j] > arr[j+1]) { // Если текущий элемент больше следующего
                // Меняем местами два соседних элемента
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Функция для вывода массива
void printArray(int arr[], int size) {
    for (int i=0; i<size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]); // Определяем размер массива

    printf("Исходный массив:\n");
    printArray(arr, n);
    
    bubbleSort(arr, n); // Сортируем массив методом пузырька

    printf("Отсортированный массив:\n");
    printArray(arr, n);
	
	printf("Нажмите любую клавишу...\n");
	getch();
    return 0;
}
