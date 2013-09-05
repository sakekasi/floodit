#ifndef SDL_AI_HOOK_H
#define SDL_AI_HOOK_H
#pragma once

#include <unordered_set>

#include "board-tree-gen.hh"
#include "board-tree-search.hh"

class AIListener;

class SDLAiHook
{
public:
    SDLAiHook();
    virtual ~SDLAiHook();

    void calculate_path(FlooditBoard*);
    color next();

    inline void add_listener(AIListener*);

private:
    std::unordered_set<AIListener*> *_listeners;
    BoardTreePath *_best_path;
};

inline void add_listener(AIlistener ail)
{
    _listeners->insert(ail);
}

class AIListener
{
public:
    virtual void path_calculated() = 0;
};

#endif // SDL_AI_HOOK_H
