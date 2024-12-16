#ifndef UNTITLED30_NUMERICALTICTACTOE_H
#define UNTITLED30_NUMERICALTICTACTOE_H


#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <set>

using namespace std;

// Numerical Tic-Tac-Toe Board Class
template <typename T>
class NumericalBoard : public Board<T> {
private:
    std::set<T> used_numbers; // Track used numbers

public:
    NumericalBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int get_n_moves() const;
};

// Numerical Tic-Tac-Toe Player Class
template <typename T>
class NumericalPlayer : public Player<T> {
public:
    NumericalPlayer(string name, T symbol);
    void getmove(int& x, int& y);
};

// Numerical Tic-Tac-Toe Random Player Class
template <typename T>
class NumericalRandomPlayer : public RandomPlayer<T> {
public:
    NumericalRandomPlayer(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

// Constructor for NumericalBoard
template <typename T>
NumericalBoard<T>::NumericalBoard() {
    this->rows = 3;
    this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0; // Initialize with 0 (empty)
        }
    }
    this->n_moves = 0;
}

// Update board logic
template <typename T>
bool NumericalBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0 || used_numbers.count(symbol)) {
        return false; // Invalid move: out of bounds, position taken, or number already used
    }

    // Enforce odd/even rules
    int current_move = this->n_moves;
    bool is_player1_turn = (current_move % 2 == 0);

    if ((is_player1_turn && symbol % 2 == 0) || (!is_player1_turn && symbol % 2 != 0)) {
        cout << "Invalid number for the current player. Player 1 must play odd numbers, and Player 2 must play even numbers.\n";
        return false;
    }

    this->board[x][y] = symbol;
    used_numbers.insert(symbol);
    this->n_moves++;
    return true;
}


// Display the board
template <typename T>
void NumericalBoard<T>::display_board() {
    cout << "\n   "; // Space before column numbers
    for (int j = 0; j < this->columns; j++) {
        cout << " " << j << "  "; // Print column numbers
    }
    cout << "\n  +" << string(this->columns * 4 - 1, '-') << "+\n"; // Top border line

    for (int i = 0; i < this->rows; i++) {
        cout << i << " |"; // Print row number
        for (int j = 0; j < this->columns; j++) {
            // Display cells as numbers or dots for empty spaces
            cout << " " << (this->board[i][j] == 0 ? '.' : this->board[i][j]) << " |";
        }
        cout << "\n  +" << string(this->columns * 4 - 1, '-') << "+\n"; // Border line between rows
    }
}


// Check if there's a winner
template <typename T>
bool NumericalBoard<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 && this->board[i][0]!=0 && this->board[i][1]!=0 && this->board[i][2] != 0 ) return true;
    }
    for (int j = 0; j < this->columns; ++j) {
        if (this->board[0][j] + this->board[1][j] + this->board[2][j] == 15&& this->board[0][j]!=0 && this->board[1][j]!=0 && this->board[2][j] != 0 ) return true;
    }
    if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15&& this->board[0][0]!=0 && this->board[1][1]!=0 && this->board[2][2] != 0 ) return true;
    if (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15&& this->board[0][2]!=0 && this->board[1][1]!=0 && this->board[2][0] != 0 ) return true;
    return false;
}

template <typename T>
int NumericalBoard<T>::get_n_moves() const {
    return this->n_moves;
}

// Check for a draw
template <typename T>
bool NumericalBoard<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

// Check if the game is over
template <typename T>
bool NumericalBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for NumericalPlayer
template <typename T>
NumericalPlayer<T>::NumericalPlayer(string name, T symbol) : Player<T>(symbol) {
    this->name = name;
}

// Get move from player
template <typename T>
void NumericalPlayer<T>::getmove(int& x, int& y) {
    cout << this->name << ", enter your move (row and column): ";
    cin >> x >> y;
}

// Constructor for NumericalRandomPlayer
template <typename T>
NumericalRandomPlayer<T>::NumericalRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed RNG
}

// Get random move
template <typename T>
void NumericalRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % 3;
    cout << this->name << " chooses: (" << x << ", " << y << ")\n";
}



#endif // UNTITLED30_NUMERICALTICTACTOE_H
