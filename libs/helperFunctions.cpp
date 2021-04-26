#include "helperFunctions.hpp"
#include <iostream>
#include <random>
#include <cmath>

void setMaterialColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
  GLfloat diffuse_coeffs[] = { r, g, b, alpha };
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
} 

void drawRomanString(char *str, double x, double y, double z) {
  
  glDisable(GL_LIGHTING);
  char *c;

  glColor3f(1, 1, 1);

  glPushMatrix();
    glRasterPos3f(x, y, z);
    for (c = str; *c != '\0'; c++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
  glPopMatrix();
  glEnable(GL_LIGHTING);
  
}

std::vector<double> generateRangedNumbers(double min, double max) {

  std::vector<double> result;

  for(int i = 0; i < 15; i++) {
  
    double a_random_double = ((double)rand()/(double)RAND_MAX * (max - min) + min);
    result.push_back(a_random_double);

  }

  return result;
}

double generateRNZO() {
  return ((double)rand()/(double)RAND_MAX);
}

bool isCollision(double catZ, double objX, double objZ) {

  if(abs(catZ -objZ) <= 0.5 && abs(3 - objX) <= 0.5) {
    return true;
  }
  else { 
    return false;
  }
}
