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

int evalScore(Board * currentBoard) {
  return currentBoard->score;
}

int minimax(Board * currentBoard, const size_t depth, const bool white, size_t * nodes) {
  ++*nodes;

  const size_t nMoves = 3;

  if (depth == 0) // The search has gone deep enough
    return evalScore(currentBoard);

  int currentScore = (white ? -1000 : 1000);

  // randomly initialize scores
  vector<int> moves(nMoves);

  for (size_t i = 0; i != nMoves; ++i)
    moves.push_back(i + 1);

  random_shuffle(moves.begin(), moves.end());

  for (size_t i = 0; i != nMoves; ++i)
  {
    // Do move
    currentBoard->score += moves[i];

    int score = minimax(currentBoard, depth - 1, not white, nodes);

    if ((white and score > currentScore) or (not white and score < currentScore)) {
      currentScore = score;
    }

    // Undo move
    currentBoard->score -= moves[i];
  }

  return currentScore;
}

double getAvgCosts(const size_t trials, const size_t depth)
{
  double avgCosts = 0.0;
  Board game;

  for (size_t trial = 1; trial <= trials; ++trial)
  {
    size_t counter = 0;
    game.score = 0;
    minimax(&game, depth, true, &counter);
    avgCosts += (static_cast<double>(counter) - avgCosts) / trial;
  }

  return avgCosts;
}

int main(int argc, char **argv) {
  srand(unsigned(time(NULL)));

  size_t depth = argc == 2 ? stoi(argv[1]) : 5;

  double avgCosts = getAvgCosts(100, depth);

  cout << "Visited: " << avgCosts << '\n';
}