/*
 *main-window.cc
 *
 *The main window containing the floodit board
 *
 *Author: Saketh Kasibatla
 */
#include "main-window-inl.hh"
#include <cstdlib>
#include <string>
#include <cstring>

MainWindow::MainWindow()
    :Gtk::Window(), vbox_(false), hbox_(true), board_(), score_(0),
     active_color_(this->board_.active_color()), toolbar_(),
     grid_on_("Hide Grid"), reset_("Reset"),
     score_button_(std::to_string(this->score_) + "/" + std::to_string(MAX_MOVES))
{

  this->set_title("Floodit");
  this->set_default_size(400,400);

  for(int i=0; i<NUM_COLORS; i++){
    switch(i){
      case NAVY:
        this->color_buttons_[i] = new Gtk::Button("NAVY");

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(this->board_, &GtkFlooditBoard::set_active_navy));

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(*this, &MainWindow::update_score));

        this->hbox_.pack_start(*(this->color_buttons_[i]));
        break;
      case BLUE:
        this->color_buttons_[i] = new Gtk::Button("BLUE");

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(this->board_, &GtkFlooditBoard::set_active_blue));

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(*this, &MainWindow::update_score));

        this->hbox_.pack_start(*(this->color_buttons_[i]));
        break;
      case GREEN:
        this->color_buttons_[i] = new Gtk::Button("GREEN");
        
        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(this->board_, &GtkFlooditBoard::set_active_green));

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(*this, &MainWindow::update_score));

        this->hbox_.pack_start(*(this->color_buttons_[i]));
        break;
      case YELLOW:
        this->color_buttons_[i] = new Gtk::Button("YELLOW");

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(this->board_, &GtkFlooditBoard::set_active_yellow));

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(*this, &MainWindow::update_score));

        this->hbox_.pack_start(*(this->color_buttons_[i]));
        break;
      case RED:
        this->color_buttons_[i] = new Gtk::Button("RED");

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(this->board_, &GtkFlooditBoard::set_active_red));

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(*this, &MainWindow::update_score));

        this->hbox_.pack_start(*(this->color_buttons_[i]));
        break;
      case PINK:
        this->color_buttons_[i] = new Gtk::Button("PINK");

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(this->board_, &GtkFlooditBoard::set_active_pink));

        this->color_buttons_[i]->signal_clicked().
            connect(sigc::mem_fun(*this, &MainWindow::update_score));

        this->hbox_.pack_start(*(this->color_buttons_[i]));
        break;
      default:
        this->color_buttons_[i] = new Gtk::Button();
    }
  }

  this->grid_on_.signal_toggled().
      connect(sigc::mem_fun(this->board_, &GtkFlooditBoard::toggle_grid_enabled));

  this->reset_.signal_clicked().
      connect(sigc::mem_fun(this->board_, &GtkFlooditBoard::Reset));
        
  this->toolbar_.append(this->grid_on_);
  this->toolbar_.append(this->reset_);
  this->toolbar_.append(this->score_button_);

  this->vbox_.pack_start(this->toolbar_, Gtk::PACK_SHRINK);
  this->vbox_.pack_start(this->board_);
  this->vbox_.pack_start(this->hbox_, Gtk::PACK_SHRINK);

  this->add(this->vbox_);
  this->show_all_children();
}

MainWindow::~MainWindow()
{
  for(int i=0;i<6;i++){
    delete this->color_buttons_[i];
  }
}

