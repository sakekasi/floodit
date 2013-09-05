#include "board-tree-gen.hh"

BoardTreeNode* generate_board_tree(FlooditBoard *board)
{
    return new BoardTreeNode(board);
}
