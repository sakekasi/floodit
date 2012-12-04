/*
 *main-window.cc
 *
 *The main window containing the floodit board
 *
 *Author: Saketh Kasibatla
 */
#include "main-window.hh"
#include <cstdlib>
#include <string>
#include <cstring>

MainWindow::MainWindow()
    :Gtk::Window(), vbox(false), hbox(true), board(), score(0), active_color(this->board.get_active_color()),
     toolbar(), grid_on("Hide Grid"), reset("Reset"), score_button(std::to_string(this->score) + "/" + std::to_string(MAX_MOVES))
{

  this->set_title("Floodit");
  this->set_default_size(400,400);

  for(int i=0; i<NUM_COLORS; i++){
    switch(i){
      case NAVY:
        this->color_buttons[i] = new Gtk::Button("NAVY");
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                       &GtkFlooditBoard::set_active_navy));
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(*this,
                                                                       &MainWindow::update_score));
        this->hbox.pack_start(*(this->color_buttons[i]));
        break;
      case BLUE:
        this->color_buttons[i] = new Gtk::Button("BLUE");
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                       &GtkFlooditBoard::set_active_blue));
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(*this,
                                                                       &MainWindow::update_score));
        this->hbox.pack_start(*(this->color_buttons[i]));
        break;
      case GREEN:
        this->color_buttons[i] = new Gtk::Button("GREEN");
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                       &GtkFlooditBoard::set_active_green));
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(*this,
                                                                       &MainWindow::update_score));
        this->hbox.pack_start(*(this->color_buttons[i]));
        break;
      case YELLOW:
        this->color_buttons[i] = new Gtk::Button("YELLOW");
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                       &GtkFlooditBoard::set_active_yellow));
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(*this,
                                                                       &MainWindow::update_score));
        this->hbox.pack_start(*(this->color_buttons[i]));
        break;
      case RED:
        this->color_buttons[i] = new Gtk::Button("RED");
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                       &GtkFlooditBoard::set_active_red));
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(*this,
                                                                       &MainWindow::update_score));
        this->hbox.pack_start(*(this->color_buttons[i]));
        break;
      case PINK:
        this->color_buttons[i] = new Gtk::Button("PINK");
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                       &GtkFlooditBoard::set_active_pink));
        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(*this,
                                                                       &MainWindow::update_score));
        this->hbox.pack_start(*(this->color_buttons[i]));
        break;
      default:
        this->color_buttons[i] = new Gtk::Button();
    }
  }

  this->grid_on.signal_toggled().connect(sigc::mem_fun(this->board, &GtkFlooditBoard::toggle_grid_enabled));
  this->reset.signal_clicked().connect(sigc::mem_fun(this->board, &GtkFlooditBoard::h_reset));
        
  this->toolbar.append(this->grid_on);
  this->toolbar.append(this->reset);
  this->toolbar.append(this->score_button);

  this->vbox.pack_start(this->toolbar, Gtk::PACK_SHRINK);
  this->vbox.pack_start(this->board);
  this->vbox.pack_start(this->hbox, Gtk::PACK_SHRINK);

  this->add(vbox);
  this->show_all_children();
}

MainWindow::~MainWindow()
{
  //delete stuff here
}

void MainWindow::update_score()
{
  this->score_button.set_label(std::to_string(this->board.get_move_count()) + "/" + std::to_string(MAX_MOVES));
}
