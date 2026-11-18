#include "model.h"
#include "view.h"

void resetData(int &currX, int& currY, int &turn) {
	for(int i = 0; i < boardSize; ++i) {
		for(int j = 0; j < boardSize; ++j) {
			chessBoard[i][j].X = 4 * j + left + 2;
			chessBoard[i][j].Y = 2 * i + top + 1;
			chessBoard[i][j].mark = 0;
		}
	}
	currX = 0;
	currY = 0;
	turn = 1;
}

void checkLegalMove(int &currX, int &currY) {
	if(currX < 0) currX = 0;
	else if(currX > boardSize - 1) currX = boardSize - 1;
	if(currY < 0) currY = 0;
	else if(currY > boardSize - 1) currY = boardSize - 1;

	goToXY(chessBoard[currX][currY].X, chessBoard[currX][currY].Y);
}

int checkDraw() {
	for(int i = 0; i < boardSize; ++i) {
		for(int j = 0; j < boardSize; ++j) {
			if(chessBoard[i][j].mark == 0) return 0;
		}
	}
	return 1;
}

int checkWin(int currX, int currY) {
	int h[] = {0, 0, -1, 1, -1, 1, -1, 1};
	int k[] = {1, -1, 0, 0, -1, 1, 1, -1};
	for(int i = 0; i < 8; ++i) {
		int ver = currY + h[i], hor = currX + k[i];
		if(currX >= 0 && currX < boardSize && currY >= 0 && currY < boardSize && chessBoard[currX][currY].mark == chessBoard[hor][ver].mark) {
			int count = 0, ver2 = 0, hor2 = 0, flag = 1;
			if(i % 2 == 0) {
				ver2 = currY + h[i + 1];
				hor2 = currX + k[i + 1];
				flag = 0;
			}
			int j = 0;
			while(j < 4 && count < 4) {
				if(ver >= 0 && ver < boardSize && hor >= 0 && hor < boardSize && chessBoard[currX][currY].mark == chessBoard[hor][ver].mark) {
					count++;
					ver += h[i];
					hor += k[i];
				}
				if(i % 2 == 0 && ver2 >= 0 && ver2 < boardSize && hor2 >= 0 && hor2 < boardSize && chessBoard[currX][currY].mark == chessBoard[hor2][ver2].mark) {
					count++;
					ver2 += h[i + 1];
					hor2 += k[i + 1];
				}
				j++;
			}	
			if(count == 4) {
				return 1;
			}
		}
	}
	return 0;
}

int checkLegalEnter(int turn, int currX, int currY) {
    if(chessBoard[currX][currY].mark == 0) {
        chessBoard[currX][currY].mark = turn;
        return 1;
    }
    return 0;
}