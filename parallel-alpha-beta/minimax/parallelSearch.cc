#include "minimax.ih"

int Minimax::parallelSearch(Board *board, int alpha, int beta, size_t depth, bool maximizing, bool pv, node proc)
{
  if (depth == 0)
    return maximizing ? board->evaluate() : -board->evaluate();

  int max = numeric_limits<int>::min();

  // Prepare the moves
  vector<int> moves(d_branches);

  for (size_t i = 0; i != d_branches; ++i)
    moves[i] = maximizing ? d_branches - i : i + 1;

  if (pv)
  {
    board->move(moves[0]); // Do move
    int PVScore = -parallelSearch(board, -beta, -alpha, depth - 1, not maximizing, true, proc);
    board->move(-moves[0]); // Undo move

    if (PVScore > max)
      max = PVScore;

    if (alpha < PVScore)
      alpha = PVScore;

    if (alpha >= beta)
      return max;

    /**
     * Do the other moves in parallel
     * assume there are enough processors
     */
    node total = bsp_nprocs();
    int *nonPVScores = new int[total];

    bsp_push_reg(nonPVScores, total * sizeof(int));
    bsp_sync();

    for (size_t i = 1; i < d_branches; ++i)
    {
      if (proc + 1 == i)
      {
        board->move(moves[i]); // Do move
        nonPVScores[proc] = -parallelSearch(board, -beta, -alpha, depth - 1, not maximizing, false, proc);
        board->move(-moves[i]); // Undo move

        // Broadcast to other processors
        for (node p = 0; p < total; ++p)
          if (p != proc)
            bsp_put(p, &nonPVScores[proc], nonPVScores, p * sizeof(int), sizeof(int));
      }
    }

    bsp_sync();

    // Find the highest score
    // Maybe this can be ran in parallel too for large branching factors?
    for (node p = 0; p < total; ++p)
      if (nonPVScores[p] > max)
        max = nonPVScores[p];

    bsp_pop_reg(nonPVScores);
    delete[] nonPVScores;

    return max;
  }

  // Not on the PV, so simply go over each move.
  for (size_t i = 0; i < d_branches; ++i)
  {
    board->move(moves[i]); // Do move
    int score = -parallelSearch(board, -beta, -alpha, depth - 1, not maximizing, false, proc);
    board->move(-moves[i]); // Undo move

    if (score > max)
      max = score;

    if (alpha < score)
      alpha = score;

    if (alpha >= beta)
      break;
  }

  return max;
}
