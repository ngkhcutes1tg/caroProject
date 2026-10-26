#include <ctype.h>
#include <stdio.h>
#include "control.h"
#include "view.h"
#include "model.h"
#include <conio.h>
#include <windows.h>
#define boardSize 12
#define top 1
#define left 3

extern int currX, currY;
extern point chessBoard[][boardSize];

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

void start() {
    fixConsole();
    resizeConsole(left + 4 * boardSize + 5, top + 2 * boardSize + 5);
    resetData();
    drawBoard();
}

int end() {
    endMenu();
    int curr = 5, command;
    do {
        setColor(0, 8);
        endMenuBorder(curr);        
         
        command = getch();
        if(command == 's') {
            if(curr == 5) {
                endMenuBorder(5);
                endMenu(0, 15, 3, 6);
            }
            curr = 6;
        } 
        else if(command == 'w') {
            if(curr == 6) {
                endMenuBorder(6);
                endMenu();
            }
            curr = 5;
        }
        else if(command == 13) {
            break;
        }
    }
    while(1);
    if(curr == 5) {
        setColor();
        return 1;
    }
    else return 0;
}

void out() {
    setColor(7, 0);
    system("cls");
}
