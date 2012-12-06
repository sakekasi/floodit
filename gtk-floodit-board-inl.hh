/* This Source Code is subject to the terms of the GNU General
 * Public License 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0.txt */

#ifndef GTK_FLOODIT_BOARD
#define GTK_FLOODIT_BOARD

#include <gtkmm/drawingarea.h>
#include "floodit-board-inl.hh"

#define TOP_YCOORD 0
#define LEFT_XCOORD 0
#define REFRESH_TIME_MILLIS 50

class GtkFlooditBoard: public FlooditBoard, public Gtk::DrawingArea
{
 public:
  GtkFlooditBoard();
  GtkFlooditBoard(FlooditBoard*);

  virtual ~GtkFlooditBoard();

  inline int width() const;
  inline int height() const;

  inline int col_width() const;
  inline int row_height() const;

  inline bool grid_enabled() const;
  inline void toggle_grid_enabled();

  inline void set_active_navy();
  inline void set_active_blue();
  inline void set_active_green();
  inline void set_active_yellow();
  inline void set_active_red();
  inline void set_active_pink();

 protected:

  //drawing
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>&);

  //specific drawing methods
  bool draw_grid(const Cairo::RefPtr<Cairo::Context>&);
  bool fill_grid(const Cairo::RefPtr<Cairo::Context>&);
  bool fill_square(const Cairo::RefPtr<Cairo::Context>&, int, int, color);

  //drawing helper methods
  bool set_color(const Cairo::RefPtr<Cairo::Context>&, color);
  bool on_timeout();

  inline void ShowWin();
  inline void ShowLose();

  int width_;
  int height_;
  const int l_width_;
  bool grid_enabled_;
};

//inline functions
//public

inline int GtkFlooditBoard::width() const
{
  return this->width_;
}

inline int GtkFlooditBoard::height() const
{
  return this->height_;
}

inline int GtkFlooditBoard::col_width() const
{
  return this->width_/(BOARD_SIZE);
}

inline int GtkFlooditBoard::row_height() const
{
  return this->height_/(BOARD_SIZE);
}

inline bool GtkFlooditBoard::grid_enabled() const
{
  return this->grid_enabled_;
}

inline void GtkFlooditBoard::toggle_grid_enabled()
{
  this->grid_enabled_ = !this->grid_enabled_;
}

//button action methods
inline void GtkFlooditBoard::set_active_navy()
{
  color result = this->set_active_color(NAVY);
  if(result == WIN){
    this->ShowWin();
  } else if(result == LOSE){
    this->ShowLose();
  }
}

inline void GtkFlooditBoard::set_active_blue()
{
  color result = this->set_active_color(BLUE);
  if(result == WIN){
    this->ShowWin();
  } else if(result == LOSE){
    this->ShowLose();
  }
}

inline void GtkFlooditBoard::set_active_green()
{
  color result = this->set_active_color(GREEN);
  if(result == WIN){
    this->ShowWin();
  } else if(result == LOSE){
    this->ShowLose();
  }
}

inline void GtkFlooditBoard::set_active_yellow()
{
  color result = this->set_active_color(YELLOW);
  if(result == WIN){
    this->ShowWin();
  } else if(result == LOSE){
    this->ShowLose();
  }
}

inline void GtkFlooditBoard::set_active_red()
{
  color result = this->set_active_color(RED);
  if(result == WIN){
    this->ShowWin();
  } else if(result == LOSE){
    this->ShowLose();
  }
}

inline void GtkFlooditBoard::set_active_pink()
{
  color result = this->set_active_color(PINK);
  if(result == WIN){
    this->ShowWin();
  } else if(result == LOSE){
    this->ShowLose();
  }
}

//private

inline void GtkFlooditBoard::ShowWin()
{
  Gtk::MessageDialog win("You win!");
  win.run();
}

inline void GtkFlooditBoard::ShowLose()
{
  Gtk::MessageDialog lose("You lose.");
  lose.run();
}
#endif
