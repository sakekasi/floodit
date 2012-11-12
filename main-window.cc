/*
 *main-window.cc
 *
 *The main window containing the floodit board
 *
 *Author: Saketh Kasibatla
 */
#include "main-window.hh"

MainWindow::MainWindow()
        :Gtk::Window(), board(), vbox(true), hbox(true),
         grid_on("Hide Grid"), toolbar()
{

        this->set_title("Floodit");
        this->set_default_size(400,400);

        for(int i=0; i<NUM_COLORS; i++){
                switch(i){
                case NAVY:
                        this->color_buttons[i] = new Gtk::Button("NAVY");
                        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                                       &GtkFlooditBoard::set_active_navy));
                        this->hbox.pack_start(*(this->color_buttons[i]));
                        break;
                case BLUE:
                        this->color_buttons[i] = new Gtk::Button("BLUE");
                        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                         &GtkFlooditBoard::set_active_blue));
                        this->hbox.pack_start(*(this->color_buttons[i]));
                        break;
                case GREEN:
                        this->color_buttons[i] = new Gtk::Button("GREEN");
                        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                         &GtkFlooditBoard::set_active_green));
                        this->hbox.pack_start(*(this->color_buttons[i]));
                        break;
                case YELLOW:
                        this->color_buttons[i] = new Gtk::Button("YELLOW");
                        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                         &GtkFlooditBoard::set_active_yellow));
                        this->hbox.pack_start(*(this->color_buttons[i]));
                        break;
                case RED:
                        this->color_buttons[i] = new Gtk::Button("RED");
                        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                         &GtkFlooditBoard::set_active_red));
                        this->hbox.pack_start(*(this->color_buttons[i]));
                        break;
                case PINK:
                        this->color_buttons[i] = new Gtk::Button("PINK");
                        this->color_buttons[i]->signal_clicked().connect(sigc::mem_fun(this->board,
                                                                         &GtkFlooditBoard::set_active_pink));
                        this->hbox.pack_start(*(this->color_buttons[i]));
                        break;
                default:
                        this->color_buttons[i] = new Gtk::Button();
                }
        }

        this->grid_on.signal_toggled().connect(sigc::mem_fun(this->board, &GtkFlooditBoard::toggle_grid_enabled));
        this->toolbar.append(this->grid_on);

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
