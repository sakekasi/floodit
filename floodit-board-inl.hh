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

enum color {
    NAVY = 0,
    BLUE = 1,
    GREEN = 2,
    YELLOW = 3,
    RED = 4,
    PINK = 5,
    NIL = -1,
    WIN = -2,
    LOSE = -3
};

#define BOARD_SIZE 12
#define NUM_COLORS 6
#define NULL_COLOR -1
#define MAX_MOVES 22

class FlooditBoard
{
public:
  FlooditBoard();
  FlooditBoard(FlooditBoard *);
  FlooditBoard(FlooditBoard *, color);
  virtual ~FlooditBoard();

  //operators
  FlooditBoard& operator=(const FlooditBoard&);
  bool operator==(const FlooditBoard&);

  //accessors
  int max_percent() const;
  inline color color_at(int, int) const;
  inline color active_color() const;
  inline color** color_values() const;
  inline int move_count() const;

  color set_active_color(color);

  void Reset();
        
private:

  inline void set_color(int, int, color);
  void h_set_active_color(color, color, int, int);
  
  color** color_values_;
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

inline color** FlooditBoard::color_values() const
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
