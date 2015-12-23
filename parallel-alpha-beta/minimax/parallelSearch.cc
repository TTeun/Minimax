#include "minimax.ih"

int Minimax::parallelSearch(Board *board, vector<char> *finished, int alpha, int beta, size_t depth, bool maximizing, NodeType type)
{
  ++d_total;
  ++d_nodes;

  // Some check for completeness
  if (d_nodes % 100000 == 0)
  {
    // Reset counting
    d_nodes = 0;

    // Mark your status as working
    broadCastStatus(finished, false);

    bsp_sync();

    // Here you can possibly send some board position...
  }

  // Prepare the moves
  vector<Move> moves = board->listMoves(maximizing, d_branches);

  if (depth == 1 or moves.size() == 0)
  {
    return maximizing ? board->evaluate() : -board->evaluate();
  }

  switch (type)
  {
    /**
     * On the principal nodes parallelism is always an option
     * after the first child is searche sequentially to
     * establish an initial search window [alpha, beta].
     */
    case PRINCIPAL:
    {
      // Stores the score of each move
      vector<int> scores(moves.size());
      bsp_push_reg(&scores[0], scores.size() * sizeof(int));
      bsp_sync();

      // Search the principle variation with all processors sequentially
      board->move(moves[0]); // Do move
      scores[0] = -parallelSearch(board, finished, -beta, -alpha, depth - 1, not maximizing, PRINCIPAL);
      board->undo(moves[0]); // Undo move

      // PV alpha value
      alpha = scores[0];

      /**
       * Do the other moves in parallel
       * assume there are enough processors
       */

      for (size_t move = 1; move < moves.size(); ++move)
      {
        // Cyclically distribute the remaining moves
        if (d_proc == (move - 1) % d_procs)
        {
          // Do move
          board->move(moves[move]);

          // The younger brother is a CUT node
          scores[move] = -parallelSearch(board, finished, -beta, -alpha, depth - 1, not maximizing, CUT);

          // Undo move
          board->undo(moves[move]);

          // Broadcast score to other processors
          for (processor p = 0; p != d_procs; ++p)
            if (p != d_proc)
              bsp_put(p, &scores[move], &scores[0], move * sizeof(int), sizeof(int));
        }
      }

      // Reset the node counter
      d_nodes = 0;

      // Inform the others of being done
      broadCastStatus(finished, true);

      while (waitForWork(finished))
      {
        // Here this guy should receive work from a busy proc
        // change its status to NOT finished
      }

      // Find the highest score
      for (size_t idx = 1; idx < moves.size(); ++idx)
        if (scores[idx] > alpha)
          alpha = scores[idx];

      bsp_pop_reg(&scores[0]);

      return alpha;

      break;
    }

    /**
     * Never put children of CUT nodes on the work queue
     */
    case CUT:
    {
      // Not on the PV, so simply go over each move.
      int max = numeric_limits<int>::min();

      // Search all moves
      for (size_t move = 0; move < moves.size(); ++i)
      {
        board->move(moves[i]); // Do move
        int score = -parallelSearch(board, finished, -beta, -alpha, depth - 1, not maximizing, ALL);
        board->undo(moves[i]); // Undo move

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

    /**
     * Put all children of ALL nodes in the work queue :)
     */
    case ALL:
    {
      // Not on the PV, so simply go over each move.
      int max = numeric_limits<int>::min();

      // Search all moves
      for (size_t move = 0; move < moves.size(); ++i)
      {
        board->move(moves[i]); // Do move
        int score = -parallelSearch(board, finished, -beta, -alpha, depth - 1, not maximizing, CUT);
        board->undo(moves[i]); // Undo move

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

  // You cannot reach this part, but this disables compiler warnings
  return 0;
}
