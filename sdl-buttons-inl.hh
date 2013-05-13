#ifndef SDL_BUTTONS_HH
#define SDL_BUTTONS_HH
#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <unordered_set>

#include "floodit-board-inl.hh"
#include "sdl-constants.hh"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 100
#define BUTTON_LEFT_X 600

class ButtonListener;

class SDLButtons
{
public:
    SDLButtons(SDL_Surface*);
    virtual ~SDLButtons();

    void clicked(int, int);

    inline void add_listener(ButtonListener*);
    inline void add_listener(ButtonListener&);

    virtual void draw();    
    
private:
    SDL_Surface* _screen;
    std::unordered_set<ButtonListener*>* _listeners;

    //drawing

};

inline void SDLButtons::add_listener(ButtonListener* b)
{
    _listeners->insert(b);
}

inline void SDLButtons::add_listener(ButtonListener& b)
{
    _listeners->insert(&b);
}

class ButtonListener
{
public:
    virtual void button_clicked(color) =0;
};




#endif
