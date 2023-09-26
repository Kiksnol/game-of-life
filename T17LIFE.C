/*ND4 */
/* OKAY WE PROSTO IGRAEM V LIFE */
#include <stdlib.h>

#include <glut.h>

#include "LIFE.h"

#define FRAME_H 400
#define FRAME_W 600

byte Frame[FRAME_H][FRAME_W][3];
int Zoom = 6;

void PutPixel( int x, int y, int r, int g, int b )
{
  if (x < 0 || y < 0 || x >= FRAME_W || y >= FRAME_H)
    return;
  Frame[y][x][0] = b;
  Frame[y][x][1] = g;
  Frame[y][x][2] = r;
}

void Keyboard( unsigned char Key, int X, int Y )
{
  if (Key == 27)
    exit(0);
  else if (Key == '-')
    Zoom--;
  else if (Key == '+')
    Zoom++;
  else
    LifeKeyboard(Key);
}

void Display( void )
{
  LifeStep();
  fope();

  glClearColor(0.3, 0.5, 0.7, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  glFinish();

  glutSwapBuffers();
  glutPostRedisplay();
}

void main ( int ArgC, char *Argv[] )
{
  LifeInit();

  glutInit(&ArgC, Argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920, 1080);
  glutCreateWindow("ND4 T17LIFE");
  glutFullScreen();

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glClearColor(0.3, 0.5, 0.7, 1);
  glutMainLoop();
}