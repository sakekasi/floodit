#include "board-tree-inl.hh"
#include <cstdlib>

BoardTreeNode::BoardTreeNode(FlooditBoard* other)
{
    _board = new FlooditBoard(other);

    for( int i=0; i<NUM_COLORS; i++){
        if( (color) i == active_color() ){
            _children[i] = NULL;
        } else {
            _children[i] = new BoardTreeNode(other, (color) i);
        }
    }
}

BoardTreeNode::BoardTreeNode(FlooditBoard* other, color c)
    :BoardTreeNode(other)
{
    _board->set_active_color(c);
}

BoardTreeNode::~BoardTreeNode()
{
    for( int i=0; i<NUM_COLORS; i++){
        if( _children[i] ){
            delete _children[i];
        }
    }
}


BoardPath::BoardPath(BoardTreeNode *node)
{
    push(node);
}

BoardPath::BoardPath(BoardPath *path, BoardTreeNode *node)
    :stack<BoardTreeNode*>(*path)
{
    push(node);
}

double BoardPath::g_score()
{
    return top()->move_count() * HEURISTIC_WEIGHT;
}

double BoardPath::f_score()
{
    return g_score() + top()->heuristic();
}

