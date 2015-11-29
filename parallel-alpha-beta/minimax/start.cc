#include "minimax.ih"

void Minimax::start()
{
  node processor = bsp_pid();

  int min = numeric_limits<int>::min() + 1;
  int max = numeric_limits<int>::max() - 1;

  int result = parallelSearch(
    &d_board,
    min,
    max,
    d_depth,
    d_maximizing,
    true,
    processor
  );

  if(processor == 0)
    cout << result << '\n';
}
