/*
 *main.cc
 *
 *Main file for floodit
 *
 *Author: Saketh Kasibatla
 */

#include <gtkmm/application.h>
#include "main-window-inl.hh"

int main(int argc, char **argv)
{
  Gtk::Main main(argc, argv);
        
  MainWindow win;
        
  main.run(win);
  return 0;
}
