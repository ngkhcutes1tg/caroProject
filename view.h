#pragma once
#define BOARDSIZE 12
#define LEFT 3
#define TOP 1

typedef struct{int X, Y, mark;} point;
extern point chessBoard[BOARDSIZE][BOARDSIZE];

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
void pauseMenu(int = 1);
void gameListMenu(int = 0);