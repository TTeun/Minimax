#include "minimax.ih"

Minimax::Minimax(Board board, processor procs, processor proc, size_t branches, size_t depth, bool maximizing)
  :
  d_board(board),
  d_procs(procs),
  d_proc(proc),
  d_branches(branches),
  d_depth(depth),
  d_maximizing(maximizing),
  d_total(0),
  d_nodes(0)
{
}
