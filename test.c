#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#define boardSize 12
#define left 3
#define top 1

typedef struct {
	int X, Y, mark;
} point;

point chessBoard[boardSize][boardSize];
int currX, currY;

void goToXY(int x, int y) {
	COORD coord = {(short) x, (short) y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void resetData() {
	for(int i = 0; i < boardSize; ++i) {
		for(int j = 0; j < boardSize; ++j) {
			chessBoard[i][j].X = 4 * j + left + 2;
			chessBoard[i][j].Y = 2 * i + top + 1;
			chessBoard[i][j].mark = 0;
		}
	}
	currX = 0, currY = 0;
}

void setColor(int textColor, int bgColor) {
	HANDLE hConsole = (GetStdHandle(STD_OUTPUT_HANDLE));
	SetConsoleTextAttribute(hConsole, (WORD)(bgColor << 4 | textColor));
}

void drawBoard() {
	system("cls");
	for(int i = 0; i <= boardSize; ++i) {
		for(int j = 0; j <= boardSize; ++j) {
			goToXY(left + 4 * j, top + 2 * i);
			printf("+");
			if(j < boardSize)	
				printf("---");
			if(i < boardSize) {
				goToXY(left + 4 * j, top + 2 * i + 1);
				printf("|");
			}
		}
	}
}

void fixConsole() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) &~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void resizeConsole(int width, int height) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {(short)width, (short)height};
	SetConsoleScreenBufferSize(hConsole, coord);

	SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &rect);
}

void moveUp() {	
	currX--;
}

void moveDown() {
	currX++;
}

void moveLeft() {
	currY--;
}

void moveRight() {
	currY++;
}

void checkCorrectMove() {
	if(currX < 0) currX = 0;
	else if(currX > boardSize - 1) currX = boardSize - 1;
	if(currY < 0) currY = 0;
	else if(currY > boardSize - 1) currY = boardSize - 1;

	goToXY(chessBoard[currX][currY].X, chessBoard[currX][currY].Y);
}

void printChessChar(int turn) {
	chessBoard[currX][currY].mark = turn;
	switch(turn) {
		case 1:
			setColor(4, 0);
			printf("X");
			break;
		default:
			setColor(1, 0);
			printf("O");
	}
}

void start() {
	resetData();
	drawBoard();
	fixConsole();
	resizeConsole(80, 34);
	goToXY(chessBoard[currX][currY].X, chessBoard[currX][currY].Y);
}

void end() {
	system("cls");
	setColor(7, 0);
	printf("Cam on ban vi da choi game!\n");
	printf("Bam phim bat ki de thoat");
	int c = getch();
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

void winPlayer(int check) {
	if(check != 0) {
	goToXY(0, chessBoard[boardSize - 1][boardSize - 1].Y + 2);
		switch(check) {
			case 1: 
				printf("Nguoi choi X thang");
				break;
			case -1: 
				printf("Nguoi choi O thang");
				break;
		}
	}
}

int main() {
	start();
	int turn = 1;
	while(1) {
		int readChar = getch();
		if(readChar == 'w') moveUp();
		else if(readChar == 's') moveDown();
		else if(readChar == 'a') moveLeft();
		else if(readChar == 'd') moveRight();
		else if(readChar == 27) {
			end();	
			return 0;
		}
		checkCorrectMove();
		if(readChar == 13 && chessBoard[currX][currY].mark == 0) {
			printChessChar(turn);
			if(checkWin(turn) != 0) {
				winPlayer(checkWin(turn));
				setColor(7, 0);
				return 0;
			}
			turn = -turn;
		}
	}
	setColor(7, 0);
	return 0;
}




