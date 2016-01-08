#ifndef INCLUDED_GAME_
#define INCLUDED_GAME_

#include "../board/board.h"
#include "../parallel.h"

class Minimax
{
  Board d_board;
  node d_nodes;
  size_t d_branches;
  size_t d_depth;
  bool d_maximizing;
  size_t d_count;
public:
  Minimax(Board board, node nodes, size_t branches, size_t depth, bool maximizing);
  void start();
  int parallelSearch(Board *board, int alpha, int beta, size_t depth, bool maximizing, bool pv, node proc);
  size_t getCount() const;
};

inline size_t Minimax::getCount() const
{
  return d_count;
}

#endif
