#ifndef INCLUDED_BOARD_
#define INCLUDED_BOARD_

#include <vector>
#include "../move/move.h"

class Board
{
  size_t d_position;

public:
  Board();

  // Construct a board from a communicated integer
  explicit Board(int position);

  size_t evaluate() const;
  void move(Move const &move);
  void undo(Move const &move);
  std::vector<Move> listMoves(bool maximizing, size_t branches) const;
};

inline size_t Board::evaluate() const
{
  return d_position;
}

inline void Board::move(Move const &move)
{
  d_position += move.getValue();
}

inline void Board::undo(Move const &move)
{
  d_position -= move.getValue();
}

#endif
