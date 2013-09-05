#include "sdl-ai-hook-inl.hh"

using namespace std;

SDLAiHook::SDLAiHook()
    :_best_path(NULL)
{
    _listeners = new unordered_set<AIListener*>();
}

SDLAiHook::~SDLAiHook()
{
    delete _listeners;
}

void SDLAiHook::calculate_path(FlooditBoard *board)
{
    BoardTreeNode *tree = generate_board_tree(board);
    BoardTreePath *best_path = a_star_solve(tree);

    _best_path = best_path;

    for(unordered_set<AIListener*>::iterator it = _listeners->begin();
        it != _listeners->end();
        it++){
        (*it)->path_calculated();
    }
}

color SDLAiHook::next()
{
    color ret = NIL;
    if(_best_path){
        ret = _best_path->top()->active_color();
    }

    return ret;
}

