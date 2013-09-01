#include "board-tree-inl.hh"

BoardTreeNode::BoardTreeNode(FlooditBoard* other)
{
    _board = new FlooditBoard(other);

    for( int i=0; i<NUM_COLORS; i++){
        if( (color) i == active_color() )
            continue;
        _children[i] = new BoardTreeNode(other, i);
    }
}

BoardTreeNode::BoardTreeNode(FlooditBoard& other)
    :BoardTreeNode(&other)
{
}

BoardTreeNode::BoardTreeNode(FlooditBoard* other, color c)
    :BoardTreeNode(other)
{
    _board->set_active_color(c);
}

BoardTreeNode::~BoardTreeNode()
{
}


double BoardPath::g_score()
{
    return top()->move_count() * HEURISTIC_WEIGHT;
}

double BoardPath::f_score()
{
    return g_score() + top()->heuristic();
}

