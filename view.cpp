#include <windows.h>
#include <stdio.h>
#include "view.h"

void hideCursor() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);
	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);
}

void showCursor() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);
	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);
}

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
	goToXY(chessBoard[0][0].X, chessBoard[0][0].Y);
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
    setColor();
}

void winPlayer(int check) {
	goToXY(0, chessBoard[boardSize - 1][boardSize - 1].Y + 2);
	switch(check) {
		case 1: 
			setColor(4, 0);
			printf("Nguoi choi X thang\n");
			break;
		case -1: 
			setColor(1, 0);
			printf("Nguoi choi O thang\n");
			break;
		default:
			printf("Hai nguoi choi hoa nhau\n");
	}
	setColor();
}

void endMenu(int choice) {
	setColor();
	for(int i = top + 2 * 5; i <= top + 2 * 7; ++i) {
    	goToXY(left + 4 * 4, i);
		for(int i = 1; i <= 17; ++i) {
			printf(" ");
		}
	}
	goToXY(chessBoard[5][4].X + 2, chessBoard[5][4].Y);
	printf("Choi lai");
	goToXY(chessBoard[6][4].X + 1, chessBoard[6][4].Y);
	printf("Thoat game");
	if(choice) {
		setColor(0, 7);
		goToXY(chessBoard[5][4].X + 2, chessBoard[5][4].Y);
		printf("Choi lai");
	}
	else {
		setColor(0, 7);
		goToXY(chessBoard[6][4].X + 1, chessBoard[6][4].Y);
		printf("Thoat game");
	}
	setColor();
}

void menu(int choice) {
	setColor();
	goToXY(30, 11);	
	printf("Choi moi");
	goToXY(30, 13);
	printf("Choi tiep");
	goToXY(30, 15);
	printf("Cai dat");
	goToXY(30, 17);
	printf("Thoat");
	setColor(0, 7);
	switch(choice) {
		case 1: 
			goToXY(30, 11);	
			printf("Choi moi");
			break;
		case 2:
			goToXY(30, 13);
			printf("Choi tiep");			
			break;
		case 3:
			goToXY(30, 15);
			printf("Cai dat");
			break;
		default:
			goToXY(30, 17);
			printf("Thoat");
	}
	setColor();
}

void settingMenu(int choice) {
	goToXY(30, 14);
	printf("Am thanh");
	goToXY(30, 16);
	printf("Thoat");
}