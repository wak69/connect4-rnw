#include <stdlib.h>

int easyMove(char** board){
    int col;
    do {
        col = rand() % 7;
    } while (board[0][col] != '.');
    return col;
}

