#include "callbackFunctions.hpp"
#include "shapes.hpp"

void onKeyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
    case 27:
      exit(0);
      break;
    
  }
}

void onReshape(int width, int height)
{
  glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, width/height, 1, 1000);
  
}

void onDisplay(void)
{
  GLfloat light_position[] = { 1, 1, 1, 0 };

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  gluLookAt(5, 3, 1, 0, 0, 0, 0, 1, 0);

  draw_axis(3);

  glPushMatrix();
    
    glColor3f(1, 1, 1);
    drawPlatform();

  glPopMatrix();


  glutSwapBuffers();
}

