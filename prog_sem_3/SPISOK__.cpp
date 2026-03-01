#include <iostream>
#include <conio.h>
using namespace std;

struct pointer {
    int d;
    pointer *p;
};

// Создание первого элемента списка
void FormOch(pointer **ph, int data) {
    *ph = new pointer;
    (*ph)->d = data;
    (*ph)->p = NULL;
}

// Добавление элемента в конец списка
void DobOch(pointer **pk, int data) {
    pointer *px = new pointer;
    px->d = data;
    (*pk)->p = px;
    *pk = px;
    (*pk)->p = NULL;
}

// Извлечение элемента из начала списка
void IskOch(pointer **ph, int &data) {
    data = (*ph)->d;
    *ph = (*ph)->p;
}

// Вывод списка
void PrintList(pointer *ph) {
    if (ph == NULL) {
        cout << "Список пуст!\n";
        return;
    }
    
    cout << "\nСодержимое списка:\n";
    pointer *current = ph;
    int i = 1;
    while (current != NULL) {
        cout << i << ". " << current->d << "\n";
        current = current->p;
        i++;
    }
}

// Поиск элемента в списке
bool SearchElement(pointer *ph, int key, pointer **found, pointer **prev) {
    *found = ph;
    *prev = NULL;
    
    while ((*found != NULL) && (key != (*found)->d)) {
        *prev = *found;
        *found = (*found)->p;
    }
    
    return (*found != NULL);
}

// Вставка элемента после найденного
void InsertAfter(pointer **found, int insert) {
    pointer *px = new pointer;
    px->d = insert;
    px->p = (*found)->p;
    (*found)->p = px;
}

// Удаление элемента из списка
bool DeleteElement(pointer **ph, int key) {
    pointer *found, *prev;
    
    if (!SearchElement(*ph, key, &found, &prev)) {
        return false; // элемент не найден
    }
    
    if (prev == NULL) { // удаляем первый элемент
        *ph = found->p;
    } else {
        prev->p = found->p;
    }
    
    delete found; // освобождаем память
    return true;
}

// Очистка списка (освобождение памяти)
void ClearList(pointer **ph) {
    int data;
    while (*ph != NULL) {
        IskOch(ph, data); // извлекаем и удаляем элементы
    }
}

// Меню программы
void ShowMenu() {
    system("cls");
    cout << "=== МЕНЮ УПРАВЛЕНИЯ СПИСКОМ ===\n\n";
    cout << "1. Добавить элемент в список\n";
    cout << "2. Вывести список\n";
    cout << "3. Найти элемент\n";
    cout << "4. Вставить элемент после найденного\n";
    cout << "5. Удалить элемент\n";
    cout << "6. Очистить список\n";
    cout << "7. Выйти из программы\n";
    cout << "\nВыберите операцию (1-7): ";
}

int main() {
    pointer *ph = NULL; // указатель на начало списка
    pointer *pk = NULL; // указатель на конец списка
    int choice, data, key, insert;
    pointer *found, *prev;
    
    do {
        ShowMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Введите значение для добавления: ";
                cin >> data;
                if (ph == NULL) {
                    FormOch(&ph, data);
            pk = ph;
        } else {
            DobOch(&pk, data);
        }
        cout << "Элемент " << data << " добавлен в список!\n";
        break;
        
            case 2:
                PrintList(ph);
                break;
        
            case 3:
                cout << "Введите данные для поиска: ";
                cin >> key;
                if (SearchElement(ph, key, &found, &prev)) {
                    cout << "Элемент " << key << " найден в списке!\n";
        } else {
            cout << "Элемент " << key << " не найден в списке!\n";
        }
        break;
        
            case 4:
                cout << "Введите данные для поиска элемента, после которого вставить: ";
                cin >> key;
                if (SearchElement(ph, key, &found, &prev)) {
            cout << "Введите данные для вставки: ";
            cin >> insert;
            InsertAfter(&found, insert);
            cout << "Элемент " << insert << " вставлен после " << key << "\n";
        } else {
            cout << "Элемент " << key << " не найден, вставка невозможна!\n";
        }
        break;
        
            case 5:
                cout << "Введите данные для удаления: ";
                cin >> key;
                if (DeleteElement(&ph, key)) {
            cout << "Элемент " << key << " удалён из списка!\n";
            // Обновляем указатель на конец списка, если нужно
            if (ph != NULL) {
                pk = ph;
                while (pk->p != NULL) pk = pk->p;
            }
        } else {
            cout << "Элемент " << key << " не найден, удаление невозможно!\n";
        }
        break;
        
            case 6:
                ClearList(&ph);
                pk = NULL;
                cout << "Список очищен!\n";
                break;
        
            case 7:
                cout << "Выход из программы...\n";
                ClearList(&ph); // очистка памяти перед выходом
                break;
        
            default:
                cout << "Неверный выбор! Попробуйте ещё раз.\n";
                break;
        } // конец switch
        
        if (choice != 7) {
            cout << "\nНажмите любую клавишу для продолжения...";
            getch();
        }
    } while (choice != 7); // конец do-while
    
    return 0;
}

