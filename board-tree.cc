/*
 *board-tree.cc
 *
 *an implementation of an n-ary tree of boards for the floodit AI.
 *
 *Author: Saketh Kasibatla
 */
#include "board-tree.hh"

//public functions

BoardTree_Node::BoardTree_Node(FlooditBoard* b)
    :BoardTree_Node(new auto_ptr<FlooditBoard>(b))
{
}

BoardTree_Node::BoardTree_Node(auto_ptr<FlooditBoard> b)
{
  this->set_board(b);
}


void BoardTree_Node::set_board(auto_ptr<FlooditBoard> b)
{
  this->board = b;
}

void BoardTree_Node::set_board(FlooditBoard* b)
{
  this->set_board(new auto_ptr<FlooditBoard>(b));
}


color BoardTree_Node::get_active_color()
{
  return this->board->get_active_color();
}

int BoardTree_Node::max_percent()
{
  return this->board->max_percent();
}


void BoardTree_Node::add_child(auto_ptr<BoardTree_Node> n)
{
  this->children.push_back(n);
}

void BoardTree_Node::add_child(BoardTree_Node *n)
{
  this->add_child(new auto_ptr<BoardTree_Node>(n));
}


auto_ptr<BoardTree_Node> BoardTree_Node::operator[](int i)
{
  return this->get_child(i);
}

auto_ptr<BoardTree_Node> BoardTree_Node::get_child(int i)
{
  return this->children[i];
}
