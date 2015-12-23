#include "board.ih"

vector<Move> Board::listMoves(bool maximizing, size_t branches) const
{
  vector<Move> moves;

  moves.reserve(branches);

  for (size_t i = 0; i != branches; ++i)
  {
    int value = maximizing ? branches - i : i + 1;
    moves.push_back(Move(value));
  }

  return moves;
}
