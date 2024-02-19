#include <iostream>
using namespace std;


int board[8][8];
const int QUEEN = -1;


void resetBoard();
void showBoard();
bool checkQueen(int i);
void setQueen(int i, int j);
void deleteQueen(int i, int j);


int main() {
	resetBoard();
	checkQueen(0);
	showBoard();

	return 0;
}


void resetBoard() {
	int board[8][8] = {0};
}


void showBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == QUEEN) {
				cout << "[Q] ";
			}
			else {
				cout << "[ ] ";
			}
		}
		cout << endl;
	}
}


void setQueen(int x, int j) {
	int d; 
	for (int i = 0; i < 8; ++i) { 
		board[i][j]++;              //указываем на клетку, атакуемую по вертикали
		board[x][i]++;              //указываем на клетку по горизонтали

		d = j - i + x;              //вычисляем 1 диагональ
		if (d >= 0 && d < 8) {      
			board[i][d]++;
		}
		d = j + i - x;              //вычисляем 2 диагональ

		if (d >= 0 && d < 8) {
			board[i][d]++;
		}
	}
	board[x][j] = QUEEN;
}


void deleteQueen(int x, int j) {
	int d;
	for (int i = 0; i < 8; ++i) { 
		board[i][j]--;                  //указываем на клетку, атакуемую по вертикали
		board[x][i]--;                  //указываем на клетку, атакуемую по горизонтали

		d = j - x + i;                  //вычисляем 1 диагональ
		if (d >= 0 && d < 8) { 
			board[i][d]--;
		}
		d = j + x - i;                  //вычисляем 2 диагональ

		if (d >= 0 && d < 8) {
			board[i][d]--;
		}
	}
	board[x][j] = 0;
}

 
bool checkQueen(int i) {
	bool result = false;
	for (int j = 0; j < 8; ++j) {
		if (board[i][j] == 0) {
			setQueen(i, j);         //пробуем поставить ферзя и разметить клетки под боем  

			if (i == 7) { 
                result = true; 
            }
			else if (!(result = checkQueen(i + 1))) { 
                deleteQueen(i, j); 
            }
		
		}
		if (result) {
			break;
		}
	}
	return result;  
}

