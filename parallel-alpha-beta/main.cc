#include "board/board.h"
#include "minimax/minimax.h"
#include <iostream>
#include <string>

using namespace std;

size_t depth;
size_t branching;
processor procs;

void startSearch()
{
  bsp_begin(procs);

  Board initial;
  Minimax game(initial, procs, bsp_pid(), branching, depth, true);

  double start = bsp_time();
  game.start();
  bsp_sync();
  double duration = bsp_time() - start;

  if(bsp_pid() == 0)
  {
    cout << "Explored: " << game.getCount() << "; duration: " << duration << '\n';
  }

  bsp_end();
}

int main(int argc, char **argv)
{
  branching = argc >= 2 ? stoi(argv[1]) : 3;
  procs = argc >= 3 ? stoi(argv[2]) : 1;
  depth = argc >= 4 ? stoi(argv[3]) : 10;

  bsp_init(startSearch, argc, argv);

  startSearch();
}