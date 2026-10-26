#include "model.h"
#include "view.h"
#define boardSize 12
#define left 3
#define top 1

extern point chessBoard[boardSize][boardSize];
extern int currX, currY;

void resetData() {
	for(int i = 0; i < boardSize; ++i) {
		for(int j = 0; j < boardSize; ++j) {
			chessBoard[i][j].X = 4 * j + left + 2;
			chessBoard[i][j].Y = 2 * i + top + 1;
			chessBoard[i][j].mark = 0;
		}
	}
}

void checkLegalMove() {
	if(currX < 0) currX = 0;
	else if(currX > boardSize - 1) currX = boardSize - 1;
	if(currY < 0) currY = 0;
	else if(currY > boardSize - 1) currY = boardSize - 1;

	goToXY(chessBoard[currX][currY].X, chessBoard[currX][currY].Y);
}

int checkWin(int turn) {
	int h[] = {0, 0, -1, -1, -1, 1, 1, 1};
	int k[] = {1, -1, 0, 1, -1, 0, 1, -1};
	for(int i = 0; i < 8; ++i) {
		int ver = currY + h[i], hor = currX + k[i];
		if(currX >= 0 && currX < boardSize && currY >= 0 && currY < boardSize && chessBoard[currX][currY].mark == chessBoard[hor][ver].mark) {
			int count = 0;
			while(currX >= 0 && currX < boardSize && currY >= 0 && currY < boardSize && chessBoard[currX][currY].mark == chessBoard[hor][ver].mark && count < 4) {
				count++;
				ver += h[i];
				hor += k[i];
			}
			if(count == 4) {
				return turn;
			}
		}
	}
	return 0;
}

int checkLegalEnter(int turn) {
    if(chessBoard[currX][currY].mark == 0) {
        chessBoard[currX][currY].mark = turn;
        return 1;
    }
    return 0;
}