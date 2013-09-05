#include "board-tree-search.hh"

#include <set>
#include <cstdlib>

using namespace std;

BoardPath* lowest_value_path(set<BoardPath*> *frontier);
bool goal(BoardPath *path);
bool contains(set<BoardPath*> *set, BoardTreeNode *node);

BoardPath* a_star_solve(BoardTreeNode *root)
{
    //visited: node set already evaluated
    set<BoardPath*> visited;
    
    //frontier: the set of nodes currently to be eval'd
    set<BoardPath*> frontier;

    BoardPath *current = new BoardPath(root);
    current->push(root);

    frontier.insert(current);

    while(!frontier.empty()){
        current = lowest_value_path(&frontier);

        //  if current == goal:
        if( goal(current) ){
            return current;
        }

        //  move current from frontier to visited
        frontier.erase(current);
        visited.insert(current);
        
        //  for each child:
        for(int i=0; i<NUM_COLORS; i++){
            if(current->top()->child(i)){
                //if neighbor in closedset:
                if(contains(&visited, current->top()->child(i))){
                    continue;
                } else {
                    frontier.insert(new BoardPath(current,
                                                  current->top()->child(i)));
                }
            }
        }
    }
    
    return NULL;
}

BoardPath* lowest_value_path(set<BoardPath*> *frontier)
{
    BoardPath *ret = *(frontier->begin());

    for(set<BoardPath*>::iterator it = frontier->begin() + 1;
        it != frontier->end();
        it++){
        if( (*it)->f_score < ret->f_score() ){
            ret = (*it);
        }
    }

    return ret;
}

bool goal(BoardPath *path)
{
    return path->top()->heuristic() == 100;
}

bool contains(set<BoardPath*> *set, BoardTreeNode *node)
{
    for(set<BoardPath*>::iterator it = set->begin();
        it != set->end();
        it++){
        if( (*it)->top() == node ){
            return true;
        }
    }

    return false;
}

