

#ifndef UNTITLED30_CONNECT4_H
#define UNTITLED30_CONNECT4_H


#include "BoardGame_Classes.h"

template <typename T>
class connect4_Board:public Board<T> {
public:
    connect4_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class connect4_Player : public Player<T> {
public:
    connect4_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class connect4_Random_Player : public RandomPlayer<T>{
public:
    connect4_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
connect4_Board<T>::connect4_Board() {
    this->rows = 6;
    this->columns = 7;
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
bool connect4_Board<T>::update_board(int x, int y, T mark) {
    // تحديث العلامة فقط إذا كانت الحركة صحيحة
    if (y < 0 || y >= this->columns) {
        return false; // عمود خارج النطاق
    }
    for (x = this->rows - 1; x >= 0; x--) { // نبدأ من الأسفل
        if (this->board[x][y] == 0) { // إذا كان الخانة فارغة
            this->board[x][y] = toupper(mark); // وضع العلامة
            this->n_moves++;
            return true;
        }
    }
    return false; // العمود ممتلئ
}

// Display the board and the pieces on it
template <typename T>
void connect4_Board<T>::display_board() {
    cout << "\n   "; // مسافة قبل أرقام الأعمدة
    for (int j = 0; j < this->columns; j++) {
        cout << " " << j << "  "; // طباعة أرقام الأعمدة
    }
    cout << "\n  +" << string(this->columns * 4 - 1, '-') << "+\n"; // خط علوي

    for (int i = 0; i < this->rows; i++) {
        cout << i << " |"; // طباعة رقم الصف
        for (int j = 0; j < this->columns; j++) {
            // إظهار الخانات كعلامات أو فراغات
            cout << " " << (this->board[i][j] == 0 ? '.' : this->board[i][j]) << " |";
        }
        cout << "\n  +" << string(this->columns * 4 - 1, '-') << "+\n"; // خط فاصل بين الصفوف
    }
}


// Returns true if there is any winner
template <typename T>
bool connect4_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 4; ++j) {

            if ((this->board[i][j] != 0 && this->board[i][j] == this->board[i][j+1] && this->board[i][j] == this->board[i][j+2] &&
                 this->board[i][j] == this->board[i][j+3])) {

                return true;
            }
        }
    }

    // Check diagonals
    for(int j = 0; j < this->columns; ++j){
        for (int i =0; i <= this->rows-4; ++i){
            if ((this->board[i][j] == this->board[i+1][j] && this->board[i][j] == this->board[i+2][j] && this->board[i][j] == this->board[i+3][j] && this->board[i][j] != 0)){
                return true;
            }
        }
    }
    for (int i = 0; i <= this->rows - 4; ++i) {
        for (int j = 0; j <= this->columns - 4; ++j) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2] && this->board[i][j] == this->board[i + 3][j + 3]) {
                return true;
            }
        }
    }

    for (int i = 3; i < this->rows; ++i) {
        for (int j = 0; j <= this->columns - 4; ++j) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i - 1][j + 1] &&
                this->board[i][j] == this->board[i - 2][j + 2] && this->board[i][j] == this->board[i - 3][j + 3]) {
                return true;

            }
        }
    }

    return false;

}


// Return true if 9 moves are done and no winner
template <typename T>
bool connect4_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool connect4_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
connect4_Player<T>::connect4_Player(std::string name, T symbol) : Player<T>(symbol) {}

template <typename T>
void connect4_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move  y (0 to 6)  separated by spaces: ";
    x=0;
    cin >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
connect4_Random_Player<T>::connect4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void connect4_Random_Player<T>::getmove(int& x, int& y) {
    this->dimension = 6;
    x = rand() % this->dimension;  // Random number between 0 and 2
    this->dimension = 7;
    y = rand() % this->dimension;
}





#endif //UNTITLED30_CONNECT4_H




