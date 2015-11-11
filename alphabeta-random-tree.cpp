#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

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

  int currentScore = (maximizing ? -1000 : 1000);

  // randomly initialize scores
  vector<int> moves(nMoves);

  for (size_t i = 0; i != nMoves; ++i)
    moves.push_back(i + 1);

  random_shuffle(moves.begin(), moves.end());

  if (maximizing)
  {
    for (size_t i = 0; i != nMoves; ++i)
    {
      // Do move
      currentBoard->score += moves[i];

      int score = minimax(currentBoard, alpha, beta, depth - 1, not maximizing);

      // Undo move
      currentBoard->score -= moves[i];

      if (score > currentScore)
        currentScore = score;

      if (alpha < currentScore)
        alpha = currentScore;

      if (beta <= alpha)
        break;
    }
  }
  else
  {
    for (size_t i = 0; i != nMoves; ++i)
    {
      // Do move
      currentBoard->score += moves[i];

      int score = minimax(currentBoard, alpha, beta, depth - 1, not maximizing);

      // Undo move
      currentBoard->score -= moves[i];

      if (score < currentScore)
        currentScore = score;

      if (beta > currentScore)
        beta = currentScore;

      if (beta <= alpha)
        break;
    }
  }

  return currentScore;
}



int main(int argc, char **argv) {
  srand(unsigned(time(NULL)));

  Board game;
  game.score = 0;

  size_t depth = argc == 2 ? stoi(argv[1]) : 5;
  cout << "Score: " << minimax(&game, -1000, 1000, depth, true) << '\n';
  cout << "Visited: " << nodes << '\n';
}