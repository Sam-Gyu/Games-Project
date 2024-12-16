// game4

#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <fstream>
#include <set>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

template <typename T>
class X_O_Board : public Board<T> {
public:
    X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T> {
public:
    X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool X_O_Board<T>::is_win() {
    // Load valid words from the file
    ifstream ipf("meow.txt");
    if (!ipf.is_open()) {
        cerr << "Error: Could not open file meow.txt" << endl;
        return false;
    }

    set<string> valid_words;
    string word;
    while (getline(ipf, word)) {
        if (word.size() == 3) {
            for (char& c : word) c = toupper(c); // Convert to uppercase for uniform comparison
            valid_words.insert(word);
        }
    }
    ipf.close();

    // Helper lambda to check if a string is a valid word
    auto is_valid_word = [&](const string& str) {
        return valid_words.find(str) != valid_words.end();
    };

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        string row_word = "";
        for (int j = 0; j < this->columns; j++) {
            row_word += this->board[i][j];
        }
        if (is_valid_word(row_word)) {
            cout << "Winner found with row: " << row_word << endl;
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < this->columns; j++) {
        string col_word = "";
        for (int i = 0; i < this->rows; i++) {
            col_word += this->board[i][j];
        }
        if (is_valid_word(col_word)) {
            cout << "Winner found with column: " << col_word << endl;
            return true;
        }
    }

    // Check diagonals
    string diag1 = "", diag2 = "";
    for (int i = 0; i < this->rows; i++) {
        diag1 += this->board[i][i];
        diag2 += this->board[i][this->rows - i - 1];
    }
    if (is_valid_word(diag1)) {
        cout << "Winner found with diagonal: " << diag1 << endl;
        return true;
    }
    if (is_valid_word(diag2)) {
        cout << "Winner found with diagonal: " << diag2 << endl;
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << " enter your character: ";
    cin >> this->symbol;
    this->symbol = toupper(this->symbol);
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}

#endif //_3X3X_O_H