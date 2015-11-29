#ifndef INCLUDED_BOARD_
#define INCLUDED_BOARD_

#include <cstddef>

class Board
{
  size_t d_position;

public:
  Board();
  size_t evaluate() const;
  void move(size_t value);
};

inline size_t Board::evaluate() const
{
  return d_position;
}

inline void Board::move(size_t value)
{
  d_position += value;
}

#endif
