#pragma once
#define boardSize 12
#define left 3
#define top 1

typedef struct{int X, Y, mark;} point;
extern point chessBoard[boardSize][boardSize];

void goToXY(int, int);
void showCursor();
void hideCursor();
void setColor(int = 7, int = 0);
void drawBoard();
void fixConsole();
void resizeConsole(int, int);
void printChessChar(int);
void winPlayer(int);
void endMenu(int = 1);
void menu(int = 1);
