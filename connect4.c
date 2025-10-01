#include <stdio.h>
#include <stdlib.h>

char** initBoard() {
    char** board = (char**) malloc(6*sizeof(char*));
    for (int i = 0; i < 6; i++) {
        board[i] = (char*) malloc(7*sizeof(char));
        for (int j = 0; j < 7; j++) {
            board[i][j] = '.';
        }
    }
    return board;
}

void printBoard(char** board) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int place(char c, int col, char** board) {
    if (col < 0 || col > 6) {
        return 2;
    }
    if (board[0][col] != '.') {
        return 1;
    }
    int i = 0;
    while (i < 6 && board[i][col] == '.') {
        i++;
    }
    board[i - 1][col] = c;
    return 0;
}

int main() {
    char** board = initBoard();
    int idk = place('A', 6, board);
    int guh = place('B', 7, board);
    int bruh;
    for (int i = 0; i < 7; i++) {
    bruh = place('A', 5, board);
    }
    printf("%d %d %d\n", idk, guh, bruh);
    printBoard(board);
    return 0;
}