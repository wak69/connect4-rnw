#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
            return 1;
        }
    }
    return 0;
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
int botMove(char** board){
int col;
    do{
        col = rand() % 7;
    }while (board[0][col] != '.');
    return  col;
}

int main() {
    srand(time(NULL));
    int mode;
    printf("Welcome to connect4!\n");
    printf("1. Two Player Mode\n");
    printf("2. Play vs Easy Bot\n");
    printf("Choose mode: \n");
    scanf("%d", &mode);
    
    char curr = 'A';
    int col, result;
    char** board = initBoard();
    int vsBot = (mode == 2);
    while (1) {
       if (!checkForRemainingMoves(board)){
           printf("No more remaining moves. It's a draw!\n");
       }
        printBoard(board);
        if(curr == 'A' || !vsBot){
            // human turn
            printf("Player %c, choose a column (1-7): ", curr);
            if(scanf("%d", &col) != 1){
                printf("Invalid input! Try again. \n");
                while(getchar() != '\n');
                continue;
            }
            col -= 1;
        }else {
            // bot turn
            col = botMove(board);
            printf("Bot chooses column %d\n", col + 1);
        }
        result = place(curr, col, board);
        if (result == INVALID_COLUMN){
            printf("Invalid move, try again.\n");
            continue;
        }else if (result == WIN){
            printBoard(board);
            if (vsBot && curr == 'B'){
                printf("Bot wins!\n");
            }else {
                printf("Player %c wins!\n", curr);
            }
            break;
        }
        // switch turns
        if (curr == 'A'){
            curr = 'B';
        }else {
            curr = 'A';
        }
    }
    freeBoard(board);
    return 0;

}
