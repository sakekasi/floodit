/* This Source Code is subject to the terms of the GNU General
 * Public License 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0.txt */

/*
 * floodit-board-inl.hh
 *
 * Defines a class outline and basic inline functions for the floodit
 * board object. Implementations of several more complex functions can be
 * found at floodit-board.cc.
 *
 * Author: Saketh Kasibatla
 */

#ifndef FLOODIT_BOARD_H
#define FLOODIT_BOARD_H

#define NAVY 0
#define BLUE 1
#define GREEN 2
#define YELLOW 3
#define RED 4
#define PINK 5

#define WIN -1
#define LOSE -2

#define BOARD_SIZE 12
#define NUM_COLORS 6
#define MAX_MOVES 22

typedef int color;

class FlooditBoard
{
 public:
  FlooditBoard();
  virtual ~FlooditBoard();

  //accessors
  int max_percent() const;
  inline color color_at(int, int) const;
  inline color active_color() const;
  inline color (*(color_values)())[BOARD_SIZE];
  inline int move_count() const;

  color set_active_color(color);

  void Reset();
        
 protected:

  inline void set_color(int, int, color);
  void h_set_active_color(color, color, int, int);
  
  color color_values_[BOARD_SIZE][BOARD_SIZE];
  int move_count_;
};


//inline function definitions

//public accessors
inline color FlooditBoard::color_at(int i, int j) const
{
  return this->color_values_[i][j];
}

inline color FlooditBoard::active_color() const
{
  return this->color_values_[0][0];
}

inline color (*(FlooditBoard::color_values)())[BOARD_SIZE]
{
  return this->color_values_;
}

inline int FlooditBoard::move_count() const
{
  return this->move_count_;
}

//private mutators
inline void FlooditBoard::set_color(int i, int j, color c)
{
  this->color_values_[i][j] = c;
}
#endif
