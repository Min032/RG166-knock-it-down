#include "helperFunctions.hpp"
#include <iostream>
#include <random>
#include <cmath>

void setMaterialColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
  GLfloat diffuse_coeffs[] = { r, g, b, alpha };
  //GLfloat ambient_coeffs[] = { r, g, b, 1 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
} 

void drawHelveticaString(char *str, double x, double y, double z) {
  
  glDisable(GL_LIGHTING);
  char *c;

  glColor3f(1, 1, 1);

  glPushMatrix();
    glRasterPos3f(x, y, z);
    for (c=str; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
  glPopMatrix();
  glEnable(GL_LIGHTING);
  
}

std::vector<double> generateRangedNumbers(double min, double max) {

  std::vector<double> result;

  std::uniform_real_distribution<double> unif(min, max);
  std::default_random_engine re;
  double a_random_double = unif(re);

  for(int i = 0; i < 15; i++) {
  
    double a_random_double = unif(re);
    result.push_back(a_random_double);

  }

  std::cout << "Called" << std::endl;
  return result;
}
