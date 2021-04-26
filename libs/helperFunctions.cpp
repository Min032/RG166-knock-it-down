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
  char *c = nullptr;

  glColor3f(1, 1, 1);

  glPushMatrix();
    glRasterPos3f(x, y, z);
    for (c = str; *c != '\0'; c++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
  glPopMatrix();
  glEnable(GL_LIGHTING);
  
}

auto generateRangedNumbers(double min, double max) -> std::vector<double> {

  std::vector<double> result;

  for(int i = 0; i < 15; i++) {
  
    double a_random_double = (static_cast<double>(rand())/static_cast<double>(RAND_MAX) * (max - min) + min);
    result.push_back(a_random_double);

  }

  return result;
}

auto generateRNZO() -> double {
  return (static_cast<double>(rand())/static_cast<double>(RAND_MAX));
}

auto isCollision(double catZ, double objX, double objZ) -> bool {

  if(abs(catZ -objZ) <= 0.5 && abs(3 - objX) <= 0.5) {
    return true;
  }
  else { 
    return false;
  }
}
