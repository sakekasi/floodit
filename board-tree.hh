#ifndef BOARD_TREE_H
#define BOARD_TREE_H

#include "floodit-board.hh"
#include <vector>
#include <memory>
using namespace std; // may not want to include this here.

class BoardTree_Node
{
 public:
  BoardTree_Node(FlooditBoard *);
  BoardTree_Node(auto_ptr<FlooditBoard>);
        
  void set_board(auto_ptr<FlooditBoard>);
  void set_board(FlooditBoard *);

  color get_active_color();
  int max_percent();

  void add_child(auto_ptr<BoardTree_Node>);
  void add_child(BoardTree_Node *);

  auto_ptr<BoardTree_Node> operator[](int);
  auto_ptr<BoardTree_Node> get_child(int);
        
 protected:
        
  vector<auto_ptr<BoardTree_Node>> children;
  auto_ptr<FlooditBoard> board;
};

#endif
