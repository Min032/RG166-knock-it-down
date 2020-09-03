#include <GL/gl.h>
#include <GL/glut.h>
#include <string>

#include "callbackFunctions.hpp"

void onDisplay(void);
void onKeyboard(unsigned char key, int x, int y);
void onReshape(int width, int height);

void initEnables();

int main(int argc, char **argv)
{
  const char *gameName = "Knock it down!";

  // Glut initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Creating the window
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(1280, 768);
  glutCreateWindow(gameName);

  // Callback functions init
  glutKeyboardFunc(onKeyboard);
  glutReshapeFunc(onReshape);
  glutDisplayFunc(onDisplay);
  glutSpecialFunc(onKeyboardSpecial);

  // OpenGL init
  initEnables();

  glutMainLoop();

  return 0;
}

void initEnables()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glEnable(GL_TEXTURE_2D);

}