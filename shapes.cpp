#include "shapes.hpp"

void draw_axis(int n)
{
  glPushMatrix();
    glDisable(GL_LIGHTING);  
    glPushMatrix();
      
      glColor3f(1, 0, 0);
      glBegin(GL_LINES);
      glVertex3f(n, 0, 0);
      glVertex3f(0, 0, 0);
      glEnd();

      glColor3f(0, 1, 0);
      glBegin(GL_LINES);
      glVertex3f(0, n, 0);
      glVertex3f(0, 0, 0);
      glEnd();

      glColor3f(0, 0, 1);
      glBegin(GL_LINES);
      glVertex3f(0, 0, n);
      glVertex3f(0, 0, 0);
      glEnd();

    glPopMatrix();
    glEnable(GL_LIGHTING);
  glPopMatrix();
}

void drawPlatform()
{
  glPushMatrix();
    glScalef(1, 0.2, 1);
    glutSolidCube(1);
  glPopMatrix();
}