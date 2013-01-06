/*
 *board-tree.cc
 *
 *an implementation of an n-ary tree of boards for the floodit AI.
 *
 *Author: Saketh Kasibatla
 */
#include "board-tree-inl.hh"

//BoardTreeNode public
//--------------------
//constructors
BoardTreeNode::BoardTreeNode()
    :active_color_(NULL_COLOR), max_percent_(-1), children_()
{
}

BoardTreeNode::BoardTreeNode(FlooditBoard* b)
    :active_color_(b->active_color()), max_percent_(b->max_percent()),
     children_()
{
}

BoardTreeNode::BoardTreeNode(color c, int i)
    :active_color_(c), max_percent_(i), children_()
{
}

//destructor
BoardTreeNode::~BoardTreeNode(){
  for(unsigned int i=0;i<this->children_.size(); i++){
    delete this->children_[i];
  }
}


//FlooditPath public
//------------------
//constructors
FlooditPath::FlooditPath(BoardTreeNode* n)
    :nodes_()
{
  this->nodes_.push_back(n);
}

FlooditPath::FlooditPath(FlooditBoard* b)
    :FlooditPath(new BoardTreeNode(b))
{
}

FlooditPath::FlooditPath(FlooditPath* path, BoardTreeNode* end){
  for(int i=0; i<path->num_steps() ; i++){
    this->nodes_.push_back( (*path)[i] );
  }
  this->nodes_.push_back(end);
}


//destructor
FlooditPath::~FlooditPath()
{
}

