#include "minimax.ih"

Minimax::Minimax(Board board, node nodes, size_t branches, size_t depth, bool maximizing)
  :
  d_board(board),
  d_nodes(nodes),
  d_branches(branches),
  d_depth(depth),
  d_maximizing(maximizing)
{}
