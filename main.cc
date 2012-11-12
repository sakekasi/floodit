/*
 *main.cc
 *
 *Main file for floodit
 *
 *Author: Saketh Kasibatla
 */

#include <gtkmm/application.h>
#include "gtk-floodit-board.hh"
#include "main-window.hh"

int main(int argc, char **argv)
{
//        Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
        Gtk::Main main(argc, argv);
        
        MainWindow win;
        
        main.run(win);
        return 0;
}
