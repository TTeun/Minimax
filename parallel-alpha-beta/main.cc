#include "board/board.h"
#include "minimax/minimax.h"
#include <iostream>
#include <string>

using namespace std;

size_t depth;
size_t branching;
node nodes;

void startSearch()
{
  bsp_begin(nodes);

  Board initial;
  Minimax game(initial, nodes, branching, depth, true);
  game.start();

  bsp_end();
}

int main(int argc, char **argv)
{
  branching = argc >= 2 ? stoi(argv[1]) : 3;
  nodes = argc >= 3 ? stoi(argv[2]) : 1;
  depth = argc >= 4 ? stoi(argv[3]) : 10;

  bsp_init(startSearch, argc, argv);

  startSearch();
}