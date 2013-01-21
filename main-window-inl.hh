#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


//import buttons and use them.
#include <gtkmm.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/toggletoolbutton.h>
#include "gtk-floodit-board-inl.hh"

class MainWindow : public Gtk::Window
{
 public:
  MainWindow();
  virtual ~MainWindow();
        
 protected:
  Gtk::VBox vbox_;
  Gtk::HBox color_box_;
  Gtk::HBox control_box_;
        
  GtkFlooditBoard board_;

  int score_;
  color active_color_;

  Gtk::ToggleButton grid_on_;
  Gtk::Button reset_;
  Gtk::Button score_button_;
  Gtk::Button solve_;

  Gtk::Button *color_buttons_[6];

  inline void update_score();

  void solve_board();
};

//inline function definitions
void MainWindow::update_score()
{
  this->score_button_.set_label(std::to_string(this->board_.move_count())
                               + "/" + std::to_string(MAX_MOVES));
}

#endif        
