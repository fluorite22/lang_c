#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <ctime>

using namespace std;

struct Cards
{
    string rank, suit;
};

void showAllCard(const vector<Cards> &deck){
    for(int i = 0; i < deck.size(); i++) {
        cout << deck[i].rank << " " << deck[i].suit << endl;
    }
}

void showMyCards(const vector<Cards> &deck) {
    cout << "(";
    for (int i = 0; i < deck.size(); i++) {
        cout << deck[i].rank << deck[i].suit;
        if (i < deck.size() - 1) cout << ", ";
    }
    cout << ")" << endl;
}

void shuffleDeck(vector<Cards> &deck) {
    random_device rd;
    mt19937 seed(rd());
    shuffle(deck.begin(), deck.end(), seed);
}

vector<Cards> giveMeCards(vector<Cards>& deck) {
    vector<Cards> result;
    for (int i = 0; i < 6; i++) {
        if (!deck.empty()) {
            result.push_back(deck.back());
            deck.pop_back();
        }
    }
    return result;
}

int getCardValue(string rank) {
    if (rank == "2") return 2;
    else if (rank == "3") return 3;
    else if (rank == "4") return 4;
    else if (rank == "5") return 5;
    else if (rank == "6") return 6;
    else if (rank == "7") return 7;
    else if (rank == "8") return 8;
    else if (rank == "9") return 9;
    else if (rank == "10") return 10;
    else if (rank == "J") return 11;
    else if (rank == "Q") return 12;
    else if (rank == "K") return 13;
    else if (rank == "A") return 14;
    return 0;
}

bool canBet(Cards atack, Cards defender, string trupm) {
    if (atack.suit == defender.suit) {
        return getCardValue(atack.rank) < getCardValue(defender.rank);
    }
    if (defender.suit == trupm && atack.suit != trupm) {
        return true;
    }
    if (defender.suit != trupm && atack.suit == trupm) {
        return false;
    }
    if (defender.suit == trupm && atack.suit == trupm) {
        return getCardValue(atack.rank) < getCardValue(defender.rank);
    }
    return false;
}

void refillHand(vector<Cards> &deck, vector<Cards> &hand) {
    while (!deck.empty() && hand.size() < 6) {
        hand.push_back(deck.back());
        deck.pop_back();
    }
}

int main(){
    srand(static_cast<unsigned int>(time(nullptr)));
    
    vector<Cards> deck;

    // Названия мастей на русском без символов
    vector<string> const suits = {"Черви", "Буби", "Крести", "Пики"};
    vector<string> const rank = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

    // Создание колоды
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 4; j++){
            deck.push_back({rank[i], suits[j]});
        }
    }

    // Перемешивание
    shuffleDeck(deck);

    // Раздача карт
    vector<Cards> playerHand = giveMeCards(deck);
    vector<Cards> botHand = giveMeCards(deck);

    // Определение козыря
    Cards trumpCard = deck.back();
    deck.pop_back();
    string trumpSuit = trumpCard.suit;
    deck.insert(deck.begin(), trumpCard);
    
    cout << "=== Игра Дурак ===\n\n";
    cout << "Козырь: " << trumpSuit << "\n\n";
    
    cout << "Карты компьютера: ";
    showMyCards(botHand);
    cout << "\n";

    vector<Cards> table;
    bool IsPlayerTurn = true;
    bool IsDeckEmpty = false;

    // Определение первого хода
    const short whoPlayFirst = rand() % 2;
    if (whoPlayFirst == 0) {
        IsPlayerTurn = false;
        cout << "Первым ходит компьютер\n\n";
    } else {
        cout << "Вы ходите первым\n\n";
    }

    // Основной игровой цикл
    while (!playerHand.empty() || !botHand.empty()) {
        int choice;
        
        if (IsPlayerTurn) {
            // Ход игрока (атака)
            table.clear();
            cout << "\n--- Ваш ход ---\n";
            cout << "Ваши карты: ";
            showMyCards(playerHand);
            cout << "Выберите карту для атаки (1-" << playerHand.size() << "): ";
            cin >> choice;

            if (choice < 1 || choice > playerHand.size()) {
                cout << "Неверный выбор!\n";
                continue;
            }

            choice -= 1;
            table.push_back(playerHand[choice]);
            cout << "Вы атакуете: " << playerHand[choice].rank << " " << playerHand[choice].suit << endl;
            playerHand.erase(playerHand.begin() + choice);

            // Компьютер защищается
            bool bootdefeter = false;
            for (int i = 0; i < botHand.size(); i++) {
                if (canBet(table[0], botHand[i], trumpSuit)) {
                    cout << "Компьютер защищается: " << botHand[i].rank << " " << botHand[i].suit << endl;
                    table.push_back(botHand[i]);
                    botHand.erase(botHand.begin() + i);
                    bootdefeter = true;
                    break;
                }
            }
            
            if (!bootdefeter) {
                cout << "Компьютер не может защититься и забирает карты\n";
                for (Cards &card : table) botHand.push_back(card);
                cout << "Карты компьютера теперь: ";
                showMyCards(botHand);
            } else {
                IsPlayerTurn = false;
            }
        }
        else {
            // Ход компьютера (атака)
            table.clear();
            choice = rand() % botHand.size();
            table.push_back(botHand[choice]);
            botHand.erase(botHand.begin() + choice);
            cout << "\n--- Ход компьютера ---\n";
            cout << "Компьютер атакует: " << table[0].rank << " " << table[0].suit << endl;

            cout << "\nВаши карты: ";
            showMyCards(playerHand);
            cout << "Выберите карту для защиты (1-" << playerHand.size() << "), 0 чтобы взять карты: ";
            cin >> choice;

            if (choice == 0) {
                cout << "Вы забираете карты\n";
                for (Cards &card : table) playerHand.push_back(card);
                cout << "Ваши карты теперь: ";
                showMyCards(playerHand);
                table.clear();
            }
            else {
                short choice_d = choice - 1;
                if (choice_d >= 0 && choice_d < playerHand.size() && 
                    canBet(table[0], playerHand[choice_d], trumpSuit)) {
                    cout << "Вы защищаетесь: " << playerHand[choice_d].rank << " " << playerHand[choice_d].suit << endl;
                    playerHand.erase(playerHand.begin() + choice_d);
                    IsPlayerTurn = true;
                }
                else {
                    cout << "Нельзя защититься этой картой, вы забираете карты\n";
                    for (Cards &card : table) playerHand.push_back(card);
                    cout << "Ваши карты теперь: ";
                    showMyCards(playerHand);
                }
            }
        }

        // Проверка на пустую колоду
        if (deck.empty() && !IsDeckEmpty) {
            cout << "\nКолода опустела\n";
            IsDeckEmpty = true;
        }

        // Проверка победителя
        if (playerHand.empty()) {
            cout << "\nПОЗДРАВЛЯЮ! Вы выиграли!\n";
            break;
        }

        if (botHand.empty()) {
            cout << "\nКомпьютер выиграл. Попробуйте ещё раз!\n";
            break;
        }

        // Добор карт
        refillHand(deck, playerHand);
        refillHand(deck, botHand);
    }

    return 0;
}
