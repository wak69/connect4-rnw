#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "checkFunctions.h"
#include "easyBot.h"
#include "normalBot.h"
#include "hardBot.h"

enum PlacingCodes {NO_WIN, WIN, INVALID_COLUMN};
enum Difficulties {EASY, NORMAL, HARD};

static int lastStarter = 0;

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
        if (board[0][i] == '.') {
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
    srand(time(NULL));
    int mode;
    int difficulty;
    printf("Welcome to connect4!\n");
    printf("1. Two Player Mode\n");
    printf("2. Play vs Bot\n");
    printf("Choose mode (1 or 2): \n");
    scanf("%d", &mode);
    
    char curr;
    int col, result;
    char** board = initBoard();
    int vsBot = (mode == 2);
    if (vsBot) {
        printf("1. Easy\n2. Normal\n3. Hard\nChoose the bot's difficulty (1, 2, or 3): \n");
        scanf("%d", &difficulty);
        difficulty--;

        //Decide who starts
        if (lastStarter = 0){
            if (rand() % 2 == 0){
                curr = 'A';// player starts 
                lastStarter = 1;
            } else {
                curr = 'B';// bot starts
                lastStarter = 2;
            }
        }else if (lastStarter == 1){
            // bot starts now
            curr = 'B';
            lastStarter = 2;
        }else {
            // player starts now 
            curr = 'A';
            lastStarter = 1;
        }
        if (curr == 'B'){
            printf("bot goes first.");
        }else {
            printf("you goes first.)";
        }       
    }else {
        // player starts first
            curr = 'A';
    }
    
    while (1) {
       if (!checkForRemainingMoves(board)){
           printf("No more remaining moves. It's a draw!\n");
           break;
       }
        printBoard(board);
        if(curr == 'A' || !vsBot){
            // human turn
            printf("Player %c, choose a column (1-7): \n", curr);
            if(scanf("%d", &col) != 1){
                printf("Invalid input! Try again. \n");
                while(getchar() != '\n');
                continue;
            }
            col -= 1;
        }else {
            // bot turn
            if (difficulty == EASY) {
                col = easyMove(board);
            } else if (difficulty == NORMAL) {
                col = normalMove(board);
            } else {
                col = hardMove(board, curr);
            }
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

