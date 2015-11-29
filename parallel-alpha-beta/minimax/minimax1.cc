#include "minimax.ih"

Minimax::Minimax(Board board, size_t branches, size_t depth, bool maximizing)
  :
  d_board(board),
  d_branches(branches),
  d_depth(depth),
  d_maximizing(maximizing)
{}
