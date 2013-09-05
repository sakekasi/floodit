#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include <string>
#include <iostream>
#include <cstring>
#include <pthread.h>

#include "constants.hh"
#include "sdl-constants.hh"
#include "constants.hh"
#include "sdl-floodit-board-inl.hh"
#include "sdl-buttons-inl.hh"
#include "board-tree-gen.hh"
#include "board-tree-search.hh"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const string WINDOW_TITLE = "floodit";

bool ctrl_pressed = false;
bool ai_solving = false;

struct ai_args
{
    SDLAiHook *ai_hook;
    FlooditBoard *board;
};

static void
start_ai_solve(void *threadarg)
{
    struct ai_args *arg = (struct ai_args *) threadarg;

    arg->ai_hook->calculate_path(arg->board);

    pthread_exit(NULL);
}

class MainAiListener 
{
public:
    void path_calculated()
        {
            ai_solving=false;
        }
};

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
  
    if( SDL_Init( SDL_INIT_EVERYTHING == -1 ) ){
        return 1;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
                               SDL_SWSURFACE);

    SDL_WM_SetCaption( WINDOW_TITLE.c_str() , NULL);

    //CREATE GAME OBJECT
    SDLFlooditBoard game(screen);
    SDLButtons buttons(screen);
    SDLAiHook ai_hook();
    MainAiListener ml();

    buttons.add_listener(game);
    ai_hook.add_listener(ml);

    SDL_Event event;
    bool gameRunning = true;
    bool left_clicked = false, right_clicked = false;

    while(gameRunning)
    {
        if(!ai_solving){
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
                    if( event.button.button == SDL_BUTTON_LEFT )
                        left_clicked = false;
                    if( event.button.button == SDL_BUTTON_RIGHT )
                        right_clicked = false;
                }
                else if( event.type == SDL_MOUSEMOTION )
                {
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
                    case SDLK_LCTRL:
                    case SDLK_RCTRL:
                        ctrl_pressed = true;
                        break;
                    case SDLK_SPACE:
                        if(ctrl_pressed){
                            ai_solving = true;
                            buttons.enabled=false;

                            struct ai_args args;
                            args.ai_hook = &ai_hook;
                            args.board = (FlooditBoard*) &game;

                            pthread_t thread;
                            int rc = pthread_create(&threads[tnum],
                                                    NULL,
                                                    start_ai_solve,
                                                    (void*) &args);
                            if (rc){
                                exit(-1);
                            }
                        }
                        break;
                    default:
                        ;
                    }
                } else if ( event.type == SDL_KEYUP ){
                    switch( event.key.keysym.sym ){
                    case SDLK_LCTRL:
                    case SDLK_RCTRL:
                        ctrl_pressed = false;
                        break;
                    default:
                        ;
                    }
                }
            }

            color next = ai_hook.next();
            if(next != NIL){
                switch(next){
                case NAVY:
                    game.set_active_navy();
                    break;
                case BLUE:
                    game.set_active_blue();
                    break;
                case GREEN:
                    game.set_active_green();
                    break;
                case YELLOW:
                    game.set_active_yellow();
                    break;
                case RED:
                    game.set_active_red();
                    break;
                case PINK:
                    game.set_active_pink();
                    break;
                default:
                    exit(-1);
                }
            } else {
                buttons.enabled=true;
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
