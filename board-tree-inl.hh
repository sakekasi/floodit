#ifndef BOARD_TREE_H
#define BOARD_TREE_H

#include "floodit-board-inl.hh"
#include <vector>


/*
 * A BoardTreeNode is a node in the AI's tree representation of the game.
 * These make up the tree representation of the floodit game and the
 * paths that the AI generates by searching this tree.
 */
class BoardTreeNode {
 public:
  BoardTreeNode();
  BoardTreeNode(FlooditBoard *);
  BoardTreeNode(color, int);

  virtual ~BoardTreeNode();

  //accessors
  inline color active_color() const;
  inline int max_percent() const;
  inline int level() const;
  inline int num_children() const;

  //mutators
  inline void set_active_color(color);
  inline void set_max_percent(int);
  inline void set_level(int);
  inline void add_child(BoardTreeNode *);
  inline void add_child(color, int);

  //operators
  inline BoardTreeNode* operator[](int);
  inline BoardTreeNode* child(int);
        
 protected:
  color active_color_;
  int max_percent_;
  int level_;
 
  std::vector<BoardTreeNode*> children_;
  
};

/*
 * A FlooditPath is a basic container for BoardTreeNodes. It indicates
 * the order of nodes and moves that an AI should take.
 */
class FlooditPath {
 public:
  FlooditPath(FlooditBoard *);
  FlooditPath(BoardTreeNode *);
  /*
   * A copy constructor that appends a new node to the end.
   */
  FlooditPath(FlooditPath*, BoardTreeNode*);

  /*
   * Destructor. Because a FlooditPath is made from a tree, and we do
   * not want to accidentaly destroy parts of the tree, the path
   * does not destroy the nodes it contains.
   */
  virtual ~FlooditPath();

  //accessors
  inline int heuristic() const;
  inline int cost() const;
  inline int num_steps() const;

  //mutators
  inline void add(BoardTreeNode*);
  inline void pop();
  inline BoardTreeNode* end();

  //operators
  inline BoardTreeNode* operator[](int);
  inline BoardTreeNode* step(int);

 protected:
  std::vector<BoardTreeNode*> nodes_;
};

//INLINE FUNCTIONS
//================
//BoardTreeNode public
//--------------------
//accessors
inline color BoardTreeNode::active_color() const {
  return this->active_color_;
}

inline int BoardTreeNode::max_percent() const {
  return this->max_percent_;
}

inline int BoardTreeNode::level() const{
  return this->level_;
}

inline int BoardTreeNode::num_children() const{
  return this->children_.size();
}

//mutators
inline void BoardTreeNode::set_active_color(color c){
  this->active_color_ = c;
}

inline void BoardTreeNode::set_max_percent(int i){
  this->max_percent_ = i;
}

inline void BoardTreeNode::set_level(int l){
  this->level_ = l;
}

inline void BoardTreeNode::add_child(BoardTreeNode *n)
{
  this->children_.push_back(n);
}

inline void BoardTreeNode::add_child(color c, int i){
  this->children_.push_back(new BoardTreeNode(c,i));
}

//operators
inline BoardTreeNode* BoardTreeNode::operator[](int i)
{
  return this->children_[i];
}

inline BoardTreeNode* BoardTreeNode::child(int i)
{
  return this->children_[i];
}

//FlooditPath public
//------------------

//accessors

/*
 * heuristic provides an estimate as to how close to the
 * solution this particular node is. In this case, the heuristic
 * function gives the 100 - the max percent of the board taken up by
 * one color.
 */
inline int FlooditPath::heuristic() const{
  return 100 - this->nodes_[this->nodes_.size()-1]->max_percent();
}

inline int FlooditPath::num_steps() const{
  return this->nodes_.size();
}


/*
 * cost provides the actual cost that it took to follow
 * the path in question. In this case, the cost is how many steps it
 * took to get to the current state.
 */
inline int FlooditPath::cost() const{
  return this->nodes_.size();
}

//mutators
inline void FlooditPath::add(BoardTreeNode *n){
  this->nodes_.push_back(n);
}

inline void FlooditPath::pop(){
  this->nodes_.erase(this->nodes_.begin());
}

inline BoardTreeNode* FlooditPath::end(){
  return this->nodes_[this->nodes_.size()-1];
}

//operators
inline BoardTreeNode* FlooditPath::operator[](int i){
  return this->step(i);
}

inline BoardTreeNode* FlooditPath::step(int i){
  return this->nodes_[i];
}

#endif

