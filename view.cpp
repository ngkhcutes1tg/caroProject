#include <stdio.h>
#include <windows.h>
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
	for(int i = 0; i < boardSize; ++i) {
		for(int j = 0; j < boardSize; ++j) {
			if(chessBoard[i][j].mark == 1) {
				goToXY(chessBoard[i][j].X, chessBoard[i][j].Y);
				setColor(4, 0);
				printf("X");
			}
			else if(chessBoard[i][j].mark == -1) {
				goToXY(chessBoard[i][j].X, chessBoard[i][j].Y);
				setColor(1, 0);
				printf("O");
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
	setColor();
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
	setColor();
	for(int i = top + 2 * 4; i <= top + 2 * 4 + 1; ++i) {
		goToXY(left + 3 * 4, i);
		for(int j = 1; j <= 25; ++j) {
			printf(" ");
		}
	}
	goToXY(chessBoard[4][3].X + 2, chessBoard[4][3].Y);
	switch(check) {
		case 1: 
			setColor(4, 0);
			printf("Nguoi choi X thang");
			break;
		case -1: 
			setColor(1, 0);
			printf("Nguoi choi O thang");
			break;
		default:
			goToXY(chessBoard[4][3].X - 1, chessBoard[4][3].Y);
			setColor();
			printf("Hai nguoi choi hoa nhau");
	}
	setColor();
}

void endMenu(int choice) {
	setColor();
	for(int i = top + 2 * 5; i <= top + 2 * 7; ++i) {
    	goToXY(left + 3 * 4, i);
		for(int i = 1; i <= 25; ++i) {
			printf(" ");
		}
	}
	goToXY(chessBoard[5][4].X + 2, chessBoard[5][4].Y);
	printf("Choi lai");
	goToXY(chessBoard[6][5].X - 1, chessBoard[6][5].Y);
	printf("Thoat");
	if(choice) {
		setColor(0, 7);
		goToXY(chessBoard[5][4].X + 2, chessBoard[5][4].Y);
		printf("Choi lai");
	}
	else {
		setColor(0, 7);
		goToXY(chessBoard[6][5].X - 1, chessBoard[6][5].Y);
		printf("Thoat");
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

void pauseMenu(int choice) {
	setColor();
	for(int i = top + 2 * 4; i <= top + 2 * 7; ++i) {
		goToXY(left + 3 * 4, i);
		for(int i = 1; i <= 25; ++i) {
			printf(" ");
		}
	}
	goToXY(chessBoard[4][4].X + 1, chessBoard[4][4].Y);
	printf("Choi tiep");
	goToXY(chessBoard[5][5].X, chessBoard[5][5].Y);
	printf("Luu");
	goToXY(chessBoard[6][5].X - 1, chessBoard[6][5].Y);
	printf("Thoat");
	if(choice == 1) {
		setColor(0, 7);
		goToXY(chessBoard[4][4].X + 1, chessBoard[4][4].Y);
		printf("Choi tiep");
	}
	else if(choice == 2) {
		setColor(0, 7);
		goToXY(chessBoard[5][5].X, chessBoard[5][5].Y);
		printf("Luu");
	}
	else if(choice == 3) {
		setColor(0, 7);
		goToXY(chessBoard[6][5].X - 1, chessBoard[6][5].Y);
		printf("Thoat");
	}
	setColor();
}

void settingMenu(int choice) {
	setColor();
	goToXY(30, 14);
	printf("Am thanh");
	goToXY(30, 16);
	printf("Thoat");
}