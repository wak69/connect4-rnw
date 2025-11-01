#ifndef CHECK
#define CHECK

int checkHorizontal(int row, int col, char** board, char c);

int checkVertical(int row, int col, char** board, char c);

int checkLRDiagonal(int row, int col, char** board, char c);

int checkRLDiagonal(int row, int col, char** board, char c);

#endif