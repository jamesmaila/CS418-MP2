/* James Maila
 * CS418 - Spring 2015
 * 
 * MP2: Flight Simulator
 */ 

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "camera.h"

#define FPS 100
#define FONT GLUT_BITMAP_TIMES_ROMAN_24

using namespace std;

float sealevel;
float polysize;

Camera flyCam;

int frameCount = 0;
float fps;
int previousTime;


/*
 * CalculateFPS
 *     Inputs: None.
 *     Outputs: None.
 *     Description: Calculates the running frames per second.
 */
void CalculateFPS()
{
    frameCount++;
 
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
 
    int timeInterval = currentTime - previousTime;
 
    if (timeInterval > 1000)
    {
        fps = frameCount / (timeInterval/1000.0);
 
        previousTime = currentTime;
 
        frameCount = 0;
    }   
}

/*
 * DrawFPS
 *     Inputs: None.
 *     Outputs: None.
 *     Description: Draws the frames per second to the screen.
 */
void DrawFPS()
{

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING); 

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, GLUT_WINDOW_WIDTH, 0.0, GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.0, 1.0, 0.0);
    glRasterPos2i(10, 10);

    ostringstream stream;
    
    (fps == 0) ? (stream << "Calculating FPS...") 
               : (stream << "FPS: " << fps);

    string fpsString = stream.str();
    int length = fpsString.length();

    for (int i = 0; i < length; i++)
    {
        glutBitmapCharacter(FONT, fpsString[i]);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

/*
 * Timer
 *     Inputs: v - Value of the glutTimerFunc value parameter.
 *     Outputs: None.
 *     Description: The Glut timer function. 
 *                  Responsible for synchronizing our animation.
 */
void Timer(int v)
{
    if (!flyCam.Paused) { CalculateFPS(); }

    glutTimerFunc(1000/FPS, Timer, v);
}

/*
 * Seed
 *     Inputs: x - x seed value.
 *             y - y seed value.
 *     Returns: The seed value for generating a random number.
 *     Description: The seed function used for random number generation.
 */
int Seed(float x, float y)
{
    static int a = 1588635695, b = 1117695901;
    int xi = *(int *)&x;
    int yi = *(int *)&y;
    return ((xi * a) % b) - ((yi * b) % a);
}

/*
 * Mountain
 *     Description: Recursive method that makes mountains
 *                  randomly using Seed(x, y).
 */
void Mountain(
    float s,
    float x0, float y0, float z0, 
    float x1, float y1, float z1, 
    float x2, float y2, float z2)
{
    float x01, y01, z01, x12, y12, z12, x20, y20, z20;

    if (s < polysize)
    {
        x01 = x1 - x0;
        y01 = y1 - y0;
        z01 = z1 - z0;

        x12 = x2 - x1;
        y12 = y2 - y1;
        z12 = z2 - z1;

        x20 = x0 - x2;
        y20 = y0 - y2;
        z20 = z0 - z2;

        float nx = y01*(-z20) - (-y20)*z01;
        float ny = z01*(-x20) - (-z20)*x01;
        float nz = x01*(-y20) - (-x20)*y01;

        float den = sqrt(nx*nx + ny*ny + nz*nz);

        if (den > 0.0)
        {
            nx /= den;
            ny /= den;
            nz /= den;
        }

        glNormal3f(nx,ny,nz);
        glBegin(GL_TRIANGLES);
            glVertex3f(x0,y0,z0);
            glVertex3f(x1,y1,z1);
            glVertex3f(x2,y2,z2);
        glEnd();

        return;
    }

    x01 = 0.5 * (x0 + x1);
    y01 = 0.5 * (y0 + y1);
    z01 = 0.5 * (z0 + z1);

    x12 = 0.5 * (x1 + x2);
    y12 = 0.5 * (y1 + y2);
    z12 = 0.5 * (z1 + z2);

    x20 = 0.5 * (x2 + x0);
    y20 = 0.5 * (y2 + y0);
    z20 = 0.5 * (z2 + z0);

    s *= 0.5;

    srand(Seed(x01, y01));
    z01 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
    srand(Seed(x12,y12));
    z12 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
    srand(Seed(x20,y20));
    z20 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);

    Mountain(s, x0,y0,z0, x01,y01,z01, x20,y20,z20);
    Mountain(s, x1,y1,z1, x12,y12,z12, x01,y01,z01);
    Mountain(s, x2,y2,z2, x20,y20,z20, x12, y12, z12);
    Mountain(s, x01,y01,z01, x12,y12,z12, x20,y20,z20);
}

/*
 * Initialize
 *     Inputs: None.
 *     Returns: None.
 *     Description: Initializes the environment and sets configuration variables.
 */
