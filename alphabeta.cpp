#include <iostream>
#include <string>
#include <limits>
#include <cstddef>

using namespace std;

/* Structure that will hold all information of the game board */
struct Board
{
  int score;
};

size_t nodes = 0;

int evalScore(Board * currentBoard) {
  return currentBoard->score;
}

int minimax(Board * currentBoard, int alpha, int beta, const size_t depth, const bool maximizing) {
  ++nodes;

  const size_t nMoves = 3;

  if (depth == 0) // The search has gone deep enough
    return evalScore(currentBoard);

  int extremum = (maximizing ? numeric_limits<int>::min() : numeric_limits<int>::max());

  if (maximizing)
  {
    for (size_t i = 0; i != nMoves; ++i)
    {
      size_t moveValue = maximizing ? nMoves - i : i + 1;

      // Do move
      currentBoard->score += moveValue;

      int score = minimax(currentBoard, alpha, beta, depth - 1, not maximizing);

      // Undo move
      currentBoard->score -= moveValue;

      if (score > extremum)
        extremum = score;

      if (alpha < extremum)
        alpha = extremum;

      if (beta <= alpha)
        break;
    }
  }
  else
  {
    for (size_t i = 0; i != nMoves; ++i)
    {
      size_t moveValue = maximizing ? nMoves - i : i + 1;

      // Do move
      currentBoard->score += moveValue;

      int score = minimax(currentBoard, alpha, beta, depth - 1, not maximizing);

      // Undo move
      currentBoard->score -= moveValue;

      if (score < extremum)
        extremum = score;

      if (beta > extremum)
        beta = extremum;

      if (beta <= alpha)
        break;
    }
  }

  return extremum;
}



int main(int argc, char **argv) {
  Board game;
  game.score = 0;

  size_t depth = argc == 2 ? stoi(argv[1]) : 5;
  int score = minimax(&game, numeric_limits<int>::min(),
                  numeric_limits<int>::max(), depth, true);

  cout << "Score: " << score << '\n'
       << "Visited: " << nodes << '\n';
}