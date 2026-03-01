#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Определяем константы
#define DECK_SIZE 36
#define SUITS 4
#define RANKS 9
#define HAND_SIZE 6
#define MAX_NAME 50

// Структуры данных
typedef struct {
    char rank[3];   // 6,7,8,9,10,J,Q,K,A
    char suit[9];   // Hearts, Diamonds, Clubs, Spades
    int value;      // 6-14 для сравнения
} Card;

typedef struct {
    Card cards[DECK_SIZE];
    int size;
} Deck;

typedef struct {
    Card cards[HAND_SIZE * 2];  // Максимально возможное количество карт
    int size;
    char name[MAX_NAME];
    int is_human;
} Player;

typedef struct {
    Card cards[DECK_SIZE];
    int size;
    Card trump_card;
} DiscardPile;

// Глобальные переменные
Deck deck;
Player player, computer;
DiscardPile discard;
Card trump;
int current_player;  // 0 - игрок, 1 - компьютер
int attacker;        // кто атакует

// Прототипы функций
void initialize_game(void);
void create_deck(void);
void shuffle_deck(void);
void deal_cards(void);
void show_hand(Player p);
void show_table(void);
void player_turn(void);
void computer_turn(void);
int is_valid_attack(Card card);
int is_valid_defense(Card attack, Card defense);
void draw_cards(void);
int game_over(void);
void determine_trump(void);
void sort_hand(Player *p);
void clear_screen(void);
void wait_for_enter(void);

// Главная функция
int main() {
    char choice;
    int play_again = 1;
    
    srand(time(NULL));
    
    printf("=== Добро пожаловать в игру Дурак ===\n\n");
    printf("Введите ваше имя: ");
    fgets(player.name, MAX_NAME, stdin);
    player.name[strcspn(player.name, "\n")] = 0;  // Удаляем символ новой строки
    
    player.is_human = 1;
    computer.is_human = 0;
    strcpy(computer.name, "Компьютер");
    
    do {
        initialize_game();
        
        // Основной игровой цикл
        while (!game_over()) {
            clear_screen();
            printf("\n=== Раунд ===\n");
            printf("Козырь: %s %s\n\n", trump.rank, trump.suit);
            
            printf("Карт в колоде: %d\n", deck.size);
            printf("Карт в бите: %d\n\n", discard.size);
            
            show_table();
            
            printf("\n--- Ваши карты ---\n");
            show_hand(player);
            
            printf("\n--- Карты компьютера ---\n");
            printf("[%d карт]\n\n", computer.size);
            
            if (current_player == 0) {
                printf("Ваш ход!\n");
                player_turn();
            } else {
                printf("Ход компьютера...\n");
                computer_turn();
                wait_for_enter();
            }
        }
        
        // Определение победителя
        clear_screen();
        if (player.size == 0) {
            printf("\nПОЗДРАВЛЯЮ! Вы выиграли!\n");
        } else {
            printf("\nКомпьютер выиграл. Попробуйте ещё раз!\n");
        }
        
        printf("\nХотите сыграть ещё раз? (y/n): ");
        scanf(" %c", &choice);
        while (getchar() != '\n'); // очищаем буфер
        play_again = (tolower(choice) == 'y');
        
    } while (play_again);
    
    return 0;
}

// Инициализация игры
void initialize_game(void) {
    int i;
    int min_player, min_computer;
    
    create_deck();
    shuffle_deck();
    
    player.size = 0;
    computer.size = 0;
    discard.size = 0;
    
    determine_trump();
    deal_cards();
    
    // Определяем первого атакующего
    // У кого меньший козырь
    min_player = 15;
    min_computer = 15;
    
    for (i = 0; i < player.size; i++) {
        if (strcmp(player.cards[i].suit, trump.suit) == 0 && player.cards[i].value < min_player) {
            min_player = player.cards[i].value;
        }
    }
    
    for (i = 0; i < computer.size; i++) {
        if (strcmp(computer.cards[i].suit, trump.suit) == 0 && computer.cards[i].value < min_computer) {
            min_computer = computer.cards[i].value;
        }
    }
    
    if (min_player == 15) min_player = 100;  // Нет козыря
    if (min_computer == 15) min_computer = 100;
    
    attacker = (min_player < min_computer) ? 0 : 1;
    current_player = attacker;
}

