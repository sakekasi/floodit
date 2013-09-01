#ifndef BOARD_TREE_HH
#define BOARD_TREE_HH
#pragma once

#include "floodit-board-inl.hh"

#include <stack>

#define HEURISTIC_WEIGHT 100.0/MAX_MOVES
    

class BoardTreeNode
{
public:
    BoardTreeNode(FlooditBoard*);
    BoardTreeNode(FlooditBoard*, color);
    virtual ~BoardTreeNode();

    inline int move_count();
    inline int heuristic();
    inline color active_color();

    inline BoardTreeNode* child(int i);
    
private:
    FlooditBoard* _board;
    BoardTreeNode* _children[NUM_COLORS];
};

class BoardPath : std::stack<BoardTreeNode*>
{
public:
    BoardPath(BoardPath*, BoardTreeNode*);
    
    double g_score(); //known cost from start
    double f_score(); //estimated cost with heuristic
}

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

inline BoardTreeNode* child(int i)
{
    return _children[i];
}


#endif //BOARD_TREE_HH
