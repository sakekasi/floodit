#ifndef BOARD_TREE_HH
#define BOARD_TREE_HH
#pragma once

#include "floodit-board-inl.hh"

class BoardTreeNode
{
public:
    BoardTreeNode(FlooditBoard*);
    BoardTreeNode(FlooditBoard&);
    BoardTreeNode(FlooditBoard*, color);
    virtual ~BoardTreeNode();

    inline int move_count();
    inline int heuristic();
    inline color active_color();
    
private:
    FlooditBoard* _board;
    BoardTreeNode* _children[NUM_COLORS];
};

inline int BoardTreeNode::move_count()
{
    return _board->move_count();
}

inline int BoardTreeNode::heuristic()
{
    return _board->max_percent();
}

inline color active_color()
{
    return _board->active_color();
}


    

#endif //BOARD_TREE_HH
