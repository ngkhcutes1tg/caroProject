#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <stdio.h>
#include "control.h"
#include "view.h"
#include "model.h"

void moveUp(int &currX) {
    currX--;
}

void moveDown(int &currX) {
    currX++;
}

void moveLeft(int &currY) {
    currY--;
}

void moveRight(int &currY) {
    currY++;
}

void startGame(int &currX, int &currY, int &turn) {
    resetData(currX, currY, turn);
    drawBoard();
}

int endGame() {
    endMenu();
    int command, command2, temp;
    do {
        command = getch();
        if(command == 's' || command == 'S' || command == 'j' || command == 'J') {
            endMenu(0);
            temp = 1;
        } 
        else if(command == 'w' || command == 'W' || command == 'k' || command == 'K') {
            endMenu();
            temp = 0;
        }
        else if(command == 224 || command == 0) {
            command2 = getch();
            switch(command2) {
                case 72: endMenu(); temp = 0; break;
                default: endMenu(0); temp = 1;
            }
        }
    }
    while(command != 13);
    return temp;
}

void gameProcessing(int &currX, int &currY, int &turn) {
    while(1) {
        int command = getch();
        if(command != 27 && command != 13) {
            if(command == 'w' || command == 'W' || command == 'k' || command == 'K') 
                moveUp(currX);
            else if(command == 's' || command == 'S' || command == 'j' || command == 'J') 
                moveDown(currX);
            else if(command == 'a' || command == 'A' || command == 'h' || command == 'H')
                moveLeft(currY);
            else if(command == 'd' || command == 'D' || command == 'l' || command == 'L')
                moveRight(currY);
            else if(command == 0 || command == 224) {
                int command2 = getch();
                switch(command2) {
                    case 72:
                        moveUp(currX);
                        break;
                    case 80:
                        moveDown(currX);
                        break;
                    case 75:
                        moveLeft(currY);
                        break;
                    default: 
                        moveRight(currY);
                }
            }
            checkLegalMove(currX, currY);
        }
        else if(command == 27) {
            system("cls");
            setColor();
            return;
        } 
        else if(command == 13 && checkLegalEnter(turn, currX, currY)) {
            printChessChar(turn);
            if(checkDraw() == 1) {
                winPlayer(0);
            }
            else if(checkWin(currX, currY)) {
                winPlayer(turn);
                if(endGame() == 1) {
                    return;
                }
                else startGame(currX, currY, turn);
            }
            else turn = -turn;
        }
    }
}

int controlMenu() {
    menu();
    int choice = 1, command;
    do {
        command = getch();
        if(command == 's' || command == 'S' || command == 'j' || command == 'J') {
            moveDown(choice);
        }
        else if(command == 'w' || command == 'W' || command == 'k' || command == 'K') {
            moveUp(choice);
        }
        if(choice < 1) choice = 1;
        else if(choice > 4) choice = 4;
        menu(choice);
    }
    while(command != 13);
    return choice;
}
