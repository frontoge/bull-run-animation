#pragma once

#include <GL/gl.h>

#include "render.h"

struct Coord
{
    int x;
    int y;
};

class Unit 
{
    public: 
        Unit();
        Unit(Symbols symbol, Color col);

        void Draw(int stage);
        //The units identifying symbol
        Symbols symbol;
        //The list of coordinates for each troop
        Coord coords[32];
        Coord lastCoord;
        Color col;

};

void parseInput(Unit* units);

