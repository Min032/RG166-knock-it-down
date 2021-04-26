#include <GL/gl.h>
#include <GL/glut.h>
#include <string>

#include "libs/callbackFunctions.hpp"

void onDisplay();
void onKeyboard(unsigned char key, int x, int y);
void onReshape(int width, int height);

void initEnables();

auto main(int argc, char **argv) -> int
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
  glEnable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  srand(time(nullptr));
}