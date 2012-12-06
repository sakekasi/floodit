/* This Source Code is subject to the terms of the GNU General
 * Public License 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0.txt */

/*
 * floodit-board.cc
 *
 * The implementation of the floodit board object outlined in
 * floodit-board.hh
 *
 * Author: Saketh Kasibatla
 */

#include <cstdlib>
#include <ctime>
#include "floodit-board-inl.hh"

FlooditBoard::FlooditBoard()
{
  this->Reset();
}


FlooditBoard::~FlooditBoard()
{
}


//public methods

int FlooditBoard::max_percent() const
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




color FlooditBoard::set_active_color(color new_color)
{
  color active_color = this->active_color();

  if(new_color != active_color){
    (this->move_count_)++;
    this->h_set_active_color(active_color,
                             new_color,
                             0,0);
    if(this->max_percent() == 100){
      this->Reset();
      return WIN;
    }
                
    if(this->move_count_ == MAX_MOVES){
      int max_percent = this->max_percent();
      this->Reset();
      if(max_percent == 100){
        return WIN;
      } else {
        return LOSE;
      }
    }
  }
  return active_color;
}

void FlooditBoard::Reset()
{
  this->move_count_ = 0;
  srand( time(NULL) );

  for(int i=0; i<BOARD_SIZE; i++){
    for(int j=0; j<BOARD_SIZE; j++){
      this->set_color(i,j,rand()%NUM_COLORS);
    }
  }
}



//protected functions

void FlooditBoard::h_set_active_color(color act, color new_act, int i, int j)
{
  if(i<0 || j<0 || i>=BOARD_SIZE || j>=BOARD_SIZE){
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




