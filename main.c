#include <stdio.h>
#include "view.h"
#include "model.h"
#include "control.h"
#include <ctype.h>
#include <conio.h>

int currX, currY, turn, dem = 0;

int main() {
    start();
    while(1) {
        int command = getch();
        if(command != 27 && command != 13) {
            if(command == 'w' || command == 'W' || command == 'k' || command == 'K') 
                moveUp();
            else if(command == 's' || command == 'S' || command == 'j' || command == 'J') 
                moveDown();
            else if(command == 'a' || command == 'A' || command == 'h' || command == 'H')
                moveLeft();
            else if(command == 'd' || command == 'D' || command == 'l' || command == 'L')
                moveRight();
            else if(command == 0 || command == 224) {
                int command2 = getch();
                switch(command2) {
                    case 72:
                        moveUp();
                        break;
                    case 80:
                        moveDown();
                        break;
                    case 75:
                        moveLeft();
                        break;
                    default: 
                        moveRight();
                }
            }
            checkLegalMove();
        }
        else if(command == 27) {
            out();
            return 0;
        } 
        else if(command == 13 && checkLegalEnter(turn)) {
            printChessChar(turn);
            if(checkWin(turn)) {
                winPlayer(checkWin(turn));
                // if(end()) 
                //     start();
                // else {
                //     out();
                //     return 0; 
                // }
                setColor();
                return 0;
            }
            else turn = -turn;
        }
    }
    return 0;
}