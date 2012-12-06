/*
 *board-tree.cc
 *
 *an implementation of an n-ary tree of boards for the floodit AI.
 *
 *Author: Saketh Kasibatla
 */
#include "board-tree-inl.hh"

//public functions

BoardTreeNode::BoardTreeNode(FlooditBoard* b)
    :active_color_(b->active_color()), max_percent_(b->max_percent()),
     children()
{
}

BoardTreeNode::BoardTreeNode(color c, int i)
    :active_color_(c), max_percent_(i), children_()
{
}

BoardTreeNode::~BoardTreeNode(){
  for(int i=0;i<this->children_.size(); i++){
    delete this->children[i];
  }
}
