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