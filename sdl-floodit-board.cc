/*
 *sdl-floodit-board.cc
 *
 *A SDL subclass of FlooditBoard that can draw itself.
 *
 *Author: Saketh Kasibatla
 */
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <cstring>
#include <iostream>

#include "sdl-floodit-board-inl.hh"

using namespace std;

SDLFlooditBoard::SDLFlooditBoard(SDL_Surface* s)
    : FlooditBoard(), _screen(s)
{
}

SDLFlooditBoard::SDLFlooditBoard(SDL_Surface* s, FlooditBoard *f)
    : FlooditBoard(f), _screen(s)
{
}

SDLFlooditBoard::~SDLFlooditBoard()
{
}

void SDLFlooditBoard::button_clicked(color c)
{
    switch(c){
    case NAVY:
        set_active_navy();
        break;
    case BLUE:
        set_active_blue();
        break;
    case GREEN:
        set_active_green();
        break;
    case YELLOW:
        set_active_yellow();
        break;
    case RED:
        set_active_red();
        break;
    case PINK:
        set_active_pink();
        break;
    }
}

void SDLFlooditBoard::draw()
{
    fill_grid();
}

void SDLFlooditBoard::fill_grid()
{
    for(int i=0; i<BOARD_SIZE; i++){
        for(int j=0; j<BOARD_SIZE; j++){
            color c = color_at(i,j);
            fill_square(i, j, c);
        }
    }
}

void SDLFlooditBoard::fill_square(int i, int j, color c)
{
    boxRGBA( _screen,
             SQUARE_WIDTH*i, SQUARE_WIDTH*j,
             SQUARE_WIDTH*(i+1), SQUARE_WIDTH*(j+1),
             COLORS_RGB[c][0], COLORS_RGB[c][1], COLORS_RGB[c][2],
             OPAQUE );
}

