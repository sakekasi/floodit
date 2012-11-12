#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


//import buttons and use them.
#include <gtkmm.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/toggletoolbutton.h>
#include "gtk-floodit-board.hh"

class MainWindow : public Gtk::Window
{
public:
        MainWindow();
        virtual ~MainWindow();
        
protected:
        Gtk::VBox vbox;
        Gtk::HBox hbox;
        
        GtkFlooditBoard board;

        Gtk::Toolbar toolbar;
        Gtk::ToggleToolButton grid_on;
        Gtk::ToolButton reset;

        Gtk::Button *color_buttons[6];
        
};

#endif        
