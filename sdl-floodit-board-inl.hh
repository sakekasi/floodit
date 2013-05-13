
/* This Source Code is subject to the terms of the GNU General
 * Public License 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0.txt */

#ifndef SDL_FLOODIT_BOARD
#define SDL_FLOODIT_BOARD
#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

#include "sdl-buttons-inl.hh"
#include "sdl-constants.hh"
#include "constants.hh"

#define SQUARE_WIDTH HEIGHT/BOARD_SIZE
#define L_WIDTH 1

class SDLFlooditBoard : public FlooditBoard, public ButtonListener
{
public:
    SDLFlooditBoard(SDL_Surface*);
    SDLFlooditBoard(SDL_Surface*, FlooditBoard*);

    virtual ~SDLFlooditBoard();

    inline int width() const;
    inline int height() const;

    inline int col_width() const;
    inline int row_height() const;

    inline void set_active_navy();
    inline void set_active_blue();
    inline void set_active_green();
    inline void set_active_yellow();
    inline void set_active_red();
    inline void set_active_pink();

    inline void set_active_color(color c);

    void button_clicked(color);

    //drawing    
    virtual void draw();

private:
    SDL_Surface* _screen;

    //specific drawing methods
    void fill_grid();
    void fill_square(int, int, color);

    //drawing helper methods
    bool set_color(color);

    inline void ShowWin();
    inline void ShowLose();
};

//inline functions
//public

inline int SDLFlooditBoard::col_width() const
{
  return WIDTH/(BOARD_SIZE);
}

inline int SDLFlooditBoard::row_height() const
{
  return HEIGHT/(BOARD_SIZE);
}

//button action methods
inline void SDLFlooditBoard::set_active_navy()
{
  this->set_active_color(NAVY);        
}

inline void SDLFlooditBoard::set_active_blue()
{
  this->set_active_color(BLUE);      
}

inline void SDLFlooditBoard::set_active_green()
{
  this->set_active_color(GREEN);    
}

inline void SDLFlooditBoard::set_active_yellow()
{
  this->set_active_color(YELLOW);  
}

inline void SDLFlooditBoard::set_active_red()
{
  this->set_active_color(RED);
}

inline void SDLFlooditBoard::set_active_pink()
{
  this->set_active_color(PINK);
}

inline void SDLFlooditBoard::set_active_color(color c)
{
    color a = FlooditBoard::active_color();
    color r = FlooditBoard::set_active_color(c);
    if( r == WIN )
        ShowWin();
    else if( r == LOSE )
        ShowLose();
    else if( c != a )
        std::cout << FlooditBoard::move_count() << "/" << MAX_MOVES << std::endl;
}


inline void SDLFlooditBoard::ShowWin()
{
    std::cout << "WIN" << std::endl;
}

inline void SDLFlooditBoard::ShowLose()
{
    std::cout << "LOSE" << std::endl;
}



#endif //SDL_FLOODIT_BOARD
