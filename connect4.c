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

int main() {
    char** board = initBoard();
    printBoard(board);
    return 0;
}