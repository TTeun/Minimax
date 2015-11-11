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

  if (depth == 0)
  {
    if (maximizing)
      return evalScore(currentBoard);
    else
      return -evalScore(currentBoard);
  }

  int max = std::numeric_limits<int>::min();

  for (size_t i = 0; i != nMoves; ++i)
  {
    size_t moveValue = maximizing ? nMoves - i : i + 1;

    // Do move
    currentBoard->score += moveValue;

    int score = -minimax(currentBoard, -beta, -alpha, depth - 1, not maximizing);

    // Undo move
    currentBoard->score -= moveValue;

    if (score > max)
      max = score;

    if (alpha < score)
      alpha = score;

    if (alpha >= beta)
      break;
  }

  return max;
}



int main(int argc, char **argv) {
  Board game;
  game.score = 0;

  size_t depth = argc == 2 ? stoi(argv[1]) : 5;
  int min = std::numeric_limits<int>::min() + 1;
  int max = std::numeric_limits<int>::max() - 1;
  int score = minimax(&game, min, max, depth, true);
  cout << "Score: " << score << '\n';
  cout << "Visited: " << nodes << '\n';
}