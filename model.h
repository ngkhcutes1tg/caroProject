#pragma once

int resetData(int&, int&, int&, int = 1, char[]=0);
void checkLegalMove(int&, int&);
int checkWin(int, int);
int checkDraw();
int checkLegalEnter(int, int, int);