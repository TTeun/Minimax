#ifndef INCLUDED_GAME_
#define INCLUDED_GAME_

#include <vector>
#include "../board/board.h"
#include "../parallel.h"

class Minimax
{
  enum NodeType
  {
    PRINCIPAL,
    CUT,
    ALL
  };

  Board d_board;
  processor d_procs;
  processor d_proc;
  size_t d_branches;
  size_t d_depth;
  bool d_maximizing;
  size_t d_total;
  size_t d_nodes;
public:
  Minimax(Board board, processor procs, processor proc, size_t branches, size_t depth, bool maximizing);
  void start();
  int parallelSearch(Board *board, std::vector<char> *finished, int alpha, int beta, size_t depth, bool maximizing, NodeType type);
  size_t getCount() const;

private:
  bool waitForWork(std::vector<char> *finished);
  void broadCastStatus(std::vector<char> *finished, bool you);
};

inline size_t Minimax::getCount() const
{
  return d_total;
}

#endif
