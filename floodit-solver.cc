/*
 * floodit-solver.cc
 *
 * an implementation of an a* search of a game tree for a floodit game.
 *
 * Author: Saketh Kasibatla
 */
#include "floodit-solver.hh"
#include <cstdlib>
#include <cstdio>

FlooditSolver::FlooditSolver(FlooditBoard* b)
    :current_index_(0)
{
  this->move_tree_ = new BoardTreeNode(b);
  
  this->starting_board_ = b;
  this->GenerateLayers(this->move_tree_, this->starting_board_,
                       STARTING_LEVEL, EXPAND_LEVEL(STARTING_LEVEL));
  this->FindFastestPath();
}

FlooditSolver::~FlooditSolver(){
  delete this->move_tree_;
}

color FlooditSolver::next_step(){
  if(this->best_path_ == nullptr){
    fprintf(stderr, "ERROR: the tree was parsed to the end.\n");
    exit(1);
  }

  if(this->current_index_ >= this->best_path_->num_steps()){
    return NULL_COLOR;
  }

  //this should increment after passing current value to step
  return this->best_path_->step(this->current_index_++)->active_color();
}


//private functions

void FlooditSolver::GenerateLayers(BoardTreeNode *n, FlooditBoard *b,
                                   const int level, const int max){
  //set up this node
  n->set_active_color(b->active_color());
  n->set_max_percent(b->max_percent());
  n->set_level(level);

  //check for base case
  if(b->max_percent() == 100 ||
     level == max){
    return;
  }

  //call for not base case
  for(color i=0; i<NUM_COLORS; i++){
    if(i==b->active_color()){
      continue;
    }

    FlooditBoard *new_b = new FlooditBoard(b, i);
    BoardTreeNode *new_n = new BoardTreeNode();

    GenerateLayers(new_n, new_b, level+1, max);
    n->add_child(new_n);
  }
}

void FlooditSolver::FindFastestPath(){
  //initialize
  std::vector<FlooditPath*> *frontier = new std::vector<FlooditPath*>();
  std::vector<FlooditPath*> *explored = new std::vector<FlooditPath*>();
  
  FlooditPath *init_path = new FlooditPath(this->move_tree_);
  frontier->push_back(init_path);

  //parse the tree
  while(!frontier->empty()){
    
    //pick the next path
    FlooditPath *next = this->AStarSelect(frontier);


    //check if we reached the goal
    if(next->end()->max_percent() == 100){
      this->best_path_ = next;

      
      //delete allocated stuff
      for(unsigned int i=0; i<frontier->size() ; i++){
        delete frontier->at(i);
      }
      for(unsigned int i=0; i<explored->size() ; i++){
        delete explored->at(i);
      }

      delete frontier;
      delete explored;
      

      return;
    }

    //so that we do not delete the best path
    explored->push_back(next);
    
    //expand the frontier
    BoardTreeNode *to_expand = next->end();
    FlooditBoard *current_board = this->EvalPath(next);

    if(to_expand->num_children() == 0){
      this->GenerateLayers(to_expand, current_board,
                           to_expand->level(),
                           EXPAND_LEVEL(to_expand->level()));
    }

    delete current_board;

    for(int i=0; i<to_expand->num_children() ; i++){
      FlooditPath *new_path = new FlooditPath(next, (*to_expand)[i]);
      frontier->push_back(new_path);
    }

  }

  //if we get here, then we fail.

  
  //delete allocated stuff
  for(unsigned int i=0; i<frontier->size() ; i++){
    delete frontier->at(i);
  }
  for(unsigned int i=0; i<explored->size() ; i++){
    delete explored->at(i);
  }

  delete frontier;
  delete explored;
  
  this->best_path_ = nullptr;
}

    
FlooditPath* FlooditSolver::AStarSelect(std::vector<FlooditPath*>
                                        *frontier){
  double min_score =  HEURISTIC_MULT * (frontier->at(0)->heuristic()) 
      + COST_MULT * (frontier->at(0)->cost());
  int min_index = 0;

  for(unsigned int i=1; i<frontier->size(); i++){
    double score = HEURISTIC_MULT * (frontier->at(i)->heuristic())
        + COST_MULT * (frontier->at(i)->cost());

    if(score < min_score){
      min_score = score;
      min_index = i;
    }
  }

  FlooditPath* ret = frontier->at(min_index);
  frontier->erase(frontier->begin()+min_index);

  return ret;
}

FlooditBoard* FlooditSolver::EvalPath(FlooditPath* path){
  FlooditBoard* current = new FlooditBoard(this->starting_board_);
  
  for(int i=0; i<path->num_steps(); i++){
    current->set_active_color( (*path)[i]->active_color() );
  }

  return current;
}
