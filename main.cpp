#ifdef _WIN32
#include <windows.h>
#endif

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Board.h"
#include "MoveGenerator.h"
#include "Player.h"

using namespace std;

const int MAX_SIZE = 20;

void playGame(int n, int k)
{
    Board board(n, k);
    mt19937 rng(random_device{}());
    MoveGenerator playerX = player(board, 'X', 'O', rng);
    MoveGenerator playerO = player(board, 'O', 'X', rng);
    MoveGenerator* players[2] = {&playerX, &playerO};
    const char symbols[2] = {'X', 'O'};

    cout << "\nПоле " << n << "x" << n << ", для перемоги потрібно " << k << " в ряд\n\n";
    for (int turn = 0;; turn++) {
        int p = turn % 2;
        if (!players[p]->next()) {
            throw logic_error("сопрограма завершилась без ходу");
        }
        Move move = players[p]->value();
        board.put(move, symbols[p]);
        cout << "Хід " << turn + 1 << ": " << symbols[p] << " -> рядок " << move.row + 1
             << ", стовпець " << move.col + 1 << "\n";
        board.print();

        if (board.isWinning(move, symbols[p])) {
            cout << "Переміг " << symbols[p] << "!\n";
            return;
        }
        if (board.isFull()) {
            cout << "Нічия!\n";
            return;
        }
    }
}

bool readInt(const string& text, int& value)
{
    istringstream in(text);
    char extra;
    return (in >> value) && !(in >> extra);
}

int askNumber(const string& prompt, int minValue, int maxValue)
{
    while (true) {
        cout << prompt << " (від " << minValue << " до " << maxValue << "): ";
        string line;
        if (!getline(cin, line)) {
            throw runtime_error("введення перервано");
        }
        int value;
        if (readInt(line, value) && value >= minValue && value <= maxValue) {
            return value;
        }
        cout << "Помилка: потрібно ціле число від " << minValue << " до " << maxValue << ". Спробуйте ще раз.\n";
    }
}

void readFromKeyboard(int& n, int& k)
{
    n = askNumber("Введіть розмір поля n", 1, MAX_SIZE);
    k = askNumber("Скільки знаків у ряд потрібно для перемоги", 1, n);
}

void readFromFile(const string& fileName, int& n, int& k)
{
    ifstream file(fileName);
    if (!file) {
        throw runtime_error("не вдалося відкрити файл " + fileName);
    }
    string first, second, extra;
    if (!(file >> first >> second)) {
        throw runtime_error("у файлі мають бути два числа: n і k");
    }
    if (file >> extra) {
        throw runtime_error("у файлі є зайві дані: " + extra);
    }
    if (!readInt(first, n) || n < 1 || n > MAX_SIZE) {
        throw runtime_error("n має бути цілим числом від 1 до " + to_string(MAX_SIZE));
    }
    if (!readInt(second, k) || k < 1 || k > n) {
        throw runtime_error("k має бути цілим числом від 1 до n");
    }
}

int main(int argc, char* argv[])
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    try {
        int n, k;
        if (argc == 1) {
            readFromKeyboard(n, k);
        } else if (argc == 2) {
            readFromFile(argv[1], n, k);
        } else {
            cout << "Використання: tictactoe.exe [файл]\n";
            return 1;
        }
        playGame(n, k);
    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
