#include "parser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "render.h"


const int UNIT_WIDTH = 30;


Unit::Unit()
{
    for (int i = 0; i < 32; i++) 
    {
        coords[i] = {-2, -2};
    }
    lastCoord.x = -2;
    lastCoord.y = -2;
    col = {255, 0, 0};
    symbol = Symbols::NONE;
}

Unit::Unit(Symbols symbol, Color col)
:Unit()
{
    this->symbol = symbol;
    this->col = col;
}

void Unit::Draw(int stage)
{
    //If unit is getting deleted this time stamp
    if (this->coords[stage].x == -2)
    {
        return;
    }
    //If the unit does not move this time
    else if (this->coords[stage].x == -1) {
        //Check if the unit has not been placed on map yet
        if (this->lastCoord.x == -2) {
            return;
        }
        //Draw it at its most recent position
        else {
            if (this->symbol != Symbols::NONE)
                drawTextureSquare(lastCoord.x, lastCoord.y, UNIT_WIDTH, col, this->symbol);
            else
                drawSquare(lastCoord.x, lastCoord.y, UNIT_WIDTH, col);
        }
    }
    //If the unit has a movement coord then move it to there and update the most recent position
    else 
    {
        if (this->symbol != Symbols::NONE)
            drawTextureSquare(this->coords[stage].x, this->coords[stage].y, UNIT_WIDTH, col, this->symbol);
        else
            drawSquare(this->coords[stage].x, this->coords[stage].y, UNIT_WIDTH, col);
        lastCoord.x = coords[stage].x;
        lastCoord.y = coords[stage].y;
    }    
}

void parseInput(Unit* units)
{
    //Open input stream
    std::ifstream fin("data/movement.data");
    if (!fin) {
        return;
    }
    //Parsing algorithm
    /*
        For each line in the file
            Createa a troop object.
            Assign the correct Identifying symbol.
            Assign the correct timestamp?
            From 0-31

    */
    //Until hitting the end of the file
    
    for (int unitCtr = 0; unitCtr < 50; unitCtr++)
    {
        int colCtr = 0;
        std::string line;
        std::getline(fin, line);
        std::stringstream stream(line);
        //If there is more to the line of instructions
        while(stream)
        {
            Coord newCoord;
            if (stream.peek() == 13 || char(stream.peek()) == ',') {
                break;
            }
            if(stream.peek() == '$')
            {
                newCoord.x = -2;
                newCoord.y = -2;
                stream.ignore(10, '$');
            }
            else{
                stream >> newCoord.x >> newCoord.y;
                stream.ignore(10, ',');
            }

            units[unitCtr].coords[colCtr] = newCoord;
            colCtr++;
            // std::this_thread::sleep_for(200ms);
        }
    }



    //Close input stream
    fin.close();
}
