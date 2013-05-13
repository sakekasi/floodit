#ifndef CONSTANTS_HH
#define CONSTANTS_HH
#pragma once

#define WIDTH 800
#define HEIGHT 600
#define TOP_YCOORD 0
#define LEFT_XCOORD 0
#define REFRESH_TIME_MILLIS 50


const Uint8 BLACK_R = 0;
const Uint8 BLACK_G = 0;
const Uint8 BLACK_B = 0;

const Uint8 WHITE_R = 255;
const Uint8 WHITE_G = 255;
const Uint8 WHITE_B = 255;

const Uint8 OPAQUE = 255;

const Uint8 LINE_WIDTH = 1; //pixels

const Uint8 COLORS_RGB[6][3] = {
    {0, 0, 128}, //NAVY
    {65, 105, 225}, //BLUE
    {60, 179, 113}, //GREEN
    {251, 255, 0}, //YELLOW
    {220, 20, 60}, //RED
    {255, 105, 180} //PINK
};
#endif
