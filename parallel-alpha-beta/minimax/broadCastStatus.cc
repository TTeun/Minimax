#include "minimax.ih"

void Minimax::broadCastStatus(vector<char> *finished, bool you)
{
  finished->at(d_proc) = you;

  for (processor p = 0; p != d_procs; ++p)
    if (p != d_proc)
      bsp_put(p, &finished->at(d_proc), &finished->at(0), d_proc * sizeof(char), sizeof(char));
}
