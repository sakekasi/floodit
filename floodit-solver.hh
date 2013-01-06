#ifndef FLOODIT_SOLVER_H
#define FLOODIT_SOLVER_H

#define STARTING_LEVEL 0
#define EXPAND_LEVEL(X) X+3

#define HEURISTIC_MULT 1
#define COST_MULT 1

#include "floodit-board-inl.hh"
#include "board-tree-inl.hh"
#include <vector>


class FlooditSolver {
 public:
  FlooditSolver(FlooditBoard*);

  virtual ~FlooditSolver();

  color next_step();
  
 protected:
  void GenerateLayers(BoardTreeNode*, FlooditBoard*,
                      const int, const int);
  /**
   * FindFastestPath finds the best set of moves to solve a floodit board
   * (the best path through the tree) using an A* search.
   */
  void FindFastestPath();

  /**
   * AStarSelect is a helper function for FindFastestPath. It takes a
   * frontier and returns the path with the smallest weighted value while
   * deleting the path from frontier.
   */
  FlooditPath* AStarSelect(std::vector<FlooditPath*> *);

  /**
   * EvalPath is a helper function that evaluates a path starting at
   * the solver's first board.
   */
  FlooditBoard* EvalPath(FlooditPath*);

  FlooditBoard* starting_board_;
  BoardTreeNode* move_tree_;
  FlooditPath* best_path_;

  int current_index_;
};


#endif
