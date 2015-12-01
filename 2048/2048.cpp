#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include "2048.h"

/* 0 = up, 1 = down, 2 = left, 3 = right */

int main(){
    init_tables();
	board_t board = initBoard();
    board_t tmp;
    int c;
    while (c != -1){
        tmp  = board;
        int score = score_helper(board, score_table);
        printf("score : %d\n", score);
        printBoard(board);
        scanf("%d",&c);
        board = execute_move(c,board);
        if (board != tmp)
            board = insert_tile_rand(board,drawNew());
    }

	return 0;
}