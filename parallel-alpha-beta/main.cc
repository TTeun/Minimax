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

  for(node p = 1; p <= nodes; ++p)
  { 
    if(bsp_pid() == 0)
    {
      cout << "\nCores = " << p << '\n';
    }

    Board initial;
    Minimax game(initial, p, branching, depth, true);

    double start = bsp_time();
    game.start();
    double duration = bsp_time() - start;

    for(node p = 0; p < nodes; ++p)
    {
      if(bsp_pid() == p)
      {
        cout << "Core" << p << ": " << game.getCount() << "; duration: " << duration << '\n';
      }
      bsp_sync();
    }
  }

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