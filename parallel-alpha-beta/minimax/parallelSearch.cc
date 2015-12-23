#include "minimax.ih"

int Minimax::parallelSearch(Board *board, int alpha, int beta, size_t depth, bool maximizing, NodeType type, node proc)
{
  ++d_count;

  // Some check for completeness
  if (d_count % 1000000 == 0)
  {
    bsp_sync();
  }

  if (depth == 1)
  {
    return maximizing ? board->evaluate() : -board->evaluate();
  }

  // Prepare the moves
  vector<int> moves(d_branches);

  for (size_t i = 0; i != d_branches; ++i)
    moves[i] = maximizing ? d_branches - i : i + 1;

  switch (type)
  {
  case PRINCIPAL:
  {
    board->move(moves[0]); // Do move
    alpha = -parallelSearch(board, -beta, -alpha, depth - 1, not maximizing, PRINCIPAL, proc);
    board->move(-moves[0]); // Undo move

    /**
     * Do the other moves in parallel
     * assume there are enough processors
     */
    vector<int> nonPVScores(d_branches - 1);
    vector<char> finished(d_nodes, false);

    bsp_push_reg(&finished[0], finished.size() * sizeof(char));
    bsp_push_reg(&nonPVScores[0], nonPVScores.size() * sizeof(int));
    bsp_sync();

    for (size_t i = 1; i != d_branches; ++i)
    {
      if (proc == (i - 1) % d_nodes)
      {
        board->move(moves[i]); // Do move
        nonPVScores[i - 1] = -parallelSearch(board, -beta, -alpha, depth - 1, not maximizing, CUT, proc);
        board->move(-moves[i]); // Undo move

        // Broadcast to other processors
        for (node p = 0; p != d_nodes; ++p)
          if (p != proc)
            bsp_put(p, &nonPVScores[i - 1], &nonPVScores[0], (i - 1) * sizeof(int), sizeof(int));
      }
    }

    // Mark your status as finished
    finished[proc] = true;

    // Inform the others of being done
    for (node p = 0; p != d_nodes; ++p)
      if (p != proc)
        bsp_put(p, &finished[proc], &finished[0], proc * sizeof(char), sizeof(char));

    // Get stuck in a loop waiting for the slowest processor to arrive
    while (true)
    {
      bsp_sync();

      bool done = true;

      // Done before the others probably
      for (node p = 0; p < d_nodes; ++p)
      {
        if (not finished[p])
        {
          // Here you can fetch work from processor p :).
          done = false;
          break;
        }
      }

      // Proceed when everyone is done...
      if (done)
        break;
    }

    // Find the highest score
    for (node p = 1; p != d_branches; ++p)
      if (nonPVScores[p - 1] > alpha)
        alpha = nonPVScores[p - 1];

    bsp_pop_reg(&finished[0]);
    bsp_pop_reg(&nonPVScores[0]);

    return alpha;

    break;
  }

  case CUT:
  case ALL:
  {
    // Not on the PV, so simply go over each move.
    int max = numeric_limits<int>::min();

    // Alternate children type
    NodeType childType = (type == CUT) ? ALL : CUT;

    // Search all moves
    for (size_t i = 0; i != d_branches; ++i)
    {
      board->move(moves[i]); // Do move
      int score = -parallelSearch(board, -beta, -alpha, depth - 1, not maximizing, childType, proc);
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
  break;
  }

  return 0;
}
