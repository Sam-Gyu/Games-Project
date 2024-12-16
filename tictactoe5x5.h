#ifndef UNTITLED18_TICTACTOE3_H
#define UNTITLED18_TICTACTOE3_H

#include "BoardGame_Classes.h"

#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype> // for toupper()
#include <cstdlib> // for rand()

using namespace std;

Player<char>* globalplayers[2];

template <typename T>
class X_O_Board : public Board<T> {
public:
    int count_x; // Count for X three-in-a-rows
    int count_o; // Count for O three-in-a-rows
    int calculate_win_counts(); // Helper to calculate counts

    X_O_Board();
    ~X_O_Board(); // Destructor
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
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    count_x = 0;
    count_o = 0;
}

// Destructor for X_O_Board
template <typename T>
X_O_Board<T>::~X_O_Board() {
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

// Update the board
template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && (this->board[x][y] == 0 || mark == 0)) {
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

// Display the board
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

// Calculate three-in-a-row counts for X and O
template <typename T>
int X_O_Board<T>::calculate_win_counts() {
    count_x = 0;
    count_o = 0;

    // Check rows and columns for three-in-a-row
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= 2; j++) { // Check for three consecutive cells
            // Rows
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2]) {
                if (this->board[i][j] == 'X') count_x++;
                else if (this->board[i][j] == 'O') count_o++;
            }
            // Columns
            if (this->board[j][i] != 0 && this->board[j][i] == this->board[j + 1][i] && this->board[j][i] == this->board[j + 2][i]) {
                if (this->board[j][i] == 'X') count_x++;
                else if (this->board[j][i] == 'O') count_o++;
            }
        }
    }

    // Check diagonals for three-in-a-row
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            // Main diagonal (\)
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i][j] == this->board[i + 2][j + 2]) {
                if (this->board[i][j] == 'X') count_x++;
                else if (this->board[i][j] == 'O') count_o++;
            }
            // Anti-diagonal (/)
            if (this->board[i][j + 2] != 0 && this->board[i][j + 2] == this->board[i + 1][j + 1] && this->board[i][j + 2] == this->board[i + 2][j]) {
                if (this->board[i][j + 2] == 'X') count_x++;
                else if (this->board[i][j + 2] == 'O') count_o++;
            }
        }
    }

    // Return winner based on counts
    if (count_x > count_o) {
        return 1;  // X wins
    } else if (count_o > count_x) {
        return 2;  // O wins
    } else {
        return 3;  // Draw
    }
}


template <typename T>
bool X_O_Board<T>::is_win() {
    if (this->n_moves == 24 || this->n_moves == 25) {
        int calc = calculate_win_counts();

        if (calc == 2) {
            return true;
        }
        if (calc == 1) {
            return false;
        }
        if (this->n_moves == 25) {
            return true;
        }
    }
    return false;
}


// Check if the game is a draw
template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 25 && !is_win());
}

// Check if the game is over
template <typename T>
bool X_O_Board<T>::game_is_over() {
    if (this->n_moves == 24) {
        int calc = calculate_win_counts();
        if (calc == 2) {
            cout << "Player O wins!\n";
            return true;
        }
        else if(calc == 1) {
            cout << "Player X wins!\n";
            return true;
        }
        else {
            cout << "Draw!\n";
            return true;
        }
    }
    return (is_win() || is_draw());
}

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Get move from the player
template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    do {
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
        cin >> x >> y;
    } while (x < 0 || x >= 5 || y < 0 || y >= 5);
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

// Get random move for the player
template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 5;  // Get random x coordinate
    y = rand() % 5;  // Get random y coordinate
}

#endif // _3X3X_O_H
#endif //UNTITLED18_TICTACTOE3_H
