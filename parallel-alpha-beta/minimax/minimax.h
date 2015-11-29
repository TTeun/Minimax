#ifndef INCLUDED_GAME_
#define INCLUDED_GAME_

#include "../board/board.h"
#include "../parallel.h"

class Minimax
{
  Board d_board;
  size_t d_branches;
  size_t d_depth;
  bool d_maximizing;
public:
  Minimax(Board board, size_t branches, size_t depth, bool maximizing);
  void start();
  int parallelSearch(Board *board, int alpha, int beta, size_t depth, bool maximizing, bool pv, node proc);
};

#endif
