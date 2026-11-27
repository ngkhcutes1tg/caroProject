#include "view.h"
#include "model.h"
#include "control.h"
#include "audio.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

int currX, currY, turn;
point chessBoard[BOARDSIZE][BOARDSIZE];

typedef struct {
    char gameName[50];
}game;

int main() {
    system("cls");
    fixConsole(); 
    resizeConsole(70, 30);
    hideCursor();
    audioLoad();
    audioInit();
    while(1) {
        system("cls");
        switch(controlMenu()) {
        case 1:     
            newGame(currX, currY, turn);
            break;
        case 2: {
            FILE* f;
            f = fopen("gameList.txt", "rt");
            if(f == NULL) {
                printf("Loi mo file\n"); 
                return 1;
            }
            system("cls");
            game gameList[100];
            char s[51];
            int n = 0;
            while(fgets(s, 51, f)) {
                if(s != "\n") {
                    s[strcspn(s, "\n")] = '\0';
                    strcpy(gameList[n++].gameName, s); 
                }
            }
            setColor(0, 7);
            printf("%s\n", gameList[0].gameName);
            setColor();
            for(int i = 1; i < n; ++i) {
                printf("%s\n", gameList[i].gameName);
            }
            int command, temp = 0;
            do {
                command = getch();
                if(command == 's') moveDown(temp);
                else if(command == 'w') moveUp(temp);
                if(temp < 0) temp = 0;
                else if(temp > n - 1) temp = n - 1;
                else {
                    for(int i = 0; i < n; ++i) {
                        goToXY(0, i);
                        printf("%s\n", gameList[i].gameName);
                    }
                    goToXY(0, temp);
                    setColor(0, 7);
                    printf("%s", gameList[temp].gameName);
                    setColor();
                }
            }
            while(command != 13);
            fclose(f);
            conGame(currX, currY, turn, gameList[temp].gameName);
            break;
        }
        case 3: {
            system("cls");
            int mv, sv, mm, sm;
            printf("Music volume: ");
            scanf("%d", &mv);
            printf("Sfx volume: ");
            scanf("%d", &sv);
            printf("Music muted: ");
            scanf("%d", &mm);
            printf("Sfx muted: ");
            scanf("%d", &sm);
            audioSetMusicVolume(mv);
            audioSetSfxVolume(sv);
            audioSetMusicMuted(mm);
            audioSetSfxMuted(sm);
            break;
        }
        default:
            system("cls");
            showCursor();
            audioSave();
            audioShutdown();
            return 0;
        }
    }
}