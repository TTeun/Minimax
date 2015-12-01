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
    max = -50;
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
        if (max == 0 && i == 3){
            printf("asdsadsa");
            break;
        }
    }
    return bestMove;
}

static inline void playGameAi(){
    board_t board = initBoard();
    char c;
    while(1)
    {        
        int score = score_helper(board, score_table);  
        printf("score : %d\n", score);        
        printBoard(board);

        board = execute_move(endNode(board), board);
        board = insert_tile_rand(board,drawNew());
        scanf("%c",&c);
    }
    printf("\nGame Over...\n");
}

int main(){
    init_tables();
    playGameAi();
    return 0;
}