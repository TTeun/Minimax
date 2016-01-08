int searched = 0;
int steps = 0;
long long int totalSearched;

static float searchTree(board_t board, int depth){

    searched++;
    if (depth == 0)
        return (scoreHelper(board, heur_score_table) +
                scoreHelper(transpose(board), heur_score_table));

    
    if ( (depth == 2) && (maxTile(board) <= 512) )
        return (scoreHelper(board, heur_score_table) +
                scoreHelper(transpose(board), heur_score_table));

    int empty = countEmpty(board);
    long int max; 
    long int maxTmp;
    long long int total = 0;
    board_t tmp1;
    board_t tmp2;
    for (int i = 0; i < empty; i++)
    {
        // Fill in the ith empty block with a 2
        tmp1 = insertTileSet(board, 1, i);
        max = 0;
        for (int j = 0; j < 4; j++)
        {
            // For all viable moves
            tmp2 = executeMove(j,tmp1);
            if (tmp2 != tmp1)
            {
                // Find the highest score
                maxTmp = searchTree(tmp2, depth - 1);
                if (maxTmp > max){
                    max = maxTmp;
                }
            }
        }
        total += 0.9*max;

        max = 0;
        tmp1 = insertTileSet(board, 2, i);
        for (int j = 0; j < 4; j++)
        {
            tmp2 = executeMove(j,tmp1);
            if (tmp2 != tmp1)
            {
                maxTmp = searchTree(tmp2, depth - 1);
                if (maxTmp > max){
                    max = maxTmp;
                }
            }
        }
        total += 0.1*max;
    }
    total /= (2*empty);
    return total ;
}

static int playIt(board_t board, int depth){
    long long int max;
    long long int maxTmp;
    int bestMove = 0;
    board_t tmp;
    max = -1;

    for (int i = 0; i < 4; i++)
    {
        tmp = executeMove(i,board);
        if (tmp != board)
        {
            
            maxTmp = searchTree(tmp, depth);
            if (max <= maxTmp)
            {
                max = maxTmp;
                bestMove = i;
            }

        }

        if (max < 0 && i == 3)
            return -1;

    }
    return bestMove;
}

static int playGameAi(int depth, int print){
    board_t board = initBoard();
    int move;
    while(1)
    {        
        // printBoard(board);
        searched = 0;
        // Determine next move
        move = playIt(board, depth);
        
        totalSearched += searched;
        steps++;

        // Print some information
        if ((print > 1)){
           printf("score : %d, largest tile : %d, empty : %d, nodes searched : %d\n", (int)scoreHelper(board, score_table), 
                                       1 << maxTile(board), countEmpty(board), searched);        
        }

        if (move == -1)
            break;


        board = executeMove(move, board);
        board = insertTileRand(board,drawNew());
        //scanf("%c",&c);
    }
    if (print > 0){
        printBoard(board);
        printf("\n total searched : %lld after %d steps\n", totalSearched, steps);
    }   
    return maxTile(board);
}