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

int minimax(Board * currentBoard, const size_t depth, const bool white) {
  ++nodes;

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

    int score = minimax(currentBoard, depth - 1, not white);

    if ((white and score > currentScore) or (not white and score < currentScore)) {
      currentScore = score;
    }

    // Undo move
    currentBoard->score -= moves[i];
  }

  return currentScore;
}

int main(int argc, char **argv) {
  srand(unsigned(time(NULL)));

  Board game;
  game.score = 0;

  size_t depth = argc == 2 ? stoi(argv[1]) : 5;
  cout << "Score: " << minimax(&game, depth, true) << '\n';
  cout << "Visited: " << nodes << '\n';
}