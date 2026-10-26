#pragma once

#define boardSize 12

typedef struct{int X, Y, mark;} point;

void goToXY(int, int);
void setColor(int = 7, int = 0);
void drawBoard();
void fixConsole();
void resizeConsole(int, int);
void printChessChar(int);
void winPlayer(int);
void endMenu(int = 3, int = 6, int = 0, int = 15);
void endMenuBorder(int);
void currPosHighlight(int, int);