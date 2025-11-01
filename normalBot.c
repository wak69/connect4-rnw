#include "checkFunctions.h"
#include <stdlib.h>

int normalMove(char** board) {
    int row;
    for (int col = 0; col < 7; col++) { //check for winning move
        row = 0;
        while (row < 6 && board[row][col] == '.') {
            row++;
        }
        if (row == 0) {
            continue;
        }
        board[row - 1][col] = 'B';
        if (checkHorizontal(row - 1, col, board, 'B') == 1 || checkVertical(row - 1, col, board, 'B') == 1 || checkLRDiagonal(row - 1, col, board, 'B') == 1 || checkRLDiagonal(row - 1, col, board, 'B') == 1 ) {
            board[row - 1][col] = '.';
            return col;
        }
        board[row - 1][col] = '.';
    }

    for (int col = 0; col < 7; col++) { //check if opponent can win next turn to block them
        row = 0;
        while (row < 6 && board[row][col] == '.') {
            row++;
        }
        if (row == 0) {
            continue;
        }
        board[row - 1][col] = 'A';
        if (checkHorizontal(row - 1, col, board, 'A') == 1 || checkVertical(row - 1, col, board, 'A') == 1 || checkLRDiagonal(row - 1, col, board, 'A') == 1 || checkRLDiagonal(row - 1, col, board, 'A') == 1 ) {
            board[row - 1][col] = '.';
            return col;
        }
        board[row - 1][col] = '.';
    }

    int col;

    if (board[0][2] == '.' || board[0][3] == '.' || board[0][4] == '.') {
        do { //otherwise do a random move in the center of the board
            col = (rand() % 3) + 2;
        } while (board[0][col] != '.');
        return col;
    }

    do { //otherwise do a random move anywhere
        col = rand() % 7;
    } while (board[0][col] != '.');
    return col;
}

//let n be the number of rows, and m be the number of columns
//outer loops are O(m), check for horizontal win is O(m), while other checks are O(n), so the 