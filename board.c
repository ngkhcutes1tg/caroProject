#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

#define boardSize 10
#define left 20 
#define top 10 

typedef struct {
	int l, r, c;
} point;

point a[22][45];

int k[] = {0, 0, 1, 1, 1, -1, -1, -1};
int h[] = {1, -1, 0, 1, -1, 0, 1, -1};

void goToXY(int x, int y) {
	COORD coord = {(short)x, (short)y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void resetData() {
	for(int i = 0; i < boardSize; ++i) {
		for(int j = 0; j < boardSize; ++j) {
			a[i][j].l = 4 * j + left + 2;
			a[i][j].r = 2 * i + top + 1;
			a[i][j].c = 0;
		}
	}
}

void setColor(int textColor, int bgColor) {
	HANDLE hConsole = (GetStdHandle(STD_OUTPUT_HANDLE));
	SetConsoleTextAttribute(hConsole, (WORD)((bgColor << 4) | textColor));
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
	goToXY(a[2][2].l, 1);
	setColor(14, 0);
	printf("=== TRO CHOI CARO ===");
	setColor(7, 0);
	goToXY(a[2][2].l, 3);
	printf("Phim W/A/S/D: Di chuyen.");
	goToXY(a[2][2].l, 5);
	printf("Phim Enter: Danh co");
	goToXY(a[2][2].l, 7);
	printf("Phim Esc: Thoat game");
}

void fixConsole() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) &~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void resizeConsole(int width, int height) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord;
	coord.X = width;
	coord.Y = height;
	SetConsoleScreenBufferSize(hConsole, coord);

	SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &rect);
}

int main() {
	resetData();
	drawBoard();
	fixConsole(); 
	resizeConsole(80, 34); 
	goToXY(left + 4 * boardSize + 6, a[4][5].r);
	setColor(4, 0);
	printf("Luot choi: X"); 
	int x = 0, y = 0;
	goToXY(a[x][y].l, a[x][y].r);	
	setColor(4, 0);
	int f = 4;
	char ch = 'X';

	while(1) { 
		if(!kbhit())	continue;
		int c = getch();
		if(a[x][y].c != 4 && a[x][y].c != 1) 
			printf(" "); if(c == 'w' || c == 'W') x--; 
		else if(c == 's' || c == 'S') x++; 
		else if(c == 'a' || c == 'A') y--; 
		else if(c == 'd' || c == 'D') y++; 	
		else if(c == 224 || c == 0) {
			int c2 = getch();
			switch(c2) { 
				case 72: 
				x--;
					break;
				case 80:
					x++;
					break;
				case 75:
					y--;
					break;
				case 77:	
					y++;
					break;
			}
		}	

		else if(c == 27) {
			system("cls");
			setColor(7, 0);
			printf("Cam on ban vi da choi game!");
			return 0;
		}
	
		if(c != 13) {

			if(x < 0) x = 0; 
			else if(x > boardSize - 1) x = boardSize - 1;
			if(y < 0) y = 0; 
			else if(y > boardSize - 1) y = boardSize - 1;

			goToXY(a[x][y].l, a[x][y].r);
		}

		else if(c == 13 && a[x][y].c == 0) {
			goToXY(a[x][y].l,a[x][y].r);
			printf("%c", ch);
			a[x][y].c = f;

			for(int i = 0; i < 9; ++i) {
				int tung = x + k[i], hoanh = y + h[i];
				if(tung > 0 && tung < boardSize && hoanh > 0 && hoanh < boardSize && a[x][y].c == a[tung][hoanh].c) {
					int count = 0;
					while(a[x][y].c == a[tung][hoanh].c && count < 4) {
						count++;
						tung += k[i];
						hoanh += h[i];
					}
					if(count == 4) {
						int n = 2, tung = x, hoanh = y;
						for(int m = 0; m < 3; ++m) {
							fflush(stdout);
							Sleep(700);
							for(int j = 0; j < 5; ++j) {
								goToXY(a[x][y].l, a[x][y].r);
								setColor(f, n);
								printf("%c", ch);
								x += k[i];
								y += h[i];
							}
							x = tung; 
							y = hoanh;
							(n == 2) ? (n = 7) : (n = 2);
						}
						fflush(stdout);
						Sleep(1000);
						setColor(f, 14);
						goToXY(0, top + 2 * boardSize + 2);
						printf("NGUOI CHOI %c THANG CUOC\n", ch);
						setColor(7, 0);
						printf("Nhap phim bat ki de thoat game");
						goToXY(30, a[9][9].r + 4);
						int c = getch();
						system("cls");
						return 0;
					}
				}
			}

			if(f == 4) { 
				ch = 'O';
				f = 1;
			}	
			else { 
				ch = 'X';
				f = 4;
			}
			setColor(f, 0);
			if(f == 4) {
				int tung = 2;
				for(int i = 0; i < 12; ++i) {
					goToXY(2 + i, a[4][5].r);
					printf(" ");
				}
				goToXY(left + 4 * boardSize + 6, a[4][5].r);
			}	
			else {
				int tung = left + 4 * boardSize + 6;
				for(int i = 0; i < 12; ++i) {
					goToXY(tung + i, a[4][5].r);
					printf(" ");
				}
				goToXY(2, a[4][5].r);
			}
			printf("Luot choi: %c", ch);
			goToXY(a[x][y].l, a[x][y].r);
		}
	}
	setColor(7, 0);
	return 0;
}
