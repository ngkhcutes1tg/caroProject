#include <windows.h>
#include "view.h"
#include "model.h"
#include "control.h"

int currX, currY, turn;
point chessBoard[boardSize][boardSize];

int main() {
    system("cls");
    fixConsole(); 
    resizeConsole(70, 50);
    if(controlMenu() == 1) {
        startGame(currX, currY, turn); 
        gameProcessing(currX,currY,turn);
    }
    else if(controlMenu() == 2) {
        ;
    }
    else if(controlMenu() == 3) {
        ;
    }
    else if(controlMenu() == 4) {
        system("cls");
        setColor();
    }
    return 0;
}
