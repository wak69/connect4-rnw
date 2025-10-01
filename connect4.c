#include <stdio.h>
#include <stdlib.h>

enum PlacingCodes {NO_WIN, WIN, INVALID_COLUMN};

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

int checkForRemainingMoves(char** board) {
    for (int i = 0; i < 7; i++) {
        if (board[0][i] != '.') {
            return 0;
        }
    }
    return 1;
}

void freeBoard(char** board) {
    for (int i = 0; i < 6; i++) {
        free(board[i]);
    }
    free(board);
}

int checkHorizontal(int row, int col, char** board, char c) {
    int count = 0;
    for (int i = 0; i < 7; i++) {
        if (board[row][i] == c) {
            count++;
        } else {
            count = 0;
        }
        if (count == 4) {
            return 1;
        }
    }
    return 0;
}

int checkVertical(int row, int col, char** board, char c) {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (board[i][col] == c) {
            count++;
        } else {
            count = 0;
        }
        if (count == 4) {
            return 1;
        }
    }
    return 0;
}

int checkLRDiagonal(int row, int col, char** board, char c) {
    int x = col, y = row;
    while (x > 0 && y > 0) {
        x--;
        y--;
    }
    int count = 0;
    while (x < 7 && y < 6) {
        if (board[y][x] == c) {
            count++;
        } else {
            count = 0;
        }
        if (count == 4) {
            return 1;
        }
        x++;
        y++;
    }
    return 0;
}

int checkRLDiagonal(int row, int col, char** board, char c) {
    int x = col;
    int y = row;
    while (x < 7 && y > 0) {
        x++;
        y--;
    }
    int count = 0;
    while (x >= 0 && y < 6) {
        if (board[y][x] == c) {
            count++;
        } else {
            count = 0;
        }
        if (count == 4) {
            return 1;
        }
        x--;
        y++;
    }
    return 0;
}

int place(char c, int col, char** board) {
    if (col < 0 || col > 6) {
        return INVALID_COLUMN;
    }
    if (board[0][col] != '.') {
        return INVALID_COLUMN;
    }
    int i = 0;
    while (i < 6 && board[i][col] == '.') {
        i++;
    }
    board[i - 1][col] = c;
    if (checkHorizontal(i - 1, col, board, c) == 1 || checkVertical(i - 1, col, board, c) == 1 || checkLRDiagonal(i - 1, col, board, c) == 1 || checkRLDiagonal(i - 1, col, board, c) == 1) {
        return WIN;
    }
    return NO_WIN;
}

int main() {
    int win = 0;
    int idk;
    char curr = 'A';
    int col;
    char** board = initBoard();
    printf("Welcome to Connect 4!\nPlayer A: A\nPlayer B: B\n");
    while (1) {
        if (checkForRemainingMoves(board) == 0) {
            printf("No more remaining moves :(\n");
            break;
        }
        printBoard(board);
        printf("Player %c, choose a column (1-7): ", curr);
        scanf("%d", &col);
        printf("\n");
        idk = place(curr, col - 1, board);
        if (idk == INVALID_COLUMN) {
            printf("Invalid placement, try another column\n");
            continue;
        } else if (idk == WIN) {
            printBoard(board);
            printf("Player %c wins!", curr);
            break;
        }
        if (curr == 'A') {
            curr = 'B';
        } else {
            curr = 'A';
        }
    }
    freeBoard(board);
    return 0;
}