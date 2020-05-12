#include <GL/gl.h>
#include <GL/glut.h>
#include <string>

#include "callbackFunctions.hpp"

void onDisplay(void);
void onKeyboard(unsigned char key, int x, int y);
void onReshape(int width, int height);

void init();

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

  // OpenGL init
  init();

  glutMainLoop();

  return 0;
}

void init()
{
  // Light parameters
  GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
	GLfloat light_specular[] = { 0.7, 0.7, 0.7, 1 };

  // Material parameters
  GLfloat ambient_coeffs[] = { 0.3, 0.3, 0.3, 1 };
	GLfloat diffuse_coeffs[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
  GLfloat shininess = 30;

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);

	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

  glEnable(GL_LIGHTING);
}