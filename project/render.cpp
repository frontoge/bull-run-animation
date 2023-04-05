#include "render.h"

#include <GL/glut.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

GLuint font = 0;
GLuint fonts[15];

/// @brief Load a texture into the gpu memory from an image.
/// @param filename The file name of the image being used in the texture
/// @return The GPU
GLuint LoadTexture(const char * filename)
{
    GLuint text = 0;
    //Load an image file into raw byte data
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

    //Create a texture and store id in texture var
    glGenTextures( 1, &text ); 
    //Set the texture for the background as active
    glBindTexture( GL_TEXTURE_2D, text ); 
    //Set Texture environment mode to modulate
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 


    //even better quality, but this will do for now.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Set some texture parameters
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );


    //to the edge of our shape. 
    //Set the wrapping parameters 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, data);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    free( data ); //free the texture
    return text; //return whether it was successful
}

void loadFontText()
{
    fonts[ASTERISK] = LoadTexture("img/*.png");
    fonts[A] = LoadTexture("img/A.png");
    fonts[B] = LoadTexture("img/B.png");
    fonts[RED_C] = LoadTexture("img/c.png");
    fonts[C] = LoadTexture("img/C.png");
    fonts[D] = LoadTexture("img/D.png");
    fonts[E] = LoadTexture("img/E.png");
    fonts[F] = LoadTexture("img/F.png");
    fonts[RED_G] = LoadTexture("img/g.png");
    fonts[G] = LoadTexture("img/G.png");
    fonts[H] = LoadTexture("img/H.png");
    fonts[I] = LoadTexture("img/I.png");
    fonts[K] = LoadTexture("img/K.png");
    fonts[L] = LoadTexture("img/L.png");
    fonts[M] = LoadTexture("img/M.png");

}


void drawSquare(int x, int y, int w, Color c)
{
    double halfW = w/2;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-width/2, width/2, height/2, -height/2);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    //Translate to origin for x y coordinate placement
    glTranslatef(-width/2, -height/2, 0.0);

    //Move to x and y position of square
    glTranslatef(x, y, 0.0f);

    //Set color for square
    glColor4f(static_cast<float>(c.red/255.0), static_cast<float>(c.green/255.0), static_cast<float>(c.blue/255.0), 1.0f);
    //Draw the square
    glBegin(GL_QUADS);
        glVertex3d(x-halfW, y-halfW, 1.0);
        glVertex3d(x+halfW, y-halfW, 1.0);
        glVertex3d(x+halfW, y+halfW, 1.0);
        glVertex3d(x-halfW, y+halfW, 1.0);
    glEnd();
    glPopMatrix();


    orthogonalEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
}

void drawTextureSquare(int x ,int y, int w, Color c, Symbols symbol)
{
    double halfW = w/2;
    font = fonts[symbol];
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, font);
    // orthogonalStart();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-width/2, width/2, height/2, -height/2);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    //Translate to origin for x y coordinate placement
    glTranslatef(-width/2, -height/2, -1.0);

    //Move to x and y position of square
    glTranslatef(x, y, 0.0f);

    //Draw the square
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex3d(x-halfW, y-halfW, 1.0);
        glTexCoord2i(1, 0); glVertex3d(x+halfW, y-halfW, 1.0);
        glTexCoord2i(1, 1); glVertex3d(x+halfW, y+halfW, 1.0);
        glTexCoord2i(0, 1); glVertex3d(x-halfW, y+halfW, 1.0);
    glEnd();
    glPopMatrix();

    orthogonalEnd();
    glDisable(GL_TEXTURE_2D);

}

// Create the orthogonal projection matrix
void orthogonalStart()
{
    //Specify the current matrix as the projection matrix stack
    glMatrixMode(GL_PROJECTION);
    //Push the current matrix down one in the stack making the new top a duplicate of the one below
    glPushMatrix();
    //Replace the current matrix with the identity matrix
    glLoadIdentity();
    //Define a 2D orthographic projection matrix using the width of the window?
    gluOrtho2D(-width/2, width/2, -height/2, height/2);
    //Set the matrix mode back to the modelview matrix stack
    glMatrixMode(GL_MODELVIEW);
}

// Remove the orthogonal projection matrix
void orthogonalEnd()
{
    //Set the matrix stack to the projection matricies
    glMatrixMode(GL_PROJECTION);
    //Remove the top projection matrix from the stack
    glPopMatrix();
    //Set the matrix stack back to the modelview stack
    glMatrixMode(GL_MODELVIEW);
}
