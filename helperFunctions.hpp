#ifndef HELPER_HPP
#define HELPER_HPP

#include <GL/gl.h>
#include <GL/glut.h>

#include <string>
#include <vector>

void setMaterialColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha);

void drawRomanString(char *str, double x, double y, double z);
std::vector<double> generateRangedNumbers(double min, double max);
double generateRNZO();

bool isCollision(double catZ, double objX, double objZ);

#endif