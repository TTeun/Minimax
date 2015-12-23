#include "minimax.ih"

void Minimax::start()
{
  int min = numeric_limits<int>::min() + 1;
  int max = numeric_limits<int>::max() - 1;

  vector<char> finished(d_procs, false);
  bsp_push_reg(&finished[0], finished.size() * sizeof(char));

  int result = parallelSearch(
                 &d_board,
                 &finished,
                 min,
                 max,
                 d_depth,
                 d_maximizing,
                 PRINCIPAL
               );


  if (d_proc == 0)
    cout << result << '\n';
}
