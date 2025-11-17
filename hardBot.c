#include <limits.h>
#include "hardBot.h"
#define MAX_DEPTH 5 //6 makes the bot fucking stupid what the fuck, 7 makes the bot take incredibly long and makes my laptop overheat like crazy, might fix this with multithreading

int streak(char** board, int r, int c, int dr, int dc, char curr) {
    int streak = 0;
    for (int i = 0; i < 4; i++) { //checking to see how many pieces the selected player has in the streak
        int currRow = r + dr * i;
        int currCol = c + dc * i;
        if (currRow < 0 || currRow >= 6 || currCol < 0 || currCol >= 7) {
            return 0; //since it goes out of bounds and cannot be a good pattern
        }
        if (board[currRow][currCol] == curr) {
            streak++;
        } else if (board[currRow][currCol] != '.') {
            return 0; //since this means that the opponent's piece is in the middle of the pattern and is thus invalid
        }
    }
    return streak;
}

int evalBoard(char** board, char bot, char opp) { //heuristic function to calc how advantageous the current board is for the bot
    int score = 0;
    for (int row = 0; row < 6; row++) { //increase score for center column positions since it is more advantageous
        if (board[row][3] == bot) {
            score += 5;
        }
        if (board[row][3] == opp) {
            score += -5;
        }
    }
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            int streakBotH = streak(board, row, col, 0, 1, bot); //checking for horizontal streaks and prioritizing ones where the bot has more pieces
            if (streakBotH == 4) {
                score += 1000;
            } else if (streakBotH == 3) {
                score += 50;
            } else if (streakBotH == 2) {
                score += 10;
            }

            int streakOppH = streak(board, row, col, 0, 1, opp); //here we penalize streaks where the opponent has pieces
            if (streakOppH == 4) {
                score -= 1000;
            } else if (streakOppH == 3) {
                score -= 50;
            } else if (streakOppH == 2) {
                score -= 10;
            }

            int streakBotV = streak(board, row, col, 1, 0, bot); //same for all other directions
            if (streakBotH == 4) {
                score += 1000;
            } else if (streakBotH == 3) {
                score += 50;
            } else if (streakBotH == 2) {
                score += 10;
            }

            int streakOppV = streak(board, row, col, 1, 0, opp); 
            if (streakOppV == 4) {
                score -= 1000;
            } else if (streakOppV == 3) {
                score -= 50;
            } else if (streakOppV == 2) {
                score -= 10;
            }

            int streakBotD1 = streak(board, row, col, 1, 1, bot); 
            if (streakBotD1 == 4) {
                score += 1000;
            } else if (streakBotD1 == 3) {
                score += 50;
            } else if (streakBotD1 == 2) {
                score += 10;
            }

            int streakOppD1 = streak(board, row, col, 1, 1, opp); 
            if (streakOppD1 == 4) {
                score -= 1000;
            } else if (streakOppD1 == 3) {
                score -= 50;
            } else if (streakOppD1 == 2) {
                score -= 10;
            }

            int streakBotD2 = streak(board, row, col, 1, -1, bot); 
            if (streakBotH == 4) {
                score += 1000;
            } else if (streakBotH == 3) {
                score += 50;
            } else if (streakBotH == 2) {
                score += 10;
            }

            int streakOppD2 = streak(board, row, col, 1, -1, opp); 
            if (streakOppD2 == 4) {
                score -= 1000;
            } else if (streakOppD2 == 3) {
                score -= 50;
            } else if (streakOppD2 == 2) {
                score -= 10;
            }
        }
    }
    return score;
}

int minimax (char** board, int isMax, int depth, char bot, char opp) {
    int score = evalBoard(board, bot, opp); //calling the heuristic function to calc the current score
    if (depth == 0 || score >= 1000 || score <= -1000) { //if a winning move has been reached or the max depth has been exceeded (to reduce runtime, though move may be suboptimal)
        return score;
    }
    if (isMax) { //here we're seeing which move gets the bot the most score (since it's the bot's turn)
        int max = INT_MIN;
        for (int col = 0; col < 7; col++) {
            int row = 0;
            while (row < 6 && board[row][col] == '.') {
                row++;
            }
            if (row == 0) {
                continue;
            }
            board[row - 1][col] = bot;
            int val = minimax(board, 0, depth - 1, bot, opp);
            board[row - 1][col] = '.';
            if (val > max) { 
                max = val;
            }
        }
        return max;
    }
    int min = INT_MAX; //otherwise it's the opponent's turn, so we check which move decreases the bot's score the most (in order to assume an optimal play by the opponent)
    for (int col = 0; col < 7; col++) {
        int row = 0;
        while (row < 6 && board[row][col] == '.') {
            row++;
        }
        if (row == 0) {
            continue;
        }
        board[row - 1][col] = opp;
        int val = minimax(board, 1, depth - 1, bot, opp);
        board[row - 1][col] = '.';
        if (val < min) {
            min = val;
        }
    }
    return min;
}

int hardMove(char** board, char bot) {
    char opp = 'B';
    if (bot == 'B') {
        opp = 'A';
    }
    int max = INT_MIN;
    int ans = -1;
    for (int col = 0; col < 7; col++) {
        int row = 0;
        while (row < 6 && board[row][col] == '.') {
            row++;
        }
        if (row == 0) {
            continue;
        }
        board[row - 1][col] = bot;
        int val = minimax(board, 0, MAX_DEPTH, bot, opp); //we set isMax to 0 here because the next move is the opponent's, so we're minimizing
        board[row - 1][col] = '.';
        if (val > max) { //seeing which move gets us the largest score and play it
            max = val;
            ans = col;
        }
    }
    return ans;
}