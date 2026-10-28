#include "windows.h"
#include <stdio.h>
#include "view.h"
#define boardSize 3 
#define left 3
#define top 1

point chessBoard[boardSize][boardSize];
extern int currX, currY, turn;

void goToXY(int x, int y) {
    COORD coord = {(short) x, (short) y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
	currX = 0;
	currY = 0;
	turn = 1;
	goToXY(chessBoard[currX][currY].X, chessBoard[currX][currY].Y);
}

void fixConsole() {
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
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

void printChessChar(int turn) {
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

void winPlayer(int check) {
	goToXY(0, chessBoard[boardSize - 1][boardSize - 1].Y + 2);
		switch(check) {
			case 1: 
				printf("Nguoi choi X thang\n");
				break;
			case -1: 
				printf("Nguoi choi O thang\n");
				break;
			default:
				setColor();
				printf("2 nguoi choi hoa nhau\n");
		}
}

void endMenu(int retryTextColor, int retryBgColor, int exitTextColor, int exitBgColor) {
	setColor(0, 15);
	for(int i = top + 2 * 5; i <= top + 2 * 7; ++i) {
    	goToXY(left + 4 * 4, i);
		for(int i = 1; i <= 17; ++i) {
			printf(" ");
		}
	}
	setColor(retryTextColor, retryBgColor);
    goToXY(chessBoard[5][4].X + 2, chessBoard[5][4].Y);
    printf("Choi lai!");
	setColor(exitTextColor, exitBgColor);
    goToXY(chessBoard[6][4].X + 1, chessBoard[6][4].Y);
    printf("Thoat game!");
}

void endMenuBorder(int row) {
    for(int i = row; i <= row + 1; ++i) {
		goToXY(left + 4 * 4, top + 2 * i);
		for(int j = 1; j <= 17; ++j) {
			printf(" ");	
		}
	}
	goToXY(left + 4 * 4, top + 2 * row + 1);
	printf(" ");
	goToXY(left + 4 * 8, top + 2 * row + 1);
	printf(" ");
}

void currPosHighlight(int mark) {
	if(mark == 0) {
		setColor(0, 7);
		printf(" ");
	}
	else {
		switch(mark) {
			case 1:
				setColor(4, 7);
				printf("X");
				break;
			default:
				setColor(2, 7);
				printf("O");
		}
	}
}