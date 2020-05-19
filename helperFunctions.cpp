#include "helperFunctions.hpp"

void setMaterialColor(GLfloat r, GLfloat g, GLfloat b)
{
  GLfloat diffuse_coeffs[] = { r, g, b, 1 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse_coeffs);
} 