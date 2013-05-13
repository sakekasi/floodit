#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <string>
#include <iostream>
#include <cstring>

#include "constants.hh"
#include "sdl-constants.hh"
#include "constants.hh"
#include "sdl-floodit-board-inl.hh"
#include "sdl-buttons-inl.hh"


using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const string WINDOW_TITLE = "floodit";


int main( int argc, char* argv[] )
{

    //USAGE
    if( argc > 1 )
    {
        if (strcmp(argv[1],"-h") == 0)
        {
            exit(0);
        }
    }
  
      
  
    SDL_Surface* screen = NULL;
  
    if( SDL_Init( SDL_INIT_EVERYTHING == -1 ) )
        return 1;

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
                               SDL_SWSURFACE);

    SDL_WM_SetCaption( WINDOW_TITLE.c_str() , NULL);

    //CREATE GAME OBJECT
    SDLFlooditBoard game(screen);
    SDLButtons buttons(screen);

    buttons.add_listener(game);

    SDL_Event event;
    bool gameRunning = true;
    bool left_clicked = false, right_clicked = false;
    // bool iterating = false;

    while(gameRunning)
    {
        while( SDL_PollEvent(&event) )
        {
            if( event.type == SDL_QUIT )
                gameRunning = false;
            else if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                int x = event.button.x;
                int y = event.button.y;
	      
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    buttons.clicked(x, y);
                }
                
                else if( event.button.button == SDL_BUTTON_RIGHT )
                {
                }
            }
            else if( event.type == SDL_MOUSEBUTTONUP )
            {
                // int x = event.button.x;
                // int y = event.button.y;

                if( event.button.button == SDL_BUTTON_LEFT )
                    left_clicked = false;
                if( event.button.button == SDL_BUTTON_RIGHT )
                    right_clicked = false;
            }
            else if( event.type == SDL_MOUSEMOTION )
            {
                // int x = event.motion.x;
                // int y = event.motion.y;

                if( left_clicked )
                    ;
                else if( right_clicked )
                {
                }
            }
            else if( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                case SDLK_ESCAPE:
                    goto end;
                case SDLK_1:
                    game.button_clicked(static_cast<color>(0));
                    break;
                case SDLK_2:
                    game.button_clicked(static_cast<color>(1));
                    break;                    
                case SDLK_3:
                    game.button_clicked(static_cast<color>(2));
                    break;                    
                case SDLK_4:
                    game.button_clicked(static_cast<color>(3));
                    break;                    
                case SDLK_5:
                    game.button_clicked(static_cast<color>(4));
                    break;                    
                case SDLK_6:
                    game.button_clicked(static_cast<color>(5));
                    break;
                default:
                    ;
                }
            }
        }
    
        game.draw();
        buttons.draw();

        SDL_Flip(screen);
        //      SDL_Delay(1);
        // if(iterating)
        //     game.iterate();
    }

end:    

    SDL_FreeSurface(screen);
    SDL_Quit();

    return 0;
}
