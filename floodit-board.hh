#ifndef FLOODIT_BOARD_H
#define FLOODIT_BOARD_H

#define NAVY 0
#define BLUE 1
#define GREEN 2
#define YELLOW 3
#define RED 4
#define PINK 5

#define BOARD_SIZE 12
#define NUM_COLORS 6

typedef int color;

class FlooditBoard
{
public:
        FlooditBoard();
        virtual ~FlooditBoard();

        int max_percent();

        color color_at(int, int);

        color get_active_color();
        color set_active_color(color);

        color (*(get_color_values)())[BOARD_SIZE];
        
protected:

        color color_values[BOARD_SIZE][BOARD_SIZE];

        void h_set_active_color(color, color, int, int);

        void set_color(int, int, color);
};

#endif
