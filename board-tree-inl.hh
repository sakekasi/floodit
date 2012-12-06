#ifndef BOARD_TREE_H
#define BOARD_TREE_H

#include "floodit-board-inl.hh"
#include <vector>
#include <memory>
using namespace std; // may not want to include this here.

class BoardTreeNode {
 public:
  BoardTreeNode(FlooditBoard *);
  BoardTreeNode(color, int);

  virtual ~BoardTreeNode()
        
  inline color active_color() const;
  inline int max_percent() const;

  inline void set_active_color(color);
  inline void set_max_percent(int);

  inline void add_child(BoardTree_Node *);
  inline void add_child(color, int);

  inline BoardTreeNode* operator[](int);
  inline BoardTreeNode* child(int);
        
 protected:
  color active_color_;
  int max_percent_;
 
  vector<BoardTreeNode*> children_;
  
};

//inline functions
//public
inline color BoardTreeNode::active_color() const {
  return this->active_color_;
}

inline int BoardTreeNode::max_percent() const {
  return this->max_percent_;
}

inline void BoardTreeNode::set_active_color(color c){
  this->active_color_ = c;
}

inline void BoardTreeNode::set_max_percent(int i){
  this->max_percent_ = i;
}

inline void BoardTreeNode::add_child(BoardTreeNode *n)
{
  this->children_.push_back(n);
}

inline void BoardTreeNode::add_child(color c, int i){
  this->children_.push_back(new BoardTreeNode(c,i));
}

inline BoardTreeNode* BoardTreeNode::operator[](int i)
{
  return this->children_[i];
}

inline BoardTreeNode* BoardTreeNode::child(int i)
{
  return this->children_[i];
}

#endif