// Создание колоды
void create_deck(void) {
    char *ranks[] = {"6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    char *suits[] = {"Chervi", "Bubi", "Trefi", "Piki"};  // Без символов мастей
    int values[] = {6, 7, 8, 9, 10, 11, 12, 13, 14};
    int index, s, r;
    
    index = 0;
    for (s = 0; s < SUITS; s++) {
        for (r = 0; r < RANKS; r++) {
            strcpy(deck.cards[index].rank, ranks[r]);
            strcpy(deck.cards[index].suit, suits[s]);
            deck.cards[index].value = values[r];
            index++;
        }
    }
    deck.size = DECK_SIZE;
}

// Перемешивание колоды
void shuffle_deck(void) {
    int i;
    for (i = deck.size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = deck.cards[i];
        deck.cards[i] = deck.cards[j];
        deck.cards[j] = temp;
    }
}

// Определение козыря
void determine_trump(void) {
    trump = deck.cards[deck.size - 1];
}

// Раздача карт
void deal_cards(void) {
    int i;
    
    // Раздаём по 6 карт
    for (i = 0; i < HAND_SIZE; i++) {
        if (deck.size > 0) {
            player.cards[player.size++] = deck.cards[--deck.size];
        }
        if (deck.size > 0) {
            computer.cards[computer.size++] = deck.cards[--deck.size];
        }
    }
    
    sort_hand(&player);
    sort_hand(&computer);
}

// Сортировка карт в руке
void sort_hand(Player *p) {
    int i, j;
    for (i = 0; i < p->size - 1; i++) {
        for (j = 0; j < p->size - i - 1; j++) {
            if (p->cards[j].value > p->cards[j + 1].value ||
                (p->cards[j].value == p->cards[j + 1].value && 
                 strcmp(p->cards[j].suit, p->cards[j + 1].suit) > 0)) {
                Card temp = p->cards[j];
                p->cards[j] = p->cards[j + 1];
                p->cards[j + 1] = temp;
            }
        }
    }
}

// Показ руки игрока
void show_hand(Player p) {
    int i;
    for (i = 0; i < p.size; i++) {
        printf("%d. %s %s\n", i + 1, p.cards[i].rank, p.cards[i].suit);
    }
}

// Показ стола (текущие карты)
void show_table(void) {
    int i;
    
    if (discard.size == 0) {
        printf("Стол пуст\n");
        return;
    }
    
    printf("Карты на столе:\n");
    for (i = 0; i < discard.size; i += 2) {
        printf("Атака: %s %s", discard.cards[i].rank, discard.cards[i].suit);
        if (i + 1 < discard.size) {
            printf(" - Защита: %s %s", discard.cards[i + 1].rank, discard.cards[i + 1].suit);
        }
        printf("\n");
    }
}

// Ход игрока
void player_turn(void) {
    int choice;
    int i;
    
    if (current_player == attacker) {
        // Атака
        printf("Выберите карту для атаки (1-%d) или 0 для пропуска: ", player.size);
        scanf("%d", &choice);
        
        if (choice == 0) {
            // Пропуск хода
            printf("Вы пропускаете ход\n");
            current_player = 1 - current_player;
            return;
        }
        
        if (choice < 1 || choice > player.size) {
            printf("Неверный выбор!\n");
            wait_for_enter();
            return;
        }
        
        Card selected = player.cards[choice - 1];
        
        // Проверка валидности атаки
        if (discard.size == 0 || is_valid_attack(selected)) {
            // Добавляем карту на стол
            discard.cards[discard.size++] = selected;
            
            // Удаляем из руки
            for (i = choice - 1; i < player.size - 1; i++) {
                player.cards[i] = player.cards[i + 1];
            }
            player.size--;
            
            // Передаём ход защитнику
            current_player = 1 - current_player;
        } else {
            printf("Нельзя атаковать этой картой!\n");
            wait_for_enter();
        }
    } else {
        // Защита
        if (discard.size % 2 == 1) {  // Есть карта для отбития
            Card attack = discard.cards[discard.size - 1];
            
            printf("Отбейтесь от %s %s\n", attack.rank, attack.suit);
            printf("Выберите карту (1-%d) или 0 чтобы взять: ", player.size);
            scanf("%d", &choice);
            
            if (choice == 0) {
                // Берём все карты со стола
                for (i = 0; i < discard.size; i++) {
                    player.cards[player.size++] = discard.cards[i];
                }
                discard.size = 0;
                attacker = 1 - attacker;  // Меняем атакующего
                current_player = attacker;
                sort_hand(&player);
                return;
            }
            
            if (choice < 1 || choice > player.size) {
                printf("Неверный выбор!\n");
                wait_for_enter();
                return;
            }
            
            Card defense = player.cards[choice - 1];
            
            if (is_valid_defense(attack, defense)) {
                // Добавляем защиту на стол
                discard.cards[discard.size++] = defense;
                
                // Удаляем из руки
                for (i = choice - 1; i < player.size - 1; i++) {
                    player.cards[i] = player.cards[i + 1];
                }
                player.size--;
                
                // Проверяем, закончился ли ход
                if (discard.size % 2 == 0) {
                    // Все карты отбиты, ход закончен
                    // Сбрасываем карты со стола
                    discard.size = 0;
                    attacker = 1 - attacker;
                    current_player = attacker;
                    
                    // Добираем карты
                    draw_cards();
                } else {
                    // Можно подкинуть ещё
                    current_player = attacker;
                }
            } else {
                printf("Нельзя отбиться этой картой!\n");
                wait_for_enter();
            }
        }
    }
}

// Ход компьютера (упрощённая логика)
void computer_turn(void) {
    int i;
    
    if (current_player == attacker) {
        // Компьютер атакует
        if (computer.size > 0) {
            // Выбирает самую маленькую карту для атаки
            Card selected = computer.cards[0];
            
            // Проверка валидности
            if (discard.size == 0 || is_valid_attack(selected)) {
                printf("Компьютер атакует картой %s %s\n", selected.rank, selected.suit);
                discard.cards[discard.size++] = selected;
                
                // Удаляем из руки
                for (i = 0; i < computer.size - 1; i++) {
                    computer.cards[i] = computer.cards[i + 1];
                }
                computer.size--;
                
                current_player = 1 - current_player;
            }
        }
    } else {
        // Компьютер защищается
        if (discard.size % 2 == 1) {
            Card attack = discard.cards[discard.size - 1];
            
            // Ищем карту для защиты
            int defense_index = -1;
            for (i = 0; i < computer.size; i++) {
                if (is_valid_defense(attack, computer.cards[i])) {
                    defense_index = i;
                    break;
                }
            }
            
            if (defense_index != -1) {
                // Нашли карту для защиты
                Card defense = computer.cards[defense_index];
                printf("Компьютер защищается картой %s %s\n", defense.rank, defense.suit);
                discard.cards[discard.size++] = defense;
                
                // Удаляем из руки
                for (i = defense_index; i < computer.size - 1; i++) {
                    computer.cards[i] = computer.cards[i + 1];
                }
                computer.size--;
                
                if (discard.size % 2 == 0) {
                    // Все карты отбиты
                    discard.size = 0;
                    attacker = 1 - attacker;
                    current_player = attacker;
                    draw_cards();
                } else {
                    current_player = attacker;
                }
            } else {
                // Нечем защищаться - берём карты
                printf("Компьютер берёт карты\n");
                for (i = 0; i < discard.size; i++) {
                    computer.cards[computer.size++] = discard.cards[i];
                }
                discard.size = 0;
                attacker = 1 - attacker;
                current_player = attacker;
                sort_hand(&computer);
            }
        }
    }
}

// Проверка валидности атаки
int is_valid_attack(Card card) {
    int i;
    
    if (discard.size == 0) return 1;  // Первая атака
    
    // Можно подкинуть карту того же ранга, что уже есть на столе
    for (i = 0; i < discard.size; i++) {
        if (discard.cards[i].value == card.value) {
            return 1;
        }
    }
    return 0;
}

// Проверка валидности защиты
int is_valid_defense(Card attack, Card defense) {
    // Можно покрыть той же мастью старшей картой
    if (strcmp(defense.suit, attack.suit) == 0 && defense.value > attack.value) {
        return 1;
    }
    
    // Или козырем (если атака не козырь)
    if (strcmp(defense.suit, trump.suit) == 0 && strcmp(attack.suit, trump.suit) != 0) {
        return 1;
    }
    
    return 0;
}

// Добор карт
void draw_cards(void) {
    // Игрок добирает до 6
    while (player.size < HAND_SIZE && deck.size > 0) {
        player.cards[player.size++] = deck.cards[--deck.size];
    }
    
    // Компьютер добирает до 6
    while (computer.size < HAND_SIZE && deck.size > 0) {
        computer.cards[computer.size++] = deck.cards[--deck.size];
    }
    
    sort_hand(&player);
    sort_hand(&computer);
}

// Проверка окончания игры
int game_over(void) {
    return (player.size == 0 || computer.size == 0) && deck.size == 0;
}

// Очистка экрана
void clear_screen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Ожидание нажатия Enter
void wait_for_enter(void) {
    printf("\nНажмите Enter для продолжения...");
    while (getchar() != '\n');
    getchar();
}
