#include "minimax.ih"

bool Minimax::waitForWork(vector<char> *finished)
{
  bsp_sync();

  // Done before the others probably
  for (processor p = 0; p < d_procs; ++p)
  {
    if (not finished->at(p))
    {
      return true;
    }
  }

  return false;
}
