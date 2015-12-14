#include "minimax.ih"

int Minimax::parallelSearch(Board *board, int alpha, int beta, size_t depth, bool maximizing, bool pv, node proc)
{
  if (depth == 0)
  {
    ++d_count;
    return maximizing ? board->evaluate() : -board->evaluate();
  }

  // Prepare the moves
  vector<int> moves(d_branches);

  for (size_t i = 0; i != d_branches; ++i)
    moves[i] = maximizing ? d_branches - i : i + 1;

  if (pv)
  {
    board->move(moves[0]); // Do move
    int max = -parallelSearch(board, -beta, -alpha, depth - 1, not maximizing, true, proc);
    board->move(-moves[0]); // Undo move

    if (alpha < max)
      alpha = max;

    /**
     * Do the other moves in parallel
     * assume there are enough processors
     */
    vector<int> nonPVScores(d_branches - 1);

    bsp_push_reg(&nonPVScores[0], nonPVScores.size() * sizeof(int));
    bsp_sync();

    for (size_t i = 1; i != d_branches; ++i)
    {
      if (proc == (i - 1) % d_nodes)
      {
        board->move(moves[i]); // Do move
        nonPVScores[i - 1] = -parallelSearch(board, -beta, -alpha, depth - 1, not maximizing, false, proc);
        board->move(-moves[i]); // Undo move

        // Broadcast to other processors
        for (node p = 0; p < d_nodes; ++p)
          if (p != proc)
            bsp_put(p, &nonPVScores[i - 1], &nonPVScores[0], (i - 1) * sizeof(int), sizeof(int));
      }
    }

    bsp_sync();

    // Find the highest score
    for (node p = 1; p != d_branches; ++p)
      if (nonPVScores[p - 1] > max)
        max = nonPVScores[p - 1];

    bsp_pop_reg(&nonPVScores[0]);

    return max;
  }

  // Not on the PV, so simply go over each move.
  int max = numeric_limits<int>::min();
  for (size_t i = 0; i != d_branches; ++i)
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