void Initialize() 
{
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lpos[] = { 0.0, 1.0, 0.0, 0.0 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glClearColor(0.5, 0.5, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    sealevel = 0.0;
    polysize = 0.02;
}

/*
 * Display
 *     Inputs: None.
 *     Returns: None.
 *     Description: The Glut display function. 
 *                  Responsible for drawing to the screen.
 */
void Display()
{
    GLfloat tanamb[] = {0.2, 0.15, 0.1, 1.0};
    GLfloat tandiff[] = {0.4, 0.3, 0.2, 1.0};

    GLfloat seaamb[] = {0.0, 0.0, 0.2, 1.0};
    GLfloat seadiff[] = {0.0, 0.0, 0.8, 1.0};
    GLfloat seaspec[] = {0.5, 0.5, 1.0, 1.0};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glLoadIdentity();             

    // update fly camera position if not paused
    if (!flyCam.Paused) { flyCam.Update(); }

    gluLookAt(flyCam.Eye.X, 
              flyCam.Eye.Y, 
              flyCam.Eye.Z, 
              flyCam.Eye.X + flyCam.Center.X, 
              flyCam.Eye.Y + flyCam.Center.Y, 
              flyCam.Eye.Z + flyCam.Center.Z,
              flyCam.Up.X, flyCam.Up.Y, flyCam.Up.Z);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tandiff);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);

    Mountain(1.0, 0.0,0.0,0.0, 1.0,0.0,0.0, 0.0,1.0,0.0);
    Mountain(1.0, 1.0,1.0,0.0, 0.0,1.0,0.0, 1.0,0.0,0.0);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, seaamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, seadiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, seaspec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);

    glNormal3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(0.0, 0.0, sealevel);
        glVertex3f(1.0, 0.0, sealevel);
        glVertex3f(1.0, 1.0, sealevel);
        glVertex3f(0.0, 1.0, sealevel);
    glEnd();

    DrawFPS();

    glutSwapBuffers();
    glFlush ();

    glutPostRedisplay();
}

/*
 * Reshape
 *     Inputs: None.
 *     Returns: None.
 *     Description: The Glut reshape function. 
 *                  Responsible for reshaping the current window.
 */
void Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 0.01, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

/*
 * Keyboard
 *     Inputs: key - Ascii key pressed.
 *             x - X mouse position when key pressed.
 *             y - Y mouse position when key pressed.
 *     Outputs: None.
 *     Description: The Glut keyboard function.
 *                  Responsible for interpreting keyboard interrupts.
 */
void Keyboard(unsigned char key, int x, int y)
{
   switch (key) 
   {
        // decrease sea level
        case '-': sealevel -= 0.01; break;
        // increase sea level
        case '=': sealevel += 0.01; break;
        // decrease polygon size
        case 'f': polysize *= 0.5; break;
        // increase polygon size
        case 'c': polysize *= 2.0; break;
        // speed up
        case 'e':  if (!flyCam.Paused) { flyCam.SpeedUp(); } break;
        // slow down (reverse)
        case 'q': if (!flyCam.Paused) { flyCam.SlowDown(); } break;
        // yaw left
        case 'a': if (!flyCam.Paused) { flyCam.Yaw(LEFT); } break;
        // yaw right
        case 'd': if (!flyCam.Paused) { flyCam.Yaw(RIGHT); } break;
        // pitch up
        case 'w': if (!flyCam.Paused) { flyCam.Pitch(UP); } break;
        // pitch down
        case 's': if (!flyCam.Paused) { flyCam.Pitch(DOWN); } break;
        // pause
        case 'p': flyCam.Paused = !flyCam.Paused; break;
        // exit
        case 27: exit(0);
   }
}

/*
 * ArrowKeys
 *     Inputs: key - Ascii key pressed.
 *             x - X mouse position when key pressed.
 *             y - Y mouse position when key pressed.
 *     Outputs: None.
 *     Description: The Glut special function.
 *                  Responsible for interpreting keyboard interrupts from arrow keys.
 */
void ArrowKeys(int key, int x, int y)
{
    if (!flyCam.Paused)
    {
        switch (key)
        {
            // roll left
            case GLUT_KEY_LEFT: flyCam.Roll(LEFT); break;
            // roll right
            case GLUT_KEY_RIGHT: flyCam.Roll(RIGHT); break;
            // pitch down
            case GLUT_KEY_DOWN: flyCam.Pitch(DOWN); break;
            // pitch up
            case GLUT_KEY_UP: flyCam.Pitch(UP); break;
        }
    }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500); 
   glutInitWindowPosition(100, 100);
   glutCreateWindow("MP2: Flight Simulator");
   Initialize();
   glutDisplayFunc(Display); 
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Keyboard);
   glutSpecialFunc(ArrowKeys);
   glutTimerFunc(100, Timer, FPS);
   glutMainLoop();
   return 0;
}
