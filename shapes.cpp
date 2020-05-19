#include "shapes.hpp"
#include "helperFunctions.hpp"
#include <cmath>

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

void drawPolygon()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_POLYGON);
    glVertex3f(0.5, 0, 0.5);
    glVertex3f(-0.5, 0, 0.5);
    glVertex3f(-0.5, 0, -0.5);
    glVertex3f(0.5, 0, -0.5);
  glEnd(); 
}

void drawSidePlat()
{
  double clipPlaneLeft[] = {0, 1, 1, 0};
  glClipPlane(GL_CLIP_PLANE0, clipPlaneLeft);

  glEnable(GL_CLIP_PLANE0);  
  glutSolidCube(1);
  glDisable(GL_CLIP_PLANE0);

  glPushMatrix();
    glRotatef(45, 1, 0, 0);
    glScalef(1, 1, sqrt(2));
    drawPolygon();
  glPopMatrix();

}

void drawMidPlat()
{
  glutSolidCube(1);
}

void generatePlatform()
{
  
  setMaterialColor(0.000, 0.749, 1.000);

  glPushMatrix();
    glTranslatef(240, 0, 0);
    glScalef(500, 0.6, 4);
    drawMidPlat();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(240, 0, -3.5);
    glRotatef(180, 0, 0, 1);
    glScalef(500, 0.6, 3);
    drawSidePlat();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(240, 0, +3.5);
    glRotatef(180, 0, 0, 1);
    glRotatef(180, 0, 1, 0);
    glScalef(500, 0.6, 3);
    drawSidePlat();
  glPopMatrix();
  

}