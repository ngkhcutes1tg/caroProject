#include <windows.h>
#include <stdio.h>
#include "view.h"
#include "model.h"
#include "control.h"

int currX, currY, turn;
point chessBoard[boardSize][boardSize];

int main() {
    system("cls");
    fixConsole(); 
    resizeConsole(70, 30);
    hideCursor();
    while(1) {
        system("cls");
        switch(controlMenu()) {
        case 1:     
            startGame(currX, currY, turn);
            gameProcessing(currX, currY, turn);
            break;
        case 2: 
            FILE* p;
            p = fopen("gameList.txt", "rt");
            if(p == NULL) {
                printf("Loi mo file\n"); 
                return 1;
            }
            system("cls");
            while(!feof(p)) {
                char s[100];
                fgets(s, 100, p);
                printf("%s", s);
            }
            system("pause");
            fclose(p);
            break;
        case 3:
            system("cls");
            printf("Cai dat");       
            system("pause");
            break;
        default:
            system("cls");
            showCursor();
            return 0;
        }
    }
    return 0;
}