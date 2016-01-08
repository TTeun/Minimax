int searched = 0;
int steps = 0;
long long int totalSearched;
int searchDepth = 7;
// max heur_score = 202756.0
// min heur_score = -2609292.5

static double searchTree(board_t board, int depth, bool maximizing){
    searched++;
    if (depth == 0){
        return scoreHelper(board, score_table);
    }

    double move = -1;

    // MAXIMIZING
    if (maximizing)
    {
        double max = -std::numeric_limits<double>::max(); 
        double maxTmp;
        board_t tmp;
        for (int j = 0; j < 4; j++)
        {
            // For all viable moves
            tmp = executeMove(j,board);
            if (tmp != board)
            {
                // Find the highest score
                maxTmp = searchTree(tmp, depth - 1, false);
                if (maxTmp > max)
                {
                    move = j;
                    max = maxTmp;
                }
            }
        }
        return ( (depth == searchDepth) ? move : max );
    } else  {  // MINIMIZING
        int empty = countEmpty(board);
        double min = std::numeric_limits<double>::max();
        double minTmp;
        board_t tmp;
        for (int j = 0; j < empty; j++)
        {
            // For all possible board additions
            tmp = insertTileSet(board, 1, j);
            // Find the highest score
            minTmp = searchTree(tmp, depth - 1, true);
            if (minTmp < min)
            {
                move = j;
                min = minTmp;
            }
        }
        return ( (depth == searchDepth) ? move : min );
    }
}

int cppMove2JsMove(int move){
    if (move == 0)
        return 0;
    if (move == 1)
        return 2;
    if (move == 2)
        return 3;
    if (move == 3)
        return 1; 
}

int position2XY(int index, board_t board){
    int pos = 0;
    while (1){
        while ( (board & 0xf) != 0){
            board >>= 4;
            pos++;
        }
        if (index == 0)
            break;

        board >>= 4;
        pos++;

        --index;
    }
    return pos;

}


static int playGameAiHard(int print){
    board_t board = 0x0ULL;
    // Starting board
    // | 0 | 0 | 2 | 0 | 
    // | 4 | 0 | 0 | 0 |
    // | 0 | 0 | 0 | 0 | 
    // | 0 | 0 | 0 | 0 |
    board = insertTileSet(board, 5, 2);
    board = insertTileSet(board, 4, 3);
    board = insertTileSet(board, 7, 2);
    board = insertTileSet(board, 2, 3);
    board = insertTileSet(board, 5, 9);
    board = insertTileSet(board, 1, 8);
    board = insertTileSet(board, 1, 8);
    board = insertTileSet(board, 1, 8);
    printBoard(board);
    printf("  {type: \"add\", x: 2, y: 0, value: 2},\n");
    printf("  {type: \"add\", x: 0, y: 1, value: 4},\n");

    // printBoard(board);
    int move;
    while(1)
    {        
        searched = 0;
        // Determine next move
        move = searchTree(board, searchDepth, true);
        if (move == -1)
            break;

        // printf("  {type: \"move\", direction: %d},\n", cppMove2JsMove(move));        


        board = executeMove(move, board);
        // printBoard(board);
        totalSearched += searched;
        steps++;

        // printf("maximizing\n");
        printBoard(board);
        searched = 0;
        // Determine next move

        move = searchTree(board, searchDepth, false);
        if (move == -1)
            break;
        // printf("minimizing\n");
        int pos = position2XY(move, board);
        // printf("  {type: \"add\", x: %d, y: %d, value: 2},\n",(pos % 4), (int)(pos/4));

        board = insertTileSet(board, 1, move);
        printBoard(board);


        totalSearched += searched;

        // Print some information
        if (print > 1){
           printf("score : %d, largest tile : %d, empty : %d, nodes searched : %d\n", (int)scoreHelper(board, score_table), 
                                       1 << maxTile(board), countEmpty(board), searched);        
        }
    }
    if (print > 0){
        printBoard(board);
        printf("\n total searched : %lld after %d steps\n", totalSearched, steps);
    }   


    // printf("\n\n");
    // board = 0x0ULL;
    // // Starting board
    // // | 0 | 0 | 2 | 0 | 
    // // | 4 | 0 | 0 | 0 |
    // // | 0 | 0 | 0 | 0 | 
    // // | 0 | 0 | 0 | 0 |
    // board = insertTileSet(board, 1, 2);
    // board = insertTileSet(board, 2, 3);
    // printBoard(board);

    // move = (int)searchTree(board, searchDepth, false);
    // if (move != -1){
    //     int pos = position2XY(move, board);
    //     board = insertTileSet(board, 1, move);
    //     printf("X : %d, Y : %d\n", (pos % 4), (int)(pos/4) );
    //     printBoard(board);
    // }




    return maxTile(board);
}