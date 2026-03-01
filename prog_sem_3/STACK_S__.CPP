#include <iostream>
#include <conio.h>
using namespace std;

struct pointer {
    int d;
    pointer *p;
};

// Создание первого элемента стека
void FormSt(pointer **ph, int data) {
    *ph = new pointer;
    (*ph)->d = data;
    (*ph)->p = NULL;
}

// Добавление элемента в вершину стека
void DobSt(pointer **ph, int data) {
    pointer *px = new pointer;
    px->d = data;
    px->p = *ph;
    *ph = px;
}

// Извлечение элемента из вершины стека
void IskSt(pointer **ph, int &data) {
    data = (*ph)->d;
    *ph = (*ph)->p;
}

// Вывод стека без изменения (только просмотр)
void PrintStack(pointer *ph) {
    if (ph == NULL) {
        cout << "Стек пуст!\n";
        return;
    }
    
    cout << "\nСодержимое стека (сверху вниз):\n";
    pointer *current = ph;
    int i = 1;
    while (current != NULL) {
        cout << i << ". " << current->d << "\n";
        current = current->p;
        i++;
    }
}

// Очистка стека (освобождение памяти)
void ClearStack(pointer **ph) {
    int data;
    while (*ph != NULL) {
        IskSt(ph, data); // извлекаем и удаляем элементы
    }
    cout << "Стек очищен!\n";
}

// Получение количества элементов в стеке
int StackSize(pointer *ph) {
    int count = 0;
    pointer *current = ph;
    while (current != NULL) {
        count++;
        current = current->p;
    }
    return count;
}

// Меню программы
void ShowMenu() {
    system("cls");
    cout << "=== МЕНЮ УПРАВЛЕНИЯ СТЕКОМ ===\n\n";
    cout << "1. Добавить элемент в стек\n";
    cout << "2. Извлечь и вывести все элементы стека\n";
    cout << "3. Просмотреть содержимое стека\n";
    cout << "4. Показать количество элементов\n";
    cout << "5. Очистить стек\n";
    cout << "6. Выйти из программы\n";
    cout << "\nВыберите операцию (1-6): ";
}

int main() {
    pointer *ph = NULL; // указатель на вершину стека
    int choice, data;
    
    do {
        ShowMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Введите значение для добавления: ";
                cin >> data;
                if (ph == NULL) {
                    FormSt(&ph, data);
            } else {
                DobSt(&ph, data);
            }
            cout << "Элемент " << data << " добавлен в стек!\n";
            break;
            
            case 2:
                if (ph == NULL) {
                    cout << "Стек пуст, нечего извлекать!\n";
                } else {
                    cout << "\nИзвлечение и вывод элементов стека:\n";
            int i = 1;
            while (ph != NULL) {
                IskSt(&ph, data);
                cout << i << ". Извлечён элемент: " << data << "\n";
                i++;
            }
        }
        break;
        
        case 3:
            PrintStack(ph);
            break;
        
        case 4:
            cout << "Количество элементов в стеке: " << StackSize(ph) << "\n";
            break;
        
        case 5:
            ClearStack(&ph);
            break;
        
        case 6:
            cout << "Выход из программы...\n";
            ClearStack(&ph); // очистка памяти перед выходом
            break;
        
        default:
            cout << "Неверный выбор! Попробуйте ещё раз.\n";
            break;
        }
        
        if (choice != 6) {
            cout << "\nНажмите любую клавишу для продолжения...";
            getch();
        }
    } while (choice != 6);
    
    return 0;
}
