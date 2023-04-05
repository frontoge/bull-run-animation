#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <thread>
#include <chrono>


#include "parser.h"
#include "render.h"

Unit* units;
int timeCtr = 0;

int hours = 1;
int mins = 30;
std::string timestamp = "";

void timer()
{
    timestamp = std::to_string(hours) + ":" + std::to_string(mins) + "pm";
    using namespace std::chrono_literals;
    for (;timeCtr < 31; timeCtr++)
    {
        std::this_thread::sleep_for(1s);
        mins += 10;
        if (mins ==60)
        {
            mins = 0;
            hours++;
            timestamp = std::to_string(hours) + ":00pm";

        }
        else
            timestamp = std::to_string(hours) + ":" + std::to_string(mins) + "pm";

    }
}

//Background image texture
GLuint texture = 0;

//Current window Width and height
int w1 = 0;
int h1 = 0;

void idle()
{
    glutPostRedisplay();
}

/// @brief Function that is called when the window is resized
/// @param w width of the new window size
/// @param h height of the new window size
void reshape(int w, int h)
{
    w1 = w;
    h1 = h;
    //Set the viewport to go from origin to the current width and height of the window
    glViewport(0, 0, w, h);
}

/// @brief Draw the background image.
void background()
{
    // glColor3f(0.0f, 0.0f, 0.0f);
    //Set the texture to the background image
    glBindTexture(GL_TEXTURE_2D, texture);
    
    orthogonalStart();

    glPushMatrix();
    //Move it so its done from the origin
    glTranslatef(-w1/2, -h1/2, -1.0f);
    //Start drawing a Quadrilateral primitive
    glBegin(GL_QUADS);
        //Texture coords    Primitive Coordinates
        glTexCoord3i(0,1,2); glVertex3i(0,0, 2);
        glTexCoord3i(1,1,2); glVertex3i(w1,0, 2);
        glTexCoord3i(1,0,2); glVertex3i(w1,h1, 2);
        glTexCoord3i(0,0,2); glVertex3i(0,h1, 2);
    //Stop drawing the primitive
    glEnd();
    glPopMatrix();
    
    orthogonalEnd();
}


void display() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);

    background();

    for (int i = 0; i < 50; i++)
    {
        units[i].Draw(timeCtr);
    }

    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glRasterPos2i(width-300, height - 400);
    glColor3f(0.0f, 0.0f, 0.0f);
    // glDisable(GL_LIGHTING);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)timestamp.c_str());
    // glEnable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glutSwapBuffers();

    glFlush();

    
}

int main(int argc, char** args)
{
    //Create Unit entities and read in their positions
    units = new Unit[50];
    for (int i = 0; i < 50; i++)
    {
        if (i < 14) 
        {
            units[i].col = {0, 0, 255};
        }
        else
        {
            units[i].col = {255, 0, 0};
        }
    }
    //Add unit symbols
    units[0].symbol = ASTERISK;
    units[1].symbol = F;
    units[2].symbol = C;
    units[3].symbol = E;
    units[4].symbol = I;
    units[5].symbol = L;
    units[6].symbol = A;
    units[7].symbol = M;
    units[8].symbol = G;
    units[9].symbol = H;
    units[10].symbol = D;
    units[11].symbol = K;
    units[12].symbol = B;
    units[48].symbol = RED_C;
    units[49].symbol = RED_G;



    parseInput(units);
    

    glutInit(&argc, args);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(static_cast<int>(width), static_cast<int>(height));
    glutInitWindowPosition(200, 200);
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGBA);
    // glEnable(GL_ALPHA);
    glutCreateWindow("Battle of Bull Run");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    texture = LoadTexture("img/bg.png");
    loadFontText();
    std::thread t1(timer);
    glutMainLoop();
    t1.join();
    return 0;
}

