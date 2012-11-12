/*
 *floodit-board.cc
 *
 *The implementation of the floodit board object outlined in
 *floodit-board.hh
 *
 *Author: Saketh Kasibatla
 */

#include <cstdlib>
#include <ctime>
#include "floodit-board.hh"

FlooditBoard::FlooditBoard()
{
        srand( time(NULL) );
        
        for(int i=0;i<BOARD_SIZE; i++){
                for(int j=0;j<BOARD_SIZE; j++){
                        this->color_values[i][j] = (rand() % 6);
                }
        }
}


FlooditBoard::~FlooditBoard()
{
}


//public methods

int FlooditBoard::max_percent()
{
        int counts[NUM_COLORS];
        int max_count = 0;

        for(int i=0;i<NUM_COLORS; i++){
                counts[i] = 0;
        }
        
        for(int i=0;i<BOARD_SIZE;i++){
                for(int j=0;j<BOARD_SIZE;j++){
                        counts[this->color_at(i,j)]++;
                }
        }

        for(int i=0;i<NUM_COLORS; i++){
                if(counts[i] > max_count){
                        max_count = counts[i];
                }
        }

        return (max_count/ (BOARD_SIZE*BOARD_SIZE))*100;
}


color FlooditBoard::color_at(int i, int j)
{
        return this->color_values[i][j];
}

color FlooditBoard::get_active_color()
{
        return this->color_values[0][0];
}

color FlooditBoard::set_active_color(color new_color)
{
        color active = this->get_active_color();

        if(new_color != active){
                this->h_set_active_color(active,
                                         new_color,
                                         0,0);
        }
        return active;
}

color (*(FlooditBoard::get_color_values)())[BOARD_SIZE]
{
        return this->color_values;
}


//protected functions

void FlooditBoard::h_set_active_color(color act, color new_act, int i, int j)
{
        if(i<0 || j<0 || i>BOARD_SIZE || j>BOARD_SIZE){
                return;
        }
        
        if(this->color_at(i,j) == act){
                this->set_color(i,j,new_act);
                this->h_set_active_color(act, new_act, i-1, j);
                this->h_set_active_color(act, new_act, i+1, j);
                this->h_set_active_color(act, new_act, i, j-1);
                this->h_set_active_color(act, new_act, i, j+1);
        }
}

void FlooditBoard::set_color(int i, int j, color c)
{
        this->color_values[i][j] = c;
}
