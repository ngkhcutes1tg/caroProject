#include <stdio.h>

int main() {
    char a[12][12];
    FILE *fp = fopen("savedGame/abc", "rt");
    int k;
    for(int i = 0; i < 12; ++i) {
        for(int j = 0; j < 12; ++j) {
            fscanf(fp, "%c", &a[i][j]);
        }
    }
    for(int i = 0; i < 12; ++i) {
        for(int j = 0; j < 12; ++j) {
            printf("%c ", a[i][j]);
        }
        printf("\n");
    }
    fclose(fp);
}