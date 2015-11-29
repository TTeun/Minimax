#include "board/board.h"
#include "minimax/minimax.h"
#include <iostream>
#include <string>

using namespace std;

size_t depth;
size_t branching = 4;

void startSearch()
{
  bsp_begin(branching - 1);

  Board initial;
  Minimax game(initial, branching, depth, true);
  game.start();

  bsp_end();
}

int main(int argc, char **argv)
{
  depth = argc == 2 ? stoi(argv[1]) : 5;

  bsp_init(startSearch, argc, argv);

  startSearch();
}