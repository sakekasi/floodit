#ifndef GTK_FLOODIT_BOARD
#define GTK_FLOODIT_BOARD

#include <gtkmm/drawingarea.h>
#include "floodit-board.hh"

#define TOP_YCOORD 0
#define LEFT_XCOORD 0
#define REFRESH_TIME_MILLIS 50

class GtkFlooditBoard: public FlooditBoard, public Gtk::DrawingArea
{
public:
        GtkFlooditBoard();
        GtkFlooditBoard(FlooditBoard*);

        virtual ~GtkFlooditBoard();

        int get_width();
        int get_height();

        int get_col_width();
        int get_row_height();

        bool get_grid_enabled();
        void toggle_grid_enabled();

        void set_active_navy();
        void set_active_blue();
        void set_active_green();
        void set_active_yellow();
        void set_active_red();
        void set_active_pink();

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

        void show_win();
        void show_lose();

        int width;
        int height;

        const int l_width;
        bool grid_enabled;
};


#endif
