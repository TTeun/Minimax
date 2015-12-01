#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "2048.h"
#include "play.h"

static inline int endNode(board_t board){
    int max;
    int maxTmp;
    int bestMove;
    board_t tmp;
    max = -1;
    bestMove = 0;
    for (int i = 0; i < 4; i++)
    {
        tmp = execute_move(i,board);
        if (tmp != board)
        {
            maxTmp = score_helper(tmp, score_table) ;
            if (max <= maxTmp )
            {
                max = maxTmp;
                bestMove = i;
            }
        }
        if (max == -1 && i == 3)
            return -1;
    
    }
    return bestMove;
}

static inline void playGameAi(){
    board_t board = initBoard();
    char c;
    int move;
    while(1)
    {        
        int score = score_helper(board, score_table);  
        printf("score : %d, empty : %d\n", score, count_empty(board));        
        printBoard(board);

        move = endNode(board);
        if (move == -1)
            break;

        board = execute_move(move , board);
        board = insert_tile_rand(board,drawNew());
        //scanf("%c",&c);
    }
}

int main(){
    init_tables();
    playGameAi();
    return 0;
}