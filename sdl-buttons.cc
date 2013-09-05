/*
 *sdl-buttons.cc
 *
 *An sdl interface to draw buttons.
 *
 *Author: Saketh Kasibatla
 */
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <unordered_set>

#include "sdl-buttons-inl.hh"

using namespace std;

SDLButtons::SDLButtons(SDL_Surface *s)
    :enabled(true), _screen(s)
{
    _listeners = new unordered_set<ButtonListener*>();
}

SDLButtons::~SDLButtons()
{
    delete _listeners;
}

void SDLButtons::clicked( int x, int y )
{
    if(enabled){
        if( x >= BUTTON_LEFT_X && x <= WIDTH )
            for( unordered_set<ButtonListener*>::iterator it =
                     _listeners->begin(); it != _listeners->end(); it++ )
                (*it)->button_clicked(static_cast<color>(y / BUTTON_HEIGHT));
    }
}

void SDLButtons::draw()
{
//draw boxes
    for( int i=0; i<NUM_COLORS; i++ ){
        boxRGBA( _screen,
                 BUTTON_LEFT_X, i*BUTTON_HEIGHT,
                 WIDTH, (i+1)*BUTTON_HEIGHT,
                 COLORS_RGB[i][0], COLORS_RGB[i][1], COLORS_RGB[i][2],
                 OPAQUE);
    }


//draw lines

    thickLineRGBA( _screen,
                   BUTTON_LEFT_X, TOP_YCOORD,
                   BUTTON_LEFT_X, HEIGHT,
                   LINE_WIDTH,
                   BLACK_R, BLACK_G, BLACK_B, OPAQUE);
    
}
