#include <iostream>
using namespace std;


int board[8][8] = {0}; 


void setQueen(int i, int j);
void removeQueen(int i, int j);
void printPosition();
void solve(int i);


int main() {
    solve(0);
}


void setQueen(int i, int j) {
    for (int x = 0; x < 8; x++) {
        board[x][j]++;
        board[i][x]++;
        if (i + j - x >= 0 && i + j - x < 8) {
            board[i + j - x][x]++;
        }
        if (i - j + x >= 0 && i - j + x < 8) {
            board[i - j + x][x]++;
        }
    }

    board[i][j] = -1;
}


void removeQueen(int i, int j) {
    for (int x = 0; x < 8; x++) {
        board[x][j]--;
        board[i][x]--;
        if (i + j - x >= 0 && i + j - x < 8) {
            board[i + j - x][x]--;
        }
        if (i - j + x >= 0 && i - j + x < 8) {
            board[i - j + x][x]--;
        }
    }

    board[i][j] = 0;
}


void printPosition() {
    char alphabet[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char line[8];
    int column[8];
    int index = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == -1) {
                line[index] = alphabet[j];
                column[index] = i + 1;
                index++;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        cout << line[i] << column[i] << " ";
    }
    cout << endl;
}


void solve(int i) {
    for (int j = 0; j < 8; j++) {
        if (board[i][j] == 0) {
            setQueen(i, j);
            if (i == 7) {
                printPosition();
            }
            else {
                solve(i + 1);
            }
            removeQueen(i, j);
        }
    }
}