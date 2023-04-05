#pragma once

#include <GL/gl.h>


struct Color
{
    int red, green, blue;
};

enum Symbols 
{
    ASTERISK,
    A,
    B,
    RED_C,
    C,
    D,
    E,
    F,
    RED_G,
    G,
    H,
    I,
    K,
    L,
    M,
    NONE
};

//Scale factor of the initial window
const float scale = 2.0f;
//Width of the initial window
const int width = 1152 * scale;
//Height of the initial window
const int height = 900 * scale;

GLuint LoadTexture(const char * filename);

void drawSquare(int x, int y, int width, Color c);
void drawTextureSquare(int x, int y, int width, Color c, Symbols symbol);

void orthogonalStart();
void orthogonalEnd();
void loadFontText();

