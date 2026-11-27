#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "control.h"
#include "view.h"
#include "model.h"
#include "audio.h"

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

void newGame(int &currX, int &currY, int &turn) {
    resetData(currX, currY, turn);
    drawBoard();
    gameProcessing(currX, currY, turn);
}

void conGame(int &currX, int&currY, int &turn, char gameName[]) {
    resetData(currX, currY, turn, 0, gameName);
    drawBoard();
    gameProcessing(currX, currY, turn);
}

int retryGame() {
    endMenu();
    int command, command2, temp = 1;
    do {
        command = getch();
        audioPlaySfx(sfxMove);
        if(command == 's' || command == 'S' || command == 'j' || command == 'J') {
            endMenu(0);
            temp = 0;
        } 
        else if(command == 'w' || command == 'W' || command == 'k' || command == 'K') {
            endMenu();
            temp = 1;
        }
        else if(command == 224 || command == 0) {
            command2 = getch();
            audioPlaySfx(sfxMove);
            switch(command2) {
                case 72: 
                    endMenu(); 
                    temp = 1; 
                    break;
                default: 
                    endMenu(0); 
                    temp = 0;
            }
        }
    }
    while(command != 13);
    return temp;
}

int controlMenu() {
    menu();
    int choice = 1;
    while(1) {
        int command = getch();
        audioPlaySfx(sfxMove);
        if(command == 's' || command == 'S' || command == 'j' || command == 'J') {
            moveDown(choice);
        }
        else if(command == 'w' || command == 'W' || command == 'k' || command == 'K') {
            moveUp(choice);
        }
        else if(command == 0 || command == 224) {
            int command2 = getch();
            switch(command2) {
            case 72: 
                moveUp(choice);
                break;
            case 80: 
                moveDown(choice);
            }
        }
        else if(command == 13) {
            return choice;
        } 
        if(choice < 1) choice = 1;
        else if(choice > 4) choice = 4;
        else {
            menu(choice);
        }
    }
}

int saveGame() {
    pauseMenu();
    int command, command2, temp = 1;
    do {
        command = getch();
        audioPlaySfx(sfxMove);
        if(command == 's' || command == 'S' || command == 'j' || command == 'J') {
            moveDown(temp);
        } 
        else if(command == 'w' || command == 'W' || command == 'k' || command == 'K') {
            moveUp(temp);
        }
        else if(command == 224 || command == 0) {
            command2 = getch();
            audioPlaySfx(sfxMove);
            switch(command2) {
                case 72: 
                    moveUp(temp);
                default: 
                    moveDown(temp);
            }
        }
        if(temp < 1) temp = 1;
        else if(temp > 3) temp = 3;
        pauseMenu(temp);
    }
    while(command != 13);
    return temp;
}

void gameProcessing(int &currX, int &currY, int &turn) {
    showCursor();
    while(1) {
        int command = getch();
        if(command != 27 && command != 13) {
            if(command == 'w' || command == 'W' || command == 'k' || command == 'K') moveUp(currX);
            else if(command == 's' || command == 'S' || command == 'j' || command == 'J') 
                moveDown(currX);
            else if(command == 'a' || command == 'A' || command == 'h' || command == 'H')
                moveLeft(currY);
            else if(command == 'd' || command == 'D' || command == 'l' || command == 'L')
                moveRight(currY);
            else if(command == 'b') {
                audioPlaySfx(sfxMove);
                hideCursor();
                switch(saveGame()) {
                    case 1: 
                        showCursor();
                        drawBoard();
                        for(int i = 0; i < BOARDSIZE; ++i) {
                            for(int j = 0; j < BOARDSIZE; ++j) {
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
                        break;
                    case 2: {
                        for(int i = TOP + 2 * 4; i <= TOP + 2 * 7; ++i) {
                            goToXY(LEFT + 4 * 2, i);
                            for(int i = 1; i <= 33; ++i) {
                                printf(" ");
                            }
                        }   
                        char fileName[61];
                        goToXY(LEFT + 4 * 2, TOP + 5 * 2 + 1);
                        printf("Nhap ten: ");
                        fgets(fileName, 51, stdin);
                        FILE *f = fopen("gameList.txt", "a");
                        if(f == NULL) {
                            printf("Loi mo file");
                            return;
                        }
                        fprintf(f, "%s", fileName);
                        fileName[strcspn(fileName, "\n")] = '\0';
                        char path[62];
                        snprintf(path, sizeof(path), "savedGame/%s", fileName);
                        FILE *p = fopen(path,"wt");
                        if(p == NULL) {
                            printf("Loi mo file");
                            fclose(f);
                            return;
                        }
                        for(int i = 0; i < BOARDSIZE; ++i) {
                            for(int j = 0; j < BOARDSIZE; ++j) {
                                fprintf(p, "%d ",chessBoard[i][j].mark);
                            }
                            fprintf(p, "\n");
                        }
                        fprintf(p, "%d", turn);
                        fclose(f);
                        fclose(p);
                        setColor();
                        hideCursor();
                        return;
                    }
                    default:    
                        return;
                }
            }
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
            audioPlaySfx(sfxMove);
            checkLegalMove(currX, currY);
        }
        else if(command == 27) {
            audioPlaySfx(sfxMove);
            setColor();
            return;
        } 
        else if(command == 13 && checkLegalEnter(turn, currX, currY)) {
            printChessChar(turn);
            audioPlaySfx(sfxPlace);
            if(checkDraw()) {
                winPlayer(0);
                audioPlaySfx(sfxDraw);
                hideCursor();
                if(retryGame()) {
                    newGame(currX, currY, turn);
                    return;
                }
                else {
                    setColor();
                    return;                   
                }
            }
            else if(checkWin(currX, currY)) {
                winPlayer(turn);
                audioPlaySfx(sfxWin);
                hideCursor();
                if(retryGame()) {
                    newGame(currX, currY, turn);
                    return;
                }
                else {
                    setColor();
                    return;                   
                }
            }
            else turn = -turn;
        }
    }
}