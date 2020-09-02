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

void drawTriPolygon(float v1x, float v1y, float v1z, 
                    float v2x, float v2y, float v2z,
                    float v3x, float v3y, float v3z) 
{
  glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(v1x, v1y, v1z);
    glVertex3f(v2x, v2y, v2z);
    glVertex3f(v3x, v3y, v3z);
  glEnd();

}

void drawPyramidEar() 
{
  glPushMatrix();
    glNormal3f(0, 1, 0);
    drawTriPolygon(0, 0.5, 0,
                   0.25, -0.5, -0.5,
                   0.25, -0.5, 0.5);
  glPopMatrix();

  glPushMatrix();
    glNormal3f(0, 1, 0);
    drawTriPolygon(0, 0.5, 0,
                   0.25, -0.5, -0.5,
                   -0.25, -0.5, 0);
  glPopMatrix();

  glPushMatrix();
    glNormal3f(0, 1, 0);
    drawTriPolygon(0, 0.5, 0,
                   -0.25, -0.5, 0,
                   0.25, -0.5, 0.5);
  glPopMatrix();

  glPushMatrix();
    glNormal3f(0, 1, 0);
    drawTriPolygon(0.25, -0.5, -0.5,
                   -0.25, -0.5, 0,
                   0.25, -0.5, 0.5);
  glPopMatrix();
}

void generatePlatform()
{
  
  setMaterialColor(0.2, 0.2, 0.2);

  glPushMatrix();
    glTranslatef(240, 0, 0);
    glScalef(500, 0.6, 8);
    glutSolidCube(1);
  glPopMatrix();
}

void generateCatto() 
{
  setMaterialColor(0.5, 0.5, 0.5);

  // Body
  glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glScalef(0.8, 0.6, 0.4);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  // Legs
  glPushMatrix();
    glTranslatef(-0.45, 1, 0.3);
    glScalef(0.1, 0.7, 0.1);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.4, 1, 0.3);
    glScalef(0.1, 0.7, 0.1);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.4, 1, -0.3);
    glScalef(0.1, 0.7, 0.1);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.45, 1, -0.3);
    glScalef(0.1, 0.7, 0.1);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  // Paws
  glPushMatrix();
    glTranslatef(-0.35, 0.35, 0.3);
    glScalef(0.12, 0.1, 0.1);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.5, 0.35, 0.3);
    glScalef(0.12, 0.1, 0.1);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.5, 0.35, -0.3);
    glScalef(0.12, 0.1, 0.1);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.35, 0.35, -0.3);
    glScalef(0.12, 0.1, 0.1);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();


  // Head
  glPushMatrix();
    glTranslatef(0.8, 1.9, 0);
    glScalef(0.35, 0.4, 0.3);
    glutSolidSphere(1, 50, 50);
  glPopMatrix();


  // Ears
  glPushMatrix();
    glTranslatef(0.85, 2.25, -0.15);
    glRotatef(-15, 1, 0, 0);
    glRotatef(-15, 0, 0, 1);
    glScalef(0.6, 0.5, 0.4);
    drawPyramidEar();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.85, 2.25, 0.15);
    glRotatef(15, 1, 0, 0);
    glRotatef(-15, 0, 0, 1);
    glScalef(0.6, 0.5, 0.4);
    drawPyramidEar();
  glPopMatrix();

}

