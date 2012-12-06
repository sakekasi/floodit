/*
 *gtk-floodit-board.cc
 *
 *A gtk subclass of FlooditBoard that can draw itself.
 *
 *Author: Saketh Kasibatla
 */
#include <cairomm/context.h>
#include <glibmm/main.h>
#include <gtkmm/messagedialog.h>
#include <cstring>
#include "gtk-floodit-board-inl.hh"

GtkFlooditBoard::GtkFlooditBoard()
    : FlooditBoard(), Gtk::DrawingArea(), l_width_(1), grid_enabled_(true)
{

  //set up signals
        
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &GtkFlooditBoard::on_timeout),
                                 REFRESH_TIME_MILLIS );
#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
  //Connect the signal handler if it isn't already a virtual method override:
  signal_draw().connect(sigc::mem_fun(*this, &GameOfLife::on_draw), false);
#endif //GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED

}

GtkFlooditBoard::GtkFlooditBoard(FlooditBoard *f)
    : GtkFlooditBoard()
{
  memcpy(this->color_values_, f->color_values(),
         sizeof(this->color_values_));
}


GtkFlooditBoard::~GtkFlooditBoard()
{
  //destroy things here.
}
        


//drawing functions

bool GtkFlooditBoard::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  this->width_ = (this->get_allocation().get_width() <
                 this->get_allocation().get_height())?
      this->get_allocation().get_width() :
      this->get_allocation().get_height();
  
  this->height_ = (this->get_allocation().get_width() <
                  this->get_allocation().get_height())?
      this->get_allocation().get_width() :
      this->get_allocation().get_height();

  cr->set_line_width(this->l_width_);
  cr->save();

  this->fill_grid(cr);
  if(this->grid_enabled()){
    this->draw_grid(cr);
  }

  cr->restore();

  return true;
}

//specific drawing functions

bool GtkFlooditBoard::draw_grid(const Cairo::RefPtr<Cairo::Context>&cr)
{
  cr->save();
  cr->set_line_width(this->l_width_);
  cr->set_line_cap(Cairo::LINE_CAP_SQUARE);
  cr->set_source_rgb(1 ,1 , 1);

  for(int i=0;i < this->width(); i+=this->col_width()){
    cr->save();

    cr->move_to(i, TOP_YCOORD);
    cr->line_to(i, BOARD_SIZE * this->row_height());

    cr->stroke();
    cr->restore();
  }

  for(int i=0;i < this->height(); i+=this->row_height()){
    cr->save();

    cr->move_to(LEFT_XCOORD, i);
    cr->line_to(BOARD_SIZE* this->col_width(), i);

    cr->stroke();
    cr->restore();
  }
  cr->restore();
  return true;
}


bool GtkFlooditBoard::fill_grid(const Cairo::RefPtr<Cairo::Context>&cr)
{
  for(int i=0;i<BOARD_SIZE;i++){
    for(int j=0;j<BOARD_SIZE;j++){
      this->fill_square(cr, i, j, this->color_at(i,j));
    }
  }

  return true;
}


bool GtkFlooditBoard::fill_square(const Cairo::RefPtr<Cairo::Context>&cr,
                                  int c, int r, color col)
{
  int x=c*this->col_width();
  int y=r*this->row_height();
        
  cr->save();
  this->set_color(cr, this->color_at(c,r));

  cr->rectangle(x,y,this->col_width(), this->row_height());
  cr->fill();
  cr->restore();
        
  return true;
}


bool GtkFlooditBoard::set_color(const Cairo::RefPtr<Cairo::Context>&cr, color c)
{
  //find a way to get rid of these hard coded values (perhaps a
  //color scheme array)
  switch(c){
    case NAVY:
      cr->set_source_rgb(0.0, 0.0, 128.0 / 255.0);
      break;
    case BLUE:
      cr->set_source_rgb(65.0 / 255.0, 105.0/255.0 , 225.0 / 255.0);
      break;
    case GREEN:
      cr->set_source_rgb(60.0/255.0,179.0/255.0,113.0/255.0);
      break;
    case YELLOW:
      cr->set_source_rgb(255.0/255.0 ,215.0/255.0 ,0);
      break;
    case RED:
      cr->set_source_rgb(220.0/255.0 ,20.0/255.0 ,60.0/255.0);
      break;
    case PINK:
      cr->set_source_rgb(255.0/255.0, 105.0/255.0, 180.0/255.0);
      break;
    default:
      cr->set_source_rgb(0,0,0);
  }

  return true;
}

bool GtkFlooditBoard::on_timeout()
{
  Glib::RefPtr<Gdk::Window> win = get_window();
        
  if (win)
  {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                     get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
  return true;
}
