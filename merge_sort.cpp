#include <stdio.h>
#include <stdlib.h>

// Функция слияния двух отсортированных подмассивов
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;  // Размер левого подмассива
    int n2 = right - mid;     // Размер правого подмассива
    
    // Создаем временные массивы
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    // Копируем данные во временные массивы
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Слияние временных массивов обратно в arr[left..right]
    i = 0;      // Индекс первого подмассива
    j = 0;      // Индекс второго подмассива
    k = left;   // Индекс основного массива
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Копируем оставшиеся элементы L[], если есть
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Копируем оставшиеся элементы R[], если есть
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Освобождаем память
    free(L);
    free(R);
}

// Рекурсивная функция сортировки слиянием
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Находим среднюю точку
        int mid = left + (right - left) / 2;
        
        // Рекурсивно сортируем первую и вторую половины
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Сливаем отсортированные половины
        merge(arr, left, mid, right);
    }
}

// Упрощенная функция для сортировки всего массива
void sort(int arr[], int n) {
    mergeSort(arr, 0, n - 1);
}

// Функция для печати массива
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Альтернативная версия с использованием одного временного массива
void mergeSortOptimized(int arr[], int temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortOptimized(arr, temp, left, mid);
        mergeSortOptimized(arr, temp, mid + 1, right);
        
        // Слияние с использованием одного временного массива
        for (int i = left; i <= right; i++)
            temp[i] = arr[i];
        
        int i = left;
        int j = mid + 1;
        int k = left;
        
        while (i <= mid && j <= right) {
            if (temp[i] <= temp[j]) {
                arr[k] = temp[i];
                i++;
            } else {
                arr[k] = temp[j];
                j++;
            }
            k++;
        }
        
        while (i <= mid) {
            arr[k] = temp[i];
            i++;
            k++;
        }
    }
}

// Основная функция с примером
int main() {
    // Пример массива из 10 элементов
    int arr[] = {38, 27, 43, 3, 9, 82, 10, 15, 6, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Исходный массив:\n");
    printArray(arr, n);
    
    // Сортируем массив
    sort(arr, n);
    
    printf("\nОтсортированный массив:\n");
    printArray(arr, n);
    
    // Второй пример с другой реализацией
    printf("\n--- Второй пример ---\n");
    int arr2[] = {64, 34, 25, 12, 22, 11, 90, 88, 77, 1};
    int temp[10];  // Временный массив
    
    printf("Исходный массив:\n");
    printArray(arr2, 10);
    
    mergeSortOptimized(arr2, temp, 0, 9);
    
    printf("Отсортированный массив:\n");
    printArray(arr2, 10);
    
    // Пример со случайными числами
    printf("\n--- Пример со случайными числами ---\n");
    int arr3[10];
    
    printf("Случайный массив: ");
    for (int i = 0; i < 10; i++) {
        arr3[i] = rand() % 100;  // Числа от 0 до 99
        printf("%d ", arr3[i]);
    }
    printf("\n");
    
    sort(arr3, 10);
    
    printf("Отсортированный: ");
    printArray(arr3, 10);
    
    return 0;
}
